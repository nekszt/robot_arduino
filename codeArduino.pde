//#include <Metro.h>
#include "Robot.h"
#include "Communication.h"

/* La vitesse du robot a ete mesuree a 33.3 cm.s^-1, soit 0.33 m.s^-1, soit 1.2 km.h^-1
*  Sachant que l'on détecte un obstacle à 15 - 20 cm, le programme doit etre plus rapide que
*  (15cm) 450ms
*/



#define DELAY_UPDATE_CAPTEUR 140
#define TAILLE_BUF TAILLE_TRAME_A_TRAITER_TOT


static Temporisation *tempoUpdateCapt;

static Robot *monRobot;

int iCptTimeOut;


void setup()
{
	WDT_stop();

	//Initialisation de la liaison série pour le debuggage
	Serial.begin(115200);

	//Initialisation du bluetooth
	BLUETOOTH.begin(9600);

	delay(700);


	resetPortDir();
	delay(50);

	monRobot = new Robot();
	delay(50);
	PRINTD("robot initialized");

	/*tempoUpdateCapt = new Temporisation(DELAY_UPDATE_CAPTEUR);
	tempoUpdateCapt->demTempo();*/


	iCptTimeOut = 0;

	// blink led to show end initialization
	//blinkLedBlock(13, 3, 70);
	PRINTD("arduino initialized");
	delay(300);

	// WD time out 250ms, but time out is ~290ms
	WDT_start();
}

void loop()
{
	static char strTrame[TAILLE_BUF] = "                    ";


	// lecture des entrees
	// on lit les capteurs
	monRobot->CapteurArriere(100);
	monRobot->CapteurDroit(100);
	monRobot->CapteurGauche(100);

	
	// on lit les trames puis on les traitent
	if (readTBluetooth(strTrame, TAILLE_BUF)) // si la trame est complete
	{
		Trame maTrame;
		maTrame = traitementRecep(strTrame);
		dispatch(*monRobot, maTrame);
	}


	sendCapteurs(*monRobot);



	wdt_reset();
}


ISR(WDT_vect)
{
	WDT_stop();
	
	iCptTimeOut++;
	PRINTD("watchdog - time out :");
	PRINTD(iCptTimeOut);

	// blink quickly on led pin 13
	blinkLedBlock(13, 10, 20);

	// on reset le robot
	*monRobot = Robot();

	WDT_start();
}

