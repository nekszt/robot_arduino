#include "Communication.h"


void traitementRecep(char trameRecue[])
{
	const char carDelim = ',';
	char commande[3] = "";
	char tabParam[NB_PARAM_MAX][TAILLE_PARAM_TOT] = { "" };
	int iBcl = 0;
	int iCptParam = 0;
	int iTamponDebParam = 0;


	// rajouter condition sur trameRecu
	// while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TOT)
	while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TRAM)
	{
		commande[iBcl] = trameRecue[iBcl];
		iBcl++;
	}

	while (trameRecue[iBcl] != carDelim && iBcl < TAILLE_TRAME_A_TRAITER)
	{
		iBcl++;
	}

	// On est au caractere de delimitation de la commande
	// PRINTD(commande);
	// PRINTD(trameRecue[iBcl]);

	// on saute ce caractere de separation
	// iTamponDebParam correspond ici au premier caractere du 1er parametre
	iTamponDebParam = ++iBcl;


	// on place les parametres dans le tableau de parametres
	// dans cette condition on doit utilisé la taille max d'une trame complète : on doit donc mettre la chaine que l'on reçoit
	// dans une nouvelle variable dont on connait la taille (fixe)
	if (iBcl < 50)
	{
		/*while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TOT)
		{*/
			int cptChaine = 0;

			// while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TOT + iTamponDebParam)
			while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TRAM + iTamponDebParam)
			{
				tabParam[iCptParam][cptChaine] = trameRecue[iBcl];
				cptChaine++;
				iBcl++;
			}

			// Cette boucle permet d'atteindre le caractere de separation des trames, si ce n'est pas deja fait
			while (trameRecue[iBcl] != carDelim)
			{
				iBcl++;
			}

			// on saute ce caractere de separation
			// iTamponDebParam correspond ici au premier caractere du 2eme parametre
			iTamponDebParam = ++iBcl;


			/*iCptParam++;
		}*/

			PRINTD(tabParam[0]);
			PRINTDC(trameRecue[iBcl]);
	}
}

