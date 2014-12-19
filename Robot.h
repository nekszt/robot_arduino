#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
public:
	Robot();

	void moteurOn(bool gauche = true, bool droite = true);
	void moteurOnG(bool gauche = true);
	void moteurOnD(bool droite = true);

	void moteurAvant(bool gauche = true, bool droite = true);
	void moteurAvantG(bool gauche = true);
	void moteurAvantD(bool droite = true);
	
	void moteurVitesse(int vitesse);
	void moteurVitesseG(int vitesseG);
	void moteurVitesseD(int vitesseD);


private:

	void InitPort(void);
	void InitPWM(void);

	void MoteurGauche(int iAlpha, bool bSens);
	void MoteurDroit(int iAlpha, bool bSens);
	void Test(void);

	bool CapteurArriere(void);
	bool CapteurGauche(void);
	bool CapteurDroit(void);


	// Variables permettant de connaitre l'état des moteurs
	bool m_moteurOnG;
	bool m_moteurOnD;
	bool m_moteurAvantG;
	bool m_moteurAvantD;
	int m_moteurVitesseG; // vitesse entre 0 et 100
	int m_moteurVitesseD;
};

#endif
