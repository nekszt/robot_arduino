#ifndef ULTRASON_H
#define ULTRASON_H


#include "Fonctions.h"


/* Cette classe prend en compte que le servo moteur utilisera le timer 1,
*  on fixe maintenant la periode du timer a 20ms (periode de la pwm du servomoteur)
*  on utilise pas d'interruption pour generer la pwm de l'ultrason, mais on met a jour
*  le registre de comparaison au bon moment
*  cela permet de ne pas trop ralentir le processeur
*/
// finalement on utilise les interruptions pour generer la pwm, car il y a des problemes de mises a jour de OCR1C

class UltraSon
{
public:

	UltraSon();

	void enable();
	void disable();

	uint16_t readDistance(const int taillePalier, const int delayActualise);

	inline void interruptionPinChange();
	inline void interruptionOvf();

	inline int getDistance();


private:

	void initPorts();
	void initTimer1();

	bool m_enable;

	const uint16_t m_top;
	// il est impossible de fixer m_nbrOvf a 1 (periode du timer), puisque l'on met le registre de comparaison OCR1C = m_top
	// lorsque l'on va dans l'interruption associee. On modifie OCR1C a top, donc ce registre sera valide lors du prochain ovf
	// m_nbrOvf = 0 est insense (moins d'une periode du timer...)
	// m_nbrOvf >= 2
	const uint8_t m_nbrOvf;
	unsigned const int m_pulse; // 10 - 1 : 40us

	long m_diff;
	uint16_t m_temporaire;
	bool m_bOK;
	uint8_t m_cptOvfOutput;
	bool m_diffChanged;

	uint8_t m_cptOvfPWM;

	unsigned const long m_prescaler;
	const float m_coeffConvMS;

	// en cm
	int m_distance;
	int m_distanceNew;
	uint16_t m_realDistance;



	static volatile uint8_t &m_pwmOutputDDR;
	static volatile uint8_t &m_pwmOutputPin;
	static const uint8_t &m_pwmOutputBit;

	static volatile uint8_t &m_compTrigDDR;
	static volatile uint8_t &m_compTrigPort;
	static const uint8_t &m_compTrigBit;
};




inline void UltraSon::interruptionPinChange()
{
	//Serial.println("pin change !");
	// si la pin est a 0
	if ((m_pwmOutputPin & m_pwmOutputBit) != m_pwmOutputBit)
	//if ((PINB & BIT6) != BIT6)
	{
		m_temporaire = TCNT1;

		/*Serial.println("low");
		Serial.println(m_temporaire);*/

		m_bOK = true;
		m_cptOvfOutput = 0;
	}
	else if (m_bOK)
	{
		m_diff = TCNT1 - m_temporaire;
		m_bOK = false;

		//Serial.println("high");

		if (m_cptOvfOutput != 0)
			m_diff += (m_cptOvfOutput * (m_top + 1))/*top*/;

		/*Serial.print("m_diff");
		Serial.println(m_diff);*/

		m_diffChanged = true;
	}
	else
	{
		//Serial.println("error PC\n");
		//m_diff = 0;
		//m_diffChanged = true;
	}
}

/*inline void UltraSon::interruptionCompC()
{
// disable PWM
// se mettra à jour au prochain ovf (doc)
// il est donc impossible de fixer m_nbrOvf a 1 (periode du timer), cela reviendrait a ne pas toucher ce registre
// m_nbrOvf = 0 est insense (moins d'une periode du timer...)

if (m_firstInterrupt)
{
// disable interruption
TIMSK1 &= ~BIT3;

OCR1C = m_top;

Serial.println(m_cptOvfPWM);
m_cptOvfPWM = 0;
}
m_firstInterrupt = true;
}*/

inline void UltraSon::interruptionOvf()
{
	// incremente le compteur de debordement pour calculer le temps a l'etat bas du signal de sortie du capteur
	m_cptOvfOutput++;

	m_cptOvfPWM++;

	if (m_cptOvfPWM >= m_nbrOvf) // Apparemment OCR1C se met a jour immediatement (contrairement a la doc...)
		// oui OCR1C se met a jour immediatement pour l'interruption de comparaison, mais pas pour la pwm
		// le probleme est resolu avec la variable m_firstInterrupt !
	{
		/*OCR1C = m_pulse; // se mettra à jour au prochain ovf (doc)
		//m_firstInterrupt = false;
		// enable interruption
		TIMSK1 |= BIT3;*/
		m_compTrigPort |= m_compTrigBit;
		delayMicroseconds(m_pulse);
		m_compTrigPort &= ~m_compTrigBit;

		m_cptOvfPWM = 0;
	}

	if (m_cptOvfOutput >= 25) // correspond a 50ms avec un prescaler de 250 000
	{
		// Cette condition a ete mise en place car le capteur ne reponds pas pendant 200ms
		// le signal a l'etat bas est beaucoup trop long
		// cela pose un probleme puisque l'on ne connait pas la distance pendant ce temps
		// donc on met la difference a 0 et on signal qu'il y a un changement
		// ce probleme n'etait pas present avec la pwm genere par le timer (sans interruption, sans toucher au port de la pin COMP/TRIG)
		m_diff = 0;
		m_diffChanged = true;
	}
}

inline int UltraSon::getDistance()
{
	return m_distance;
}


#endif

