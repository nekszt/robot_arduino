#include "Robot.h"

const int Robot::m_vitessePrecision = 10;

volatile uint8_t &Robot::m_captArrPin(PINF);
volatile uint8_t &Robot::m_captGPin(PINF);
volatile uint8_t &Robot::m_captDPin(PINF);
volatile uint8_t &Robot::m_captArrDDR(DDRF);
volatile uint8_t &Robot::m_captGDDR(DDRF);
volatile uint8_t &Robot::m_captDDDR(DDRF);
const uint8_t &Robot::m_captArrBit(BIT4);
const uint8_t &Robot::m_captGBit(BIT5);
const uint8_t &Robot::m_captDBit(BIT1);

volatile uint8_t &Robot::m_ledLPort(PORTC);
volatile uint8_t &Robot::m_ledLDDR(DDRC);
const uint8_t &Robot::m_ledLBit(BIT7);

volatile uint8_t &Robot::m_USPort(PORTD);
volatile uint8_t &Robot::m_USDDR(DDRD);
const uint8_t &Robot::m_USBit(BIT6);

volatile uint8_t &Robot::m_servoPort(PORTB);
volatile uint8_t &Robot::m_servoDDR(DDRB);
const uint8_t &Robot::m_servoBit(BIT7);


Robot::Robot()
{
	InitPort();
	InitPWM();

	m_moteurOnG = 0;
	m_moteurOnD = 0;
	m_moteurAvantG = 1;
	m_moteurAvantD = 1;
	m_moteurVitesseG = 0;
	m_moteurVitesseD = 0;

	// on initialise correctement les sorties pour piloter le robot
	MoteurGauche(m_moteurVitesseG, m_moteurAvantG);
	MoteurDroit(m_moteurVitesseD, m_moteurAvantD);

	PRINTD("ctor");
}


/***********************************
FONCTION INIT
***********************************/
void Robot::InitPort(void)
{
	/* init ports moteurs
	*  
	*  PC6 : motor 1 (PWM)
	*  PD4 : motor 1 (direction), PD7 : motor 2 (PWM)
	*  PE6 : motor 2 (direction)
	*/
	DDRC |= BIT6;
	DDRD |= (BIT7 | BIT4);
	DDRE |= BIT6;

	// led pin 13 - conflit avec ultrason !!! ---------- (réglé : US sur pin 12 (PD6) et servo sur pin 11 (PB7)) -----------
	m_ledLDDR |= m_ledLBit;
	// ----------------------------------------------------------------------------
	// on met en sorti US et servo
	m_USDDR |= m_USBit;
	m_servoDDR |= m_servoBit;

	/* init ports capteurs IR
	*  INPUT Direction
	*/
	//DDRF &= ~(BIT1 | BIT4 | BIT5);
	m_captArrDDR &= ~m_captArrBit;
	m_captGDDR &= ~m_captGBit;
	m_captDDDR &= ~m_captDBit;

	PRINTD("init ports robot");
}

void Robot::InitPWM(void)
{
	//MOTEUR DROIT (2) Timer 4 
	TCCR4A = 0b00000010;
	TCCR4B = 0b00001011;
	TCCR4C = 0b00001001;
	TCCR4D = 0b00000000;
	TCCR4E = 0b00100000;
	//OCR4D = 100; //<---Registre de comparaison

	//MOTEUR GAUCHE (1) Timer3
	TCCR3A = 0b10000001;
	TCCR3B = 0b00001101;
	TCCR3C = 0b00000000;
	//OCR3AL = 100; //<---Registre de comparaison
}


/***********************************
CONTROLE MOTEURS
***********************************/
void Robot::MoteurGauche(int iAlpha, bool bSens){
	if (bSens == true){
		PORTD |= BIT4;
	}
	else{
		PORTD &= ~BIT4;
	}

	//iAlpha = iAlpha*2.55;
	OCR3AL = iAlpha*2.55;
}


void Robot::MoteurDroit(int iAlpha, bool bSens){
	if (bSens == true){
		PORTE |= BIT6;
	}
	else{
		PORTE &= ~BIT6;
	}

	//iAlpha = iAlpha*2.55;
	OCR4D = iAlpha*2.55;
}


