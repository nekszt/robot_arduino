#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <Arduino.h>
#include "Fonctions.h"
#include "Temporisation.h"


#define DEBUG
//#undef DEBUG

#ifdef DEBUG
#define PRINTD Serial.println
#else
inline int PRINTD(char*, ...)
{
	return 0;
}
inline int PRINTD(char, ...)
{
	return 0;
}
inline int PRINTD(int, ...)
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


// Define pour la reception des trames
#define MO	"1" // Moteur On
#define MOG	"2" // Moteur On Gauche
#define MOD "3"

#define MV	"4"
#define MVG "5"
#define MVD "6"

#define MA	"7"
#define MAG "8"
#define MAD "9"

#define RIR		"10"
#define RIR1	"11"
#define RIR2	"12"
#define RIR3	"13"

#define RUS	"14"


struct Trame
{
	char commande[TAILLE_CMD_TOT];
	char tabParam[NB_PARAM_MAX][TAILLE_PARAM_TOT];
};
typedef struct Trame Trame;

Trame traitementRecep(char trameRecue[]);


#endif