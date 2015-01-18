#ifndef ROBOT_H
#define ROBOT_H

#include "UltraSon.h"

class Robot
{
public:
	Robot();

	inline void moteurOn(const bool gauche = true, const bool droite = true);
	inline void moteurOnG(const bool gauche = true);
	inline void moteurOnD(const bool droite = true);

	inline void moteurAvant(const bool gauche = true, const bool droite = true);
	inline void moteurAvantG(const bool gauche = true);
	inline void moteurAvantD(const bool droite = true);
	
	inline void moteurVitesse(const int vitesseG, const int vitesseD);
	inline void moteurVitesseG(const int vitesseG);
	inline void moteurVitesseD(const int vitesseD);

	void regulVitesse();
	inline void setMoteurVitessePalierInc(int iVal);
	inline void setMoteurDelayPalierInc(int iVal);


	inline void setSendCaptIR(const bool ir1 = true, const bool ir2 = true, const bool ir3 = true);
	inline void setSendCaptIRArr(const bool ir = true);
	inline void setSendCaptIRG(const bool ir = true);
	inline void setSendCaptIRD(const bool ir = true);
	inline bool canSendCaptIRArr() const;
	inline bool canSendCaptIRG() const;
	inline bool canSendCaptIRD() const;

	static bool CapteurArriere(const unsigned int delaiTest = 50);
	static bool CapteurGauche(const unsigned int delaiTest = 50);
	static bool CapteurDroit(const unsigned int delaiTest = 50);
	inline static bool getCaptIRArr();
	inline static bool getCaptIRG();
	inline static bool getCaptIRD();


	inline void interruptPinChange();
	inline void interruptOvfT1();

	inline void enableUtraSon();
	inline void disableUltraSon();

	inline void setSendDistance(const bool us = true);
	inline bool canSendDistance() const;

	inline uint16_t CapteurDistance(const unsigned int stepSize, const unsigned int delaiTest = 50);
	inline int getDistance();


	// Utilise le timer 1
	void initServoMoteur() const;
	// Position en degre de 0 a 45
	inline void setPositionServo(const int position) const;
	void enableServo() const;
	void disableServo() const;


	void Test(void);

	inline static void putON(volatile uint8_t &port, const uint8_t &bit);
	inline static void putOFF(volatile uint8_t &port, const uint8_t &bit);


	static volatile uint8_t &m_ledLPort;
	static const uint8_t &m_ledLBit;

private:

	void InitPort(void);
	void InitPWM(void);

	UltraSon m_ultraSon;

	void MoteurGauche(int iAlpha, bool bSens);
	void MoteurDroit(int iAlpha, bool bSens);



	// Variables permettant de connaitre l'état des moteurs
	bool m_moteurOnGConsigne;
	bool m_moteurOnDConsigne;
	bool m_moteurAvantGConsigne;
	bool m_moteurAvantDConsigne;
	int m_moteurVitesseGConsigne; // vitesse entre 0 et 100
	int m_moteurVitesseDConsigne;

	// valeur reelle sur les moteurs
	bool m_moteurOnG;
	bool m_moteurOnD;
	bool m_moteurAvantG;
	bool m_moteurAvantD;
	int m_moteurVitesseG; // vitesse entre 0 et 100
	int m_moteurVitesseD;

	int m_vitessePalierIncre; // incrementation de la vitesse par palier de m_vitessePalierIncre (pour lisser les variations de commande sur le moteur)
	int m_delayPalierIncre; // delay entre les incrementations de paliers

	const int m_vitessePrecision; // precicion pour la valeur de la consigne

	static const int m_motViteConsigneMin;

	static const int m_motViteMinSurIncrem; // utilise dans la fct regulVitesse
	static const int m_motViteMinSurDecrem; // utilise dans la fct regulVitesse


	bool m_sendCaptIR1; // actuellement le capteur IR arriere
	bool m_sendCaptIR2; // actuellement le capteur IR gauche
	bool m_sendCaptIR3; // actuellement le capteur IR droite

	bool m_sendDistance;


	static bool m_etatCaptIRArr;
	static bool m_etatCaptIRG;
	static bool m_etatCaptIRD;

