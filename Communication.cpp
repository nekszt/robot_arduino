#define DEBUG
//#undef DEBUG


#ifdef DEBUG
#define PRINTD Serial.println
#else
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



void traitementRecep(char trameRecue[])
{
	const char carDelim = ',';
	char commande[3] = "  ";
	char tabParam[NB_PARAM_MAX][TAILLE_PARAM_TOT] = { "" };
	int iBcl = 0;
	int iCptParam = 0;
	int iTamponDebParam = 0;


	// rajouter condition sur trameRecu
	while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TOT)
	{
		commande[iBcl] = trameRecue[iBcl];
		iBcl++;
	}

	while (trameRecue[iBcl] != carDelim)
	{
		iBcl++;
	}

	// On est au caractere de delimitation de la commande
	PRINTD(trameRecue[iBcl]);

	iTamponDebParam = ++iBcl;

	// on place les parametres dans le tableau de parametres
	if (iBcl < TAILLE_CMD_TOT)
	{
		while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TOT)
		{
			while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TOT + iTamponDebParam)
			{
				tabParam[iCptParam][TAILLE_PARAM_TOT];
				iBcl++;
			}

			iCptParam++;
		}
	}
}

