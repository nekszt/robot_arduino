#ifndef TEMPORISATION_H
#define TEMPORISATION_H

#include <Arduino.h>

class Temporisation
{
public:
	//Temporisation();
	Temporisation(long lDuree = 0, bool bStart = 0);

	bool finTempo() const;
	bool finTempo(long lDuree) const; // on peut tester avec une autre durée que celle renseignée au début, si l'on renseigne ce paramètre
	void demTempo();
	void setDuree(long lDuree);

private:
	long m_lHeureDeb;
	long m_lDuree;
};

#endif