	// ces variables sont mises à jour par l'ack, dans l'ack on stocke aussi la valeur associee de la variable sur le telephone
	bool m_bCaptIRArrPhone;
	bool m_bCaptIRGPhone;
	bool m_bCaptIRDPhone;
	// ajouter l'etat de la variable distance sur le telephone
	//int m_distancePhone;


	unsigned const long m_prescalerT1;
	const float m_coeffConvMsStepT1;


	// ports capteurs, servo, led, 

	static volatile uint8_t &m_captArrPin;
	static volatile uint8_t &m_captGPin;
	static volatile uint8_t &m_captDPin;
	static volatile uint8_t &m_captArrDDR;
	static volatile uint8_t &m_captGDDR;
	static volatile uint8_t &m_captDDDR;
	static const uint8_t &m_captArrBit;
	static const uint8_t &m_captGBit;
	static const uint8_t &m_captDBit;

	static volatile uint8_t &m_ledLDDR;

	//static volatile uint8_t &m_USPort;
	//static volatile uint8_t &m_USDDR;
	//static const uint8_t &m_USBit;

	static volatile uint8_t &m_servoPort;
	static volatile uint8_t &m_servoDDR;
	static const uint8_t &m_servoBit;
};


inline void Robot::putON(volatile uint8_t &port, const uint8_t &bit)
{
	port |= bit;
}

inline void Robot::putOFF(volatile uint8_t &port, const uint8_t &bit)
{
	port &= ~bit;
}


inline void Robot::setSendCaptIR(const bool ir1, const bool ir2, const bool ir3)
{
	setSendCaptIRArr(ir1);
	setSendCaptIRG(ir2);
	setSendCaptIRD(ir3);
	PRINTD("setSendCaptIR : params :");
	PRINTD(ir1);
	PRINTD(ir2);
	PRINTD(ir3);
}

inline void Robot::setSendCaptIRArr(const bool ir)
{
	m_sendCaptIR1 = ir;
	PRINTD("setSendCaptIRArr");
}

inline void Robot::setSendCaptIRG(const bool ir)
{
	m_sendCaptIR2 = ir;
	PRINTD("setSendCaptIR G");
}

inline void Robot::setSendCaptIRD(const bool ir)
{
	m_sendCaptIR3 = ir;
	PRINTD("setSendCaptIR D");
}

inline bool Robot::canSendCaptIRArr() const
{
	return m_sendCaptIR1;
}

inline bool Robot::canSendCaptIRG() const
{
	return m_sendCaptIR2;
}

inline bool Robot::canSendCaptIRD() const
{
	return m_sendCaptIR3;
}

inline bool Robot::getCaptIRArr()
{
	return m_etatCaptIRArr;
}

inline bool Robot::getCaptIRG()
{
	return m_etatCaptIRG;
}

inline bool Robot::getCaptIRD()
{
	return m_etatCaptIRD;
}


inline void Robot::setSendDistance(const bool us)
{
	PRINTD("setSendDiastance");

	if (m_sendDistance = us)
	{
		m_ultraSon.enable();
		PRINTD("enable");
	}
	else
	{
		m_ultraSon.disable();
		PRINTD("disable");
	}
}

inline bool Robot::canSendDistance() const
{
	return m_sendDistance;
}

inline uint16_t Robot::CapteurDistance(const unsigned int stepSize, const unsigned int delaiTest)
{
	return m_ultraSon.readDistance(stepSize, delaiTest);
}

inline int Robot::getDistance()
{
	return m_ultraSon.getDistance();
}

inline void Robot::interruptPinChange()
{
	m_ultraSon.interruptionPinChange();
}

inline void Robot::interruptOvfT1()
{
	m_ultraSon.interruptionOvf();
}

inline void Robot::enableUtraSon()
{
	m_ultraSon.enable();
}

inline void Robot::disableUltraSon()
{
	m_ultraSon.disable();
}


inline void Robot::setPositionServo(const int position) const
{
	if (position >= POS_SERVO_DEG_MIN && position <= POS_SERVO_DEG_MAX)
	{
		OCR1A = ((float)(1 + (position / (float)POS_SERVO_DEG_MAX)) * m_coeffConvMsStepT1) - 1;
	}
}


