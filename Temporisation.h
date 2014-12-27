#ifndef TEMPORISATION_H
#define TEMPORISATION_H

#include <Arduino.h>

class Temporisation
{
public:
	//Temporisation();
	Temporisation(long lDuree = 0, bool bStart = 0);

	bool finTempo();
	bool finTempo(long lDuree); // on peut tester avec une autre durée que celle renseignée au début, si l'on renseigne ce paramètre
	void demTempo();
	void setDuree(long lDuree);
	bool isStart() const;
	void stop();

private:
	long m_lHeureDeb;
	long m_lDuree;
	bool m_started;
};

#endif
