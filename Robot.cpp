#include "Robot.h"

Robot::Robot()
{
	InitPort();
	InitPWM();

	m_vitesseG = 50;
	m_vitesseD = 50;
}


/***********************************
FONCTION INIT
***********************************/
void Robot::InitPort(void)
{
	DDRC |= 0b01000000;
	DDRD |= 0b10010000;
	DDRE |= 0b01000000;
	DDRF = 0x00;
}

void Robot::InitPWM(void)
{
	//MOTEUR DROIT (2) Timer 4 
	TCCR4A = 0b00000010;
	TCCR4B = 0b00001110;
	TCCR4C = 0b00001001;
	TCCR4D = 0b00000000;
	TCCR4E = 0b00100000;
	//OCR4D = 0; <---Registre de comparaison

	//MOTEUR GAUCHE (1) Timer3
	TCCR3A = 0b10000001;
	TCCR3B = 0b00001101;
	TCCR3C = 0b00000000;
	//OCR3AL = 0; <---Registre de comparaison
}


/***********************************
CONTROLE MOTEURS
***********************************/
void Robot::MoteurGauche(int iAlpha, bool bSens){
	if (bSens == 1){
		PORTD = PORTD | BIT4;
	}
	if (bSens == 0){
		PORTD = PORTD &~BIT4;
	}

	iAlpha = iAlpha*2.55;
	OCR3AL = iAlpha;
}


void Robot::MoteurDroit(int iAlpha, bool bSens){
	if (bSens == 1){
		PORTE = PORTE | BIT6;
	}
	if (bSens == 0){
		PORTE = PORTE &~BIT6;
	}

	iAlpha = iAlpha*2.55;
	OCR4D = iAlpha;
}


/***********************************
CAPTEURS INFRA-ROUGE
***********************************/
bool Robot::CapteurArriere(void){
	//PF4
	bool bTest = 0;
	bTest = ((PINF & BIT4) == BIT4);
	bTest = !bTest;
	return bTest;
}

bool Robot::CapteurGauche(void){
	//PF5
	bool bTest = 0;
	bTest = ((PINF & BIT5) == BIT5);
	bTest = !bTest;
	return bTest;
}

bool Robot::CapteurDroit(void){
	//PF1
	bool bTest = 0;
	bTest = ((PINF & BIT1) == BIT1);
	return bTest;
}


/***********************************
FONCTIONS TEST
***********************************/
void Robot::Test(void){
	//MOTEUR DROIT
	PORTD = PORTD | BIT7;
	PORTE = PORTE | BIT6;
	//MOTEUR GAUCHE
	PORTD = PORTD | BIT4;
	PORTC = PORTC | BIT6;
}


/***********************************
FONCTIONS PUBLIC
************************************/
void Robot::moteurOn(bool gauche, bool droite)
{
	moteurOnG(gauche);
	moteurOnD(droite);

	// Test();
}

void Robot::moteurOnG(bool gauche)
{
	// on met en route le moteur
	if (gauche && !m_moteurOnG)
	{
		MoteurGauche(m_moteurVitesseG, m_moteurAvantG);
		m_moteurOnG = true;
	}
	// on éteint le moteur
	else if (!gauche && m_moteurOnG)
	{
		MoteurGauche(0, m_moteurAvantG);
		m_moteurOnG = false;
	}
}

void Robot::moteurOnD(bool droite)
{
	// on met en route le moteur
	if (droite && !m_moteurOnD)
	{
		MoteurDroit(m_moteurVitesseD, m_moteurAvantD);
		m_moteurOnD = true;
	}
	// on éteint le moteur
	else if (!droite && m_moteurOnD)
	{
		MoteurDroit(0, m_moteurAvantD);
		m_moteurOnD = false;
	}
}


void Robot::moteurAvant(bool gauche, bool droite)
{
	moteurAvantG(gauche);
	moteurAvantD(droite);
}

void Robot::moteurAvantG(bool gauche)
{
	// on met le moteur en avant
	if (gauche && !m_moteurAvantG)
	{
		MoteurGauche(m_moteurVitesseG, true);
		m_moteurAvantG = true;
	}
	// on met le moteur en arriere
	else if (!gauche && m_moteurAvantG)
	{
		MoteurGauche(m_moteurVitesseG, false);
		m_moteurAvantG = false;
	}
}

void Robot::moteurAvantD(bool droite)
{
	// on met le moteur en avant
	if (droite && !m_moteurAvantD)
	{
		MoteurDroit(m_moteurVitesseD, true);
		m_moteurAvantD = true;
	}
	// on met le moteur en arriere
	else if (!droite && m_moteurAvantD)
	{
		MoteurDroit(m_moteurVitesseD, false);
		m_moteurAvantD = false;
	}
}


void Robot::moteurVitesse(int vitesse)
{
	moteurVitesseG(vitesse);
	moteurVitesseD(vitesse);
}

void Robot::moteurVitesseG(int vitesseG)
{
	MoteurGauche(vitesseG, m_moteurAvantG);
}

void Robot::moteurVitesseD(int vitesseD)
{
	MoteurDroit(vitesseD, m_moteurAvantD);
}