inline void Robot::setMoteurVitessePalierInc(int iVal)
{
	if (iVal > 50)
		m_vitessePalierIncre = 50;
	else if (iVal < 1)
		m_vitessePalierIncre = 1;
	else
		m_vitessePalierIncre = iVal;
}

inline void Robot::setMoteurDelayPalierInc(int iVal)
{
	if (iVal > 999)
		m_delayPalierIncre = 999;
	else if (iVal < 1)
		m_delayPalierIncre = 1;
	else
		m_delayPalierIncre = iVal;
}


/*********************************************************
* Fonction pour mettre les valeurs de consigne des moteurs
**********************************************************/


inline void Robot::moteurOn(const bool gauche, const bool droite)
{
	moteurOnG(gauche);
	moteurOnD(droite);

	/*if (gauche && droite)
	Test();*/

	PRINTD("moteurOn");
}

inline void Robot::moteurOnG(const bool gauche)
{
	// on met en route le moteur
	/*if (gauche && !m_moteurOnG)
	{
	m_moteurOnG = true;
	MoteurGauche(m_moteurVitesseG, m_moteurAvantG);
	}
	// on éteint le moteur
	else if (!gauche && m_moteurOnG)
	{
	m_moteurOnG = false;
	MoteurGauche(0, m_moteurAvantG);
	}*/

	m_moteurOnGConsigne = gauche;

	PRINTD("moteurOnG");
}

inline void Robot::moteurOnD(const bool droite)
{
	// on met en route le moteur
	/*if (droite && !m_moteurOnD)
	{
	m_moteurOnD = true;
	MoteurDroit(m_moteurVitesseD, m_moteurAvantD);
	}
	// on éteint le moteur
	else if (!droite && m_moteurOnD)
	{
	m_moteurOnD = false;
	MoteurDroit(0, m_moteurAvantD);
	}*/

	m_moteurOnDConsigne = droite;

	PRINTD("moteurOnD");
}


inline void Robot::moteurAvant(const bool gauche, const bool droite)
{
	moteurAvantG(gauche);
	moteurAvantD(droite);

	PRINTD("moteurAvant");
}

inline void Robot::moteurAvantG(const bool gauche)
{
	// on met le moteur en avant
	/*if (gauche && !m_moteurAvantG)
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
	}*/

	m_moteurAvantGConsigne = gauche;

	PRINTD("moteurAvantG");
}

inline void Robot::moteurAvantD(const bool droite)
{
	// on met le moteur en avant
	/*if (droite && !m_moteurAvantD)
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
	}*/

	m_moteurAvantDConsigne = droite;

	PRINTD("moteurAvantD");
}


inline void Robot::moteurVitesse(const int vitesseG, const int vitesseD)
{
	moteurVitesseG(vitesseG);
	moteurVitesseD(vitesseD);

	PRINTD("moteurVitesse");
}

inline void Robot::moteurVitesseG(const int vitesseG)
{
	m_moteurVitesseGConsigne = vitesseG * m_vitessePrecision;

	if (m_moteurVitesseGConsigne < m_motViteConsigneMin && m_moteurVitesseGConsigne != 0)
		m_moteurVitesseGConsigne = m_motViteConsigneMin;
	else if (m_moteurVitesseGConsigne > 100)
		m_moteurVitesseGConsigne = 100;

	/*if (m_moteurOnG)
	MoteurGauche(m_moteurVitesseG, m_moteurAvantG);
	else
	MoteurGauche(0, m_moteurAvantG);*/

	PRINTD("moteurVitesseG");
}

inline void Robot::moteurVitesseD(const int vitesseD)
{
	m_moteurVitesseDConsigne = vitesseD * m_vitessePrecision;

	if (m_moteurVitesseDConsigne < m_motViteConsigneMin && m_moteurVitesseDConsigne != 0)
		m_moteurVitesseDConsigne = m_motViteConsigneMin;
	else if (m_moteurVitesseDConsigne > 100)
		m_moteurVitesseDConsigne = 100;

	/*if (m_moteurOnD)
	MoteurDroit(m_moteurVitesseD, m_moteurAvantD);
	else
	MoteurDroit(0, m_moteurAvantD);*/

	PRINTD("moteurVitesseD");
}


#endif
