//#include <Metro.h>
#include "Communication.h"
#include "Robot.h"


#define BLUETOOTH Serial1
#define DELAY_UPDATE_CAPTEUR 100
#define TAILLE_BUF TAILLE_TRAME_A_TRAITER_TOT

//static unsigned long int iTempsEnvoieCapteur = 0;
static Temporisation tempoUpdateCapt;

Robot monRobot;


void setup()
{
	//Initialisation de la liaison série pour le debuggage
	Serial.begin(115200);
	//Initialisation du bluetooth
	BLUETOOTH.begin(9600);

	//iTempsEnvoieCapteur = millis();
	tempoUpdateCapt = Temporisation(DELAY_UPDATE_CAPTEUR);
	tempoUpdateCapt.demTempo();

}

void loop()
{
	//Réception Android
	static char strEnvoiCapteurs[TAILLE_BUF] = "";
	static int iBclReception = 0;
	Trame maTrame;

	static int iCpt = 0;
	static int iBcl;
	static char strTrame[TAILLE_BUF] = "_________";

	// Il faudra mettre la lecture des donnees dans une fonction readBluetooth -------------------------------------------------------
	if (BLUETOOTH.available() > 0)
	{
		strTrame[iBclReception] = BLUETOOTH.read(); //lecture caractère par caractère
		if (strTrame[iBclReception] == '\0')
		{
			strTrame[iBclReception] = '\0';
			Serial.print("Mobile : ");
			Serial.println(strTrame);
			iBclReception = 0;

			// La trame est complete
			maTrame = traitementRecep(strTrame);
			dispatch(monRobot, maTrame);
		}
		else {
			iBclReception++;
		}
	}


	//Envoie des infos capteurs toute les DELAY_UPDATE_CAPTEUR ms
	if (tempoUpdateCapt.finTempo())
	{
		//Envoie
		Serial.print("Robot :");
		Serial.println(iCpt);
		sprintf(strEnvoiCapteurs, "%d", iCpt);

		iBcl = -1;
		do
		{
			iBcl++;
			BLUETOOTH.write(strEnvoiCapteurs[iBcl]);

		} while (strEnvoiCapteurs[iBcl] != '\0');


		tempoUpdateCapt.demTempo();
		iCpt++;
	}
}

