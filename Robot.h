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


	bool m_sendCaptIR1; // actuellement le capteur IR arriere
	bool m_sendCaptIR2; // actuellement le capteur IR gauche
	bool m_sendCaptIR3; // actuellement le capteur IR droite

	bool m_sendUS;


	static bool m_etatCaptIRArr;
	static bool m_etatCaptIRG;
	static bool m_etatCaptIRD;

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


#endif
