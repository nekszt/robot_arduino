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
	{
		m_lHeureDeb = millis();
		m_started = true;
	}
	else
	{
		m_lHeureDeb = -1;
		m_started = false;
	}
}

void Temporisation::demTempo()
{
	m_lHeureDeb = millis();
	m_started = true;
}

bool Temporisation::finTempo()
{
	bool bRetFinTempo = false;

	/*
	si on a pas démarré la tempo, on retourne true
	(utile si on veut rentrer dans une condition directement la première fois alors qu'on ne l'a pas démarrée)
	*/
	if (m_lHeureDeb == -1 || (millis() - m_lHeureDeb >= m_lDuree))
	{
		bRetFinTempo = true;
		m_started = false;
	}

	return bRetFinTempo;
}

bool Temporisation::finTempo(long lDuree)
{
	bool bRetFinTempo = false;

	if (m_lHeureDeb == -1 || (millis() - m_lHeureDeb >= lDuree))
	{
		bRetFinTempo = true;
		m_started = false;
	}

	return bRetFinTempo;
}

void Temporisation::setDuree(long lDuree)
{
	if (lDuree >= 0)
		m_lDuree = lDuree;
	else
		m_lDuree = 0;
}

bool Temporisation::isStart() const
{
	return m_started;
}

void Temporisation::stop()
{
	m_started = false;
}
