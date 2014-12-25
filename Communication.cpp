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
const Trame& traitementRecep(char trameRecue[])
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

	trameSeparee.commande[TAILLE_CMD_TOT - 1] = '\0';
	for (int i = 0; i < NB_PARAM_MAX; i++)
	{
		trameSeparee.tabParam[i][TAILLE_PARAM_TOT - 1] = '\0';
	}

	PRINTD("debut traitement trame");
	PRINTD("f1");


	int iBcl = 0;
	int iCptParam = 0;
	int iTamponDebParam = 0;


	// rajouter condition sur trameRecu
	// while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_CMD_TOT)
	while (trameRecue[iBcl] != carDelim && iBcl < TAILLE_CMD_TRAM && trameRecue[iBcl] != '\0')
	{
		PRINTD("f2");
		trameSeparee.commande[iBcl] = trameRecue[iBcl];
		iBcl++;
	}

	while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0')
	{
		iBcl++;
		PRINTD("f3");
	}

	// On est au caractere de delimitation de la commande
	// PRINTD(commande);
	// PRINTD(trameRecue[iBcl]);

	// on saute ce caractere de separation, sinon on est à la fin de la trame
	// iTamponDebParam correspond ici au premier caractere du 1er parametre
	if (trameRecue[iBcl] != '\0')
		iTamponDebParam = ++iBcl;



	// on place les parametres dans le tableau de parametres
	PRINTD("f10");
	while (trameRecue[iBcl] != '\0')
	{
		int cptChaine = 0;
		PRINTD("f11");
		// while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TOT + iTamponDebParam)
		while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0' && iBcl < TAILLE_PARAM_TRAM + iTamponDebParam)
		{
			trameSeparee.tabParam[iCptParam][cptChaine] = trameRecue[iBcl];
			cptChaine++;
			iBcl++;
			PRINTD("f5");
		}

		// Cette boucle permet d'atteindre le caractere de separation des trames, si ce n'est pas deja fait
		while (trameRecue[iBcl] != carDelim && trameRecue[iBcl] != '\0')
		{
			iBcl++;
			PRINTD("f6");
		}

		// on saute ce caractere de separation, sinon on est à la fin de la trame
		// iTamponDebParam correspond ici au premier caractere du 2eme parametre
		if (trameRecue[iBcl] != '\0')
			iTamponDebParam = ++iBcl;

		PRINTD("f7");
		iCptParam++;
	}

	PRINTD(trameSeparee.commande);
	PRINTD(trameSeparee.tabParam[0]);
	PRINTD(trameSeparee.tabParam[1]);
	PRINTD(trameSeparee.tabParam[2]);
	PRINTD("fin separation trame");

	return trameSeparee;
}

