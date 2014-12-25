#ifndef ROBOT_H
#define ROBOT_H

#include "Fonctions.h"

class Robot
{
public:
	Robot();

	void moteurOn(const bool gauche = true, const bool droite = true);
	void moteurOnG(const bool gauche = true);
	void moteurOnD(const bool droite = true);

	void moteurAvant(const bool gauche = true, const bool droite = true);
	void moteurAvantG(const bool gauche = true);
	void moteurAvantD(const bool droite = true);
	
	void moteurVitesse(const int vitesseG, const int vitesseD);
	void moteurVitesseG(const int vitesseG);
	void moteurVitesseD(const int vitesseD);

	inline bool CapteurArriere(void);
	inline bool CapteurGauche(void);
	inline bool CapteurDroit(void);

	void Test(void);

	inline static void putON(volatile uint8_t &port, const uint8_t &bit);
	inline static void putOFF(volatile uint8_t &port, const uint8_t &bit);


	static volatile uint8_t &m_ledLPort;
	static const uint8_t &m_ledLBit;

private:

	void InitPort(void);
	void InitPWM(void);

	void MoteurGauche(int iAlpha, bool bSens);
	void MoteurDroit(int iAlpha, bool bSens);


	// Variables permettant de connaitre l'état des moteurs
	bool m_moteurOnG;
	bool m_moteurOnD;
	bool m_moteurAvantG;
	bool m_moteurAvantD;
	int m_moteurVitesseG; // vitesse entre 0 et 100
	int m_moteurVitesseD;


	bool m_etatCaptIRArr;
	bool m_etatCaptIRG;
	bool m_etatCaptIRD;

	// ces variables sont mises à jour par l'ack
	bool m_bCaptIRArrPhone;
	bool m_bCaptIRGPhone;
	bool m_bCaptIRDPhone;


	static const int m_vitessePrecision;


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

	static volatile uint8_t &m_USPort;
	static volatile uint8_t &m_USDDR;
	static const uint8_t &m_USBit;

	static volatile uint8_t &m_servoPort;
	static volatile uint8_t &m_servoDDR;
	static const uint8_t &m_servoBit;
};


/***********************************
CAPTEURS INFRA-ROUGE
***********************************/

inline bool Robot::CapteurArriere(void)
{
	//PF4
	//return !((PINF & BIT4) == BIT4);
	return !((m_captArrPin & m_captArrBit) == m_captArrBit);
}

inline bool Robot::CapteurGauche(void)
{
	//PF5
	//return !((PINF & BIT5) == BIT5);
	return !((m_captGPin & m_captGBit) == m_captGBit);
}

inline bool Robot::CapteurDroit(void)
{
	//PF1
	//return !((PINF & BIT1) == BIT1);
	return !((m_captDPin & m_captDBit) == m_captDBit);
}


inline void Robot::putON(volatile uint8_t &port, const uint8_t &bit)
{
	port |= bit;
}

inline void Robot::putOFF(volatile uint8_t &port, const uint8_t &bit)
{
	port &= ~bit;
}


#endif
