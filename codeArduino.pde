//#include <Metro.h>
#include "Communication.h"


#define BLUETOOTH Serial1
#define DELAY_UPDATE_CAPTEUR 1
#define TAILLE_BUF 75

//static unsigned long int iTempsEnvoieCapteur = 0;
static Temporisation tempoUpdateCapt;


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

	////Réception Android
	//static char strEnvoiCapteurs[TAILLE_BUF] = "_________";
	//static int iBclReception = 0;
	//static int iCpt = 0;
	//static int iBcl;
	//static char strTrame[TAILLE_BUF] = "_________";

	//if (BLUETOOTH.available() > 0)
	//{
	//	strTrame[iBclReception] = BLUETOOTH.read(); //lecture caractère par caractère
	//	if (strTrame[iBclReception] == '\0')
	//	{
	//		strTrame[iBclReception] = '\0';
	//		Serial.print("Mobile : ");
	//		Serial.println(strTrame);
	//		iBclReception = 0;

	//	}
	//	else {
	//		iBclReception++;
	//	}
	//}
	////Envoie des infos capteurs toute les DELAY_UPDATE_CAPTEUR ms
	//if (/*(iTempsEnvoieCapteur + DELAY_UPDATE_CAPTEUR) < millis()*/tempoUpdateCapt.finTempo())
	//{
	//	//Envoie
	//	Serial.print("Robot :");
	//	Serial.println(iCpt);
	//	sprintf(strEnvoiCapteurs, "%d", iCpt);

	//	iBcl = -1;
	//	do
	//	{
	//		iBcl++;
	//		BLUETOOTH.write(strEnvoiCapteurs[iBcl]);

	//	} while (strEnvoiCapteurs[iBcl] != '\0');

	//	//iTempsEnvoieCapteur = millis();
	//	tempoUpdateCapt.demTempo();
	//	iCpt++;
	//}

	DDRB = BIT5;
	PORTB = BIT5;

	traitementRecep("ffd,abcf,defg");

	delay(2000);
}

