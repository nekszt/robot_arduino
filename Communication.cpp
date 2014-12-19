#include "Communication.h"
#include "Robot.h"


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

void dispatch(Robot &robot, Trame &trameSeparee)
{
	String cmd = trameSeparee.commande;
	String params[NB_PARAM_MAX];
	for (int i = 0; i < NB_PARAM_MAX; i++)
	{
		params[i] = trameSeparee.tabParam[i];
	}


	if (cmd == MO)
	{
		// si on ne renseigne pas les parametres alors on appel la fonction sans les parametres (les moteurs se mettent en marche)
		if (params[0] == "" && params[1] == "")
			robot.moteurOn();
		else
			robot.moteurOn(params[0], params[1]); // conversion implicite de string à bool
	}

	else if (cmd == MOG)
	{
		if (params[0] == "")
			robot.moteurOnG();
		else
			robot.moteurOnG(params[0]);
	}

	else if (cmd == MOD)
	{
		if (params[0] == "")
			robot.moteurOnD();
		else
			robot.moteurOnD(params[0]);
	}

	else if (cmd == MV)
	{
		robot.moteurVitesse(params[0].toInt());
	}

	else if (cmd == MVG)
	{
		robot.moteurVitesseG(params[0].toInt());
	}

	else if (cmd == MVD)
	{
		robot.moteurVitesseD(params[0].toInt());
	}

	else if (cmd == MA)
	{
		if (params[0] == "" && params[1] == "")
			robot.moteurAvant();
		else
			robot.moteurAvant(params[0], params[1]); // conversion implicite de string à bool
	}

	else if (cmd == MAG)
	{
		if (params[0] == "")
			robot.moteurAvantG();
		else
			robot.moteurAvantG(params[0]); // conversion implicite de string à bool
	}

	else if (cmd == MAD)
	{
		if (params[0] == "")
			robot.moteurAvantD();
		else
			robot.moteurAvantD(params[0]); // conversion implicite de string à bool
	}
}

