#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "Robot.h"


#define TAILLE_CMD_TRAM 2

// Ne pas modifier
#define TAILLE_CMD_TOT TAILLE_CMD_TRAM + 1

#define NB_PARAM_MAX 3
#define TAILLE_PARAM_TRAM 3

// Ne pas modifier
#define TAILLE_PARAM_TOT TAILLE_PARAM_TRAM + 1


#define TAILLE_TRAME_A_TRAITER_TOT 21
#define TAILLE_TRAME_A_TRAITER 20


#define PARAM_VIDE -1 // utilisé lorsque la commande ou le parametre est vide

// ATTENTION modifier la taille de ces defines si on modifie la taille des params
#define CMD_BLANK	"  "
#define PARAM_BLANK "   "


// Define pour la reception des trames
#define MO	1 // Moteur On
#define MOG	2 // Moteur On Gauche
#define MOD 3

#define MV	4
#define MVG 5
#define MVD 6

#define MA	7
#define MAG 8
#define MAD 9

#define RIR		10
#define RIR1	11
#define RIR2	12
#define RIR3	13

#define RUS	14


// Define pour l'envoie des trames
#define IR1 1
#define IR2 2
#define IR3 3

#define US	4

// vitesse max qu'il est possible d'envoyer au robot
#define VITESSE_PRECISION 10


const char carDelim = ',';

struct Trame
{
	char commande[TAILLE_CMD_TOT];
	char tabParam[NB_PARAM_MAX][TAILLE_PARAM_TOT];
};
typedef struct Trame Trame;

const Trame& traitementRecep(char trameRecue[]);
void dispatch(Robot &robot, Trame const &trameSeparee);

inline void ctorTram(char trame[], int cmd, bool state);
void sendCapteurs(Robot &robot);


inline void ctorTram(char trame[], int cmd, bool state)
{
	if (cmd < 1 || cmd > 99)
		return;

	String chaine = (String)cmd;

	if (state == false)
		chaine += carDelim + (String)state;

	int i;
	for (i = 0; i < chaine.length() && i < TAILLE_TRAME_A_TRAITER; i++)
	{
		trame[i] = chaine[i];
	}
	trame[i] = '\0';
}


#endif