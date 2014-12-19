#include "Communication.h"


// lorsque l'on appel cette fonction, on est sur de sa taille : TAILLE_TRAME_A_TRAITER_TOT
// et il y a toujours le caractere de fin de chaine : '\0'
// ne pas mettre d'espaces dans la trames (sinon il faudrait les enlever)
/**
* \fn void traitementRecep(char trameRecue[])
* \brief Traite la reception des trames
*
* \param trameRecue
* \return void
*/
Trame traitementRecep(char trameRecue[])
{
	const char carDelim = ',';
	Trame trameSeparee;
	// on initialise le conteneur de la trame découpée
	for (int i = 0; i < TAILLE_CMD_TRAM; i++)
	{
		trameSeparee.commande[i] = ' ';
	}
	for (int j = 0; j < NB_PARAM_MAX; j++)
	{
		for (int i = 0; i < TAILLE_PARAM_TRAM; i++)
		{
			trameSeparee.tabParam[j][i] = ' ';
		}
	}

	int iBcl = 0;
	int iCptParam = 0;
	int iTamponDebParam = 0;


	// rajouter condition sur trameRecu
	// while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TOT)
	while (trameRecue[iBcl] != carDelim && iBcl < TAILLE_CMD_TRAM && trameRecue[iBcl] != '\0')
	{
		trameSeparee.commande[iBcl] = trameRecue[iBcl];
		iBcl++;
	}

	while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0')
	{
		iBcl++;
	}

	// On est au caractere de delimitation de la commande
	// PRINTD(commande);
	// PRINTD(trameRecue[iBcl]);

	// on saute ce caractere de separation, sinon on est à la fin de la trame
	// iTamponDebParam correspond ici au premier caractere du 1er parametre
	if (trameRecue[iBcl] != '\0')
		iTamponDebParam = ++iBcl;


	// on place les parametres dans le tableau de parametres
	// dans cette condition on doit utilisé la taille max d'une trame complète : on doit donc mettre la chaine que l'on reçoit
	// dans une nouvelle variable dont on connait la taille (fixe)
	if (iBcl < 50)
	{
		while (trameRecue[iBcl] != '\0')
		{
			int cptChaine = 0;

			// while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TOT + iTamponDebParam)
			while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TRAM + iTamponDebParam)
			{
				trameSeparee.tabParam[iCptParam][cptChaine] = trameRecue[iBcl];
				cptChaine++;
				iBcl++;
			}

			// Cette boucle permet d'atteindre le caractere de separation des trames, si ce n'est pas deja fait
			while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0')
			{
				iBcl++;
			}

			// on saute ce caractere de separation, sinon on est à la fin de la trame
			// iTamponDebParam correspond ici au premier caractere du 2eme parametre
			if (trameRecue[iBcl] != '\0')
				iTamponDebParam = ++iBcl;


			iCptParam++;
		}

		PRINTD(trameSeparee.commande);
		PRINTD(trameSeparee.tabParam[0]);
		PRINTD(trameSeparee.tabParam[1]);
		PRINTD(trameSeparee.tabParam[2]);
	}

	return trameSeparee;
}