/***********************************
FONCTIONS TEST
***********************************/
void Robot::Test(void)
{
	//MOTEUR DROIT
	PORTD |= BIT7;
	PORTE |= BIT6;

	//MOTEUR GAUCHE
	PORTD |= BIT4;
	PORTC |= BIT6;
}


/***********************************
FONCTIONS PUBLIC
************************************/
void Robot::moteurOn(const bool gauche, const bool droite)
{
#warning a modifier apres les tests
	moteurOnG(gauche);
	moteurOnD(droite);

	/*if (gauche && droite)
		Test();*/

	PRINTD("moteurOn");
}

void Robot::moteurOnG(const bool gauche)
{
	// on met en route le moteur
	if (gauche && !m_moteurOnG)
	{
		m_moteurOnG = true;
		MoteurGauche(m_moteurVitesseG, m_moteurAvantG);
	}
	// on éteint le moteur
	else if (!gauche && m_moteurOnG)
	{
		m_moteurOnG = false;
		MoteurGauche(0, m_moteurAvantG);
	}

	PRINTD("moteurOnG");
}

void Robot::moteurOnD(const bool droite)
{
	// on met en route le moteur
	if (droite && !m_moteurOnD)
	{
		m_moteurOnD = true;
		MoteurDroit(m_moteurVitesseD, m_moteurAvantD);
	}
	// on éteint le moteur
	else if (!droite && m_moteurOnD)
	{
		m_moteurOnD = false;
		MoteurDroit(0, m_moteurAvantD);
	}

	PRINTD("moteurOnD");
}


void Robot::moteurAvant(const bool gauche, const bool droite)
{
	moteurAvantG(gauche);
	moteurAvantD(droite);

	PRINTD("moteurAvant");
}

void Robot::moteurAvantG(const bool gauche)
{
	// on met le moteur en avant
	if (gauche && !m_moteurAvantG)
	{
		m_moteurAvantG = true;

		if (m_moteurOnG)
			MoteurGauche(m_moteurVitesseG, true);
		else
			MoteurGauche(0, true);
	}
	// on met le moteur en arriere
	else if (!gauche && m_moteurAvantG)
	{
		m_moteurAvantG = false;

		if (m_moteurOnG)
			MoteurGauche(m_moteurVitesseG, false);
		else
			MoteurGauche(0, false);
	}

	PRINTD("moteurAvantG");
}

void Robot::moteurAvantD(const bool droite)
{
	// on met le moteur en avant
	if (droite && !m_moteurAvantD)
	{
		m_moteurAvantD = true;

		if (m_moteurOnD)
			MoteurDroit(m_moteurVitesseD, true);
		else
			MoteurDroit(0, true);
	}
	// on met le moteur en arriere
	else if (!droite && m_moteurAvantD)
	{
		m_moteurAvantD = false;

		if (m_moteurOnD)
			MoteurDroit(m_moteurVitesseD, false);
		else
			MoteurDroit(0, false);
	}

	PRINTD("moteurAvantD");
}


void Robot::moteurVitesse(const int vitesseG, const int vitesseD)
{
	moteurVitesseG(vitesseG);
	moteurVitesseD(vitesseD);

	PRINTD("moteurVitesse");
}

void Robot::moteurVitesseG(const int vitesseG)
{
	m_moteurVitesseG = vitesseG * m_vitessePrecision;

	if (m_moteurOnG)
		MoteurGauche(m_moteurVitesseG, m_moteurAvantG);
	else
		MoteurGauche(0, m_moteurAvantG);
	
	PRINTD("moteurVitesseG");
}

void Robot::moteurVitesseD(const int vitesseD)
{
	m_moteurVitesseD = vitesseD * m_vitessePrecision;

	if (m_moteurOnD)
		MoteurDroit(m_moteurVitesseD, m_moteurAvantD);
	else
		MoteurDroit(0, m_moteurAvantD);

	PRINTD("moteurVitesseD");
}


