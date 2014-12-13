#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

//#include <Arduino.h>
//#include "Fonctions.h"
//#include "Temporisation.h"
#include <iostream>
#include <cstdio>
#include <thread>
#include <chrono>

#define DEBUG
//#undef DEBUG

#ifdef DEBUG
#define PRINTD(chaine) printf("\n%s", chaine);
#define PRINTDC(car)	printf("\n%c", car);
#else
inline int PRINTD(char*, ...)
{
	return 0;
}
inline int PRINTDC(char, ...)
{
	return 0;
}
#endif


#define TAILLE_CMD_TRAM 2

// Ne pas modifier
#define TAILLE_CMD_TOT TAILLE_CMD_TRAM + 1

#define NB_PARAM_MAX 3
#define TAILLE_PARAM_TRAM 3

// Ne pas modifier
#define TAILLE_PARAM_TOT TAILLE_PARAM_TRAM + 1


#define TAILLE_TRAME_A_TRAITER_TOT 21
#define TAILLE_TRAME_A_TRAITER 20


void traitementRecep(char trameRecue[]);


#endif