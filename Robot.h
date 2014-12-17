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
	int m_vitesseG;
	int m_vitesseD;
};

#endif
