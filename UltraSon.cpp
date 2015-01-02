#include "UltraSon.h"


// si l'on veut changer de pin, elle doit etre forcement sur un PINB
volatile uint8_t &UltraSon::m_pwmOutputDDR(DDRB);
volatile uint8_t &UltraSon::m_pwmOutputPin(PINB);
const uint8_t &UltraSon::m_pwmOutputBit(BIT6);

// difficile de changer de port car connecte au timer 1
// le nom est plus explicite
volatile uint8_t &UltraSon::m_compTrigDDR(DDRB);
volatile uint8_t &UltraSon::m_compTrigPort(PORTB);
const uint8_t &UltraSon::m_compTrigBit(BIT7);


UltraSon::UltraSon() : m_enable(false), m_top(TOP_TIMER1), m_nbrOvf(3), m_pulse(5),
m_diff(0), m_temporaire(0), m_bOK(false), m_cptOvfOutput(0), m_diffChanged(false),
m_cptOvfPWM(0), m_prescaler(250000), m_coeffConvMS(m_prescaler * 0.000001),
m_distance(-1), m_distanceNew(-1), m_realDistance(0)
{
	initPorts();
	initTimer1();

	PRINTD("ctor us called");
}

void UltraSon::enable()
{
	if (!m_enable)
	{
		m_bOK = false;

		// interruptions timer et pin PWM Output
		TIMSK1 |= BIT0/* | BIT3*/; // ovf
		PCMSK0 = m_pwmOutputBit; // on autorise pas les autres pins a faire des interruptions d'ou le = et non le |=

		//OCR1C = m_pulse;
		//TCCR1A |= BIT3;

		m_enable = true;
		PRINTD("enable us");
	}
}

void UltraSon::disable()
{
	if (m_enable)
	{
		PCMSK0 = 0x00; // on autorise pas les autres pins a faire des interruptions d'ou le = et non le &= ~m_pwmOutputBit
		TIMSK1 &= ~(BIT0 /*| BIT3*/); // ovf

		//TCCR1A &= ~(BIT3 | BIT2);

		m_distance = -1;
		m_realDistance = 0;

		m_enable = false;
		PRINTD("disable us");
	}
}

void UltraSon::initPorts()
{
	m_compTrigDDR |= m_compTrigBit;
	m_compTrigPort &= ~m_compTrigBit;
	m_pwmOutputDDR &= ~m_pwmOutputBit;

	PCICR |= BIT0;
	// Disable
	PCMSK0 = 0x00;
	// Enable
	//PCMSK0 |= m_pwmOutputBit;
}

void UltraSon::initTimer1()
{
	/* Parametrage :
	*
	*  On utilise actuellement un prescaler (Clk_IO / 64) = 250 000 coups d'horloge par seconde
	*  On envoie un signal haut sur la pin COMP/TRIG tous les 15 000 cps d'horloge (periode capteur : 60ms)
	*  comme la periode actuelle est de 20ms (pour le servomoteur), on doit atteindre 3 overflow du timer
	*  nbrOvf = 3 (le compteur commence a 0 : on aura bien 15000 paliers)
	*  60ms correspond tres bien, puisque si le robot est a pleine vitesse (33.3 cm/s), on enverra la distance tous les 2cm
	*  et comme le capteur fonctionne jusqu'a 5m (vitesse du son 340 m/s), les impulsions generee par le capteur reviennent
	*  en 29ms et on ajoute a cela le temps a l'etat bas du signal de sortie sur PWM Output qui est de 25ms (0.00005s * 500m)
	*  temps total de 54ms : on laisse bien le temps au capteur de faire son travail
	*
	*  top = 5 000 - 1
	*
	*  si on veut changer la periode du servomoteur ou de l'ultrason, comme les 2 sont tres lies par le timer,
	*  on devra utiliser des interruptions pour chacun (mais le programme serait moins rapide)
	*  si l'on change la periode de l'ultrason et qu'elle est un multiple de 20ms, il n'y a pas de probleme (on touche seulement a nbrOvf)
	*
	*  L'impulsion sur la pin COMP/TRIG, pour declencher l'envoie d'impulsion ultrason,
	*  ne doit pas etre trop longue (ni trop courte pour que le capteur puisse detecter cette impulsion)
	*  si on place un obstacle a 2cm du capteur (c = 340m/s), l'onde revient en 0.115ms
	*  l'impulsion de declenchement doit etre inferieure a 0.115ms
	*  on choisit une impulsion de 0.040ms
	*  pulse = 1 - 1 = 0 (correspond a 1 palier) fonctionne, meme si ce temps est tres court : 4us
	*
	*  au nbrOvf(3) ème overflow du timer on doit envoyer pulse
	*  c'est lors du nbrOvf - 1(3) ème overflow que l'on doit actualiser OCR1C = pulse, sinon on le fixe a top
	*  puisque OCR1C s'actualise a top
	*/
	// Finalement changement !!!!!!!!! on utilise des interruptions pour commander la pin COMP/TRIG


	//cli();

	ICR1 = m_top;
	//OCR1C = m_pulse;

	// Enable
	/*TIMSK1 = BIT0 | BIT3;

	TCCR1A = 0b00001010;
	TCCR1B = 0b00011011;
	TCCR1C = 0b00000000;*/

	// Disable timer interrupts
	TIMSK1 = 0x00;

	// initialisation du mode seulement et de l'horloge
	TCCR1A = 0b00000010;
	TCCR1B = 0b00011011;
	TCCR1C = 0b00000000;

	//sei();
}

uint16_t UltraSon::readDistance(const unsigned int taillePalier, const unsigned int delayActualise)
{
	static Temporisation tempo(delayActualise);

	if (m_diffChanged)
	{
		//PRINTD("us pin change");
		double tps;

		//Serial.print("temps = "); // temps du signal sur PWM Output en us
		tps = (m_diff / m_coeffConvMS);
		//Serial.println(tps);

		if (tps < 49500 && tps > 0) // si on a 50ms alors il y a une erreur
		{
			/* 50us represente 1cm,
			*  on corrige le defaut du capteur en enlevant 3cm
			*  on ajoute 0.5 pour que la valeur entiere soit arrondi correctement
			*/
			m_realDistance = (tps / 50.) - 2.5;
			//PRINTD("distance = "); // distance en cm
			//PRINTD(m_realDistance);
			m_distanceNew = (int)((m_realDistance + (taillePalier / 2.)) / taillePalier) * taillePalier;
			if (m_distanceNew != m_distance && tempo.finTempo())
			{
				tempo.demTempo();
				m_distance = m_distanceNew;
				//PRINTD(m_distance);
			}
		}
		else
		{
			//Serial.println("error !");
			/*Serial.print("temps = "); // temps du signal sur PWM Output en us
			Serial.println(tps);*/
			m_realDistance = 0;
			m_distanceNew = -1;
			if (m_distanceNew != m_distance && tempo.finTempo())
			{
				tempo.demTempo();
				m_distance = m_distanceNew;
			}

			//PRINTD("error");
		}

		m_diffChanged = false;
	}

	return m_realDistance;
}