void dispatch(Robot &robot, Trame const &trameSeparee)
{
	PRINTD("start dispatch1");
	int cmd;
	int params[NB_PARAM_MAX];

	// convert to integer
	if (strcmp(trameSeparee.commande, CMD_BLANK) != 0)
		cmd = atoi(trameSeparee.commande);
	else
		cmd = PARAM_VIDE;

	for (int i = 0; i < NB_PARAM_MAX; i++)
	{
		// on test si on a pas renseigne le parametre alors on ne met pas 0 mais, on le met à PARAM_VIDE (-1)
		if (strcmp(trameSeparee.tabParam[i], PARAM_BLANK) != 0)
			params[i] = atoi(trameSeparee.tabParam[i]);
		else
			params[i] = PARAM_VIDE;
	}


	PRINTD("start dispatch");
	PRINTD("commande : ");
	PRINTD(cmd);
	PRINTD(params[0]);
	PRINTD(params[1]);
	PRINTD(params[2]);

	switch (cmd)
	{
	case MO:
		// si on ne renseigne pas les parametres alors on appel la fonction sans les parametres (les moteurs se mettent en marche)
		if (params[0] == PARAM_VIDE && params[1] == PARAM_VIDE)
		{
			robot.moteurOn();
			PRINTD("at_10");
		}
		else
		{
			robot.moteurOn(params[0], params[1]); // conversion implicite de int à bool
			PRINTD("at_11");
		}
		break;

	case MOG:
		if (params[0] == PARAM_VIDE)
		{
			robot.moteurOnG();
			PRINTD("at_12");
		}
		else
		{
			robot.moteurOnG(params[0]);
			PRINTD("bool convert :");
			PRINTD((bool)params[0]);
		}
		break;

	case MOD:
		if (params[0] == PARAM_VIDE)
			robot.moteurOnD();
		else
			robot.moteurOnD(params[0]);
		break;

	case MV:
		if (params[0] >= 0 && params[0] <= VITESSE_PRECISION && params[0] != PARAM_VIDE && params[1] >= 0 && params[1] <= VITESSE_PRECISION && params[1] != PARAM_VIDE)
			robot.moteurVitesse(params[0], params[1]);
		break;

	case MVG:
		if (params[0] >= 0 && params[0] <= VITESSE_PRECISION && params[0] != PARAM_VIDE)
			robot.moteurVitesseG(params[0]);
		break;

	case MVD:
		if (params[0] >= 0 && params[0] <= VITESSE_PRECISION && params[0] != PARAM_VIDE)
			robot.moteurVitesseD(params[0]);
		break;

	case MA:
		if (params[0] == PARAM_VIDE && params[1] == PARAM_VIDE)
			robot.moteurAvant();
		else
			robot.moteurAvant(params[0], params[1]); // conversion implicite de int à bool
		break;

	case MAG:
		if (params[0] == PARAM_VIDE)
			robot.moteurAvantG();
		else
			robot.moteurAvantG(params[0]); // conversion implicite de int à bool
		break;

	case MAD:
		if (params[0] == PARAM_VIDE)
			robot.moteurAvantD();
		else
			robot.moteurAvantD(params[0]); // conversion implicite de int à bool
		break;

	default:
		PRINTD("DEFAULT switch - error");
		break;
	}





	/*if (cmd == MO)
	{
		// si on ne renseigne pas les parametres alors on appel la fonction sans les parametres (les moteurs se mettent en marche)
		if (params[0] == PARAM_VIDE && params[1] == PARAM_VIDE)
		{
			robot.moteurOn();
			PRINTD("at_10");
		}
		else
		{
			robot.moteurOn(params[0], params[1]); // conversion implicite de string à bool
			PRINTD("at_11");
		}
	}

	else if (cmd == MOG)
	{
		if (params[0] == PARAM_VIDE)
		{
			robot.moteurOnG();
			PRINTD("at_12");
		}
		else
		{
			robot.moteurOnG(params[0]);
			PRINTD("bool convert :");
			PRINTD((bool)params[0]);
		}
	}

	else if (cmd == MOD)
	{
		if (params[0] == PARAM_VIDE)
			robot.moteurOnD();
		else
			robot.moteurOnD(params[0]);
	}

	else if (cmd == MV && params[0] >= 0 && params[0] <= 100 && params[0] != PARAM_VIDE)
	{
		robot.moteurVitesse(params[0]);
	}

	else if (cmd == MVG && params[0] >= 0 && params[0] <= 100 && params[0] != PARAM_VIDE)
	{
		robot.moteurVitesseG(params[0]);
	}

	else if (cmd == MVD && params[0] >= 0 && params[0] <= 100 && params[0] != PARAM_VIDE)
	{
		robot.moteurVitesseD(params[0]);
	}

	else if (cmd == MA)
	{
		if (params[0] == PARAM_VIDE && params[1] == PARAM_VIDE)
			robot.moteurAvant();
		else
			robot.moteurAvant(params[0], params[1]); // conversion implicite de string à bool
	}

	else if (cmd == MAG)
	{
		if (params[0] == PARAM_VIDE)
			robot.moteurAvantG();
		else
			robot.moteurAvantG(params[0]); // conversion implicite de string à bool
	}

	else if (cmd == MAD)
	{
		if (params[0] == PARAM_VIDE)
			robot.moteurAvantD();
		else
			robot.moteurAvantD(params[0]); // conversion implicite de string à bool
	}*/
}

