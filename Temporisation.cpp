#include "Temporisation.h"


/*Temporisation::Temporisation() : m_lHeureDeb(0), m_lDuree(1000)
{
}*/

Temporisation::Temporisation(long lDuree, bool bStart)
{
	if (lDuree >= 0)
		m_lDuree = lDuree;
	else
		m_lDuree = 0;

	if (bStart)
		m_lHeureDeb = millis();
	else
		m_lHeureDeb = -1;
}

void Temporisation::demTempo()
{
	m_lHeureDeb = millis();
}

bool Temporisation::finTempo() const
{
	bool bRetFinTempo = false;

	/*
	si on a pas démarré la tempo, on retourne true
	(utile si on veut rentrer dans une condition directement la première fois alors qu'on ne l'a pas démarrée)
	*/
	if (m_lHeureDeb == -1 || (millis() - m_lHeureDeb >= m_lDuree))
		bRetFinTempo = true;

	return bRetFinTempo;
}

bool Temporisation::finTempo(long lDuree) const
{
	bool bRetFinTempo = false;

	if (m_lHeureDeb == -1 || (millis() - m_lHeureDeb >= lDuree))
		bRetFinTempo = true;

	return bRetFinTempo;
}

void Temporisation::setDuree(long lDuree)
{
	if (lDuree >= 0)
		m_lDuree = lDuree;
	else
		m_lDuree = 0;
}
