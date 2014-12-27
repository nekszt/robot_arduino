#include "Fonctions.h"

const uint8_t BIT0(0x01);
const uint8_t BIT1(0x02);
const uint8_t BIT2(0x04);
const uint8_t BIT3(0x08);
const uint8_t BIT4(0x10);
const uint8_t BIT5(0x20);
const uint8_t BIT6(0x40);
const uint8_t BIT7(0x80);

void resetPortDir()
{
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	DDRE = 0x00;
	DDRF = 0x00;
}


bool readTBluetooth(char trame[], const int iTaille)
{
	static int iBclReception = 0;
	bool endRead = false;

	if (BLUETOOTH.available() > 0)
	{
		trame[iBclReception] = BLUETOOTH.read(); //lecture caractère par caractère
		if (trame[iBclReception] == '\0')
		{
			//trame[iBclReception] = '\0';
			PRINTD("Mobile :");
			PRINTD(trame);

			iBclReception = 0;

			// La trame est complete
			PRINTD("trame complete");
			endRead = true;
		}
		else if (++iBclReception == iTaille - 1 && trame[iBclReception] != '\0') // si on est pas a la fin de la trame on incremente iBcl
		{
			PRINTD("deborde");
			trame[iBclReception] = '\0';

			PRINTD("Mobile :");
			PRINTD(trame);

			iBclReception = 0;

			// La trame est complete
			PRINTD("trame complete");
			endRead = true;
		}
	}

	return endRead;
}

void sendTBluetooth(char trame[], const int iTaille)
{
	int iBcl = 0;

	//Envoie
	PRINTD("Robot :");
	PRINTD(trame);

	while (trame[iBcl] != '\0' && iBcl < (iTaille -1))
	{
		BLUETOOTH.write(trame[iBcl]);
		iBcl++;
	}
	BLUETOOTH.write('\0');
}


/* Attention si on utilise cette fonction ou si on utilise analogWrite,
*  Cette derniere fonction utilise le timer 4 sur la pin 13
*  Il faut penser a remettre une vitesse correcte sur les moteurs (registres de comparaison)
*/
void blinkLedBlock(const int pin, const int times, const int speedMS)
{
	for (int i = 0; i < times; i++)
	{
		for (int j = 0; j <= 250; j += 25)
		{
			analogWrite(pin, j);
			_delay_ms(speedMS);
		}

		for (int j = 250; j >= 0; j -= 25)
		{
			analogWrite(pin, j);
			_delay_ms(speedMS);
		}
	}
}


// call in setup() at the beginning
void WDT_stop()
{
	cli(); // disable interrupts, SREG-I = 0

	wdt_reset();
	MCUSR &= ~BIT3; // clear the WDRF (Watchdog Reset Flag when the Arduino is reseted)
	WDTCSR |= BIT4 | BIT3; // set WDCE (4 clock cycle to change prescaler and WDE)
	WDTCSR = 0x00; // clear the WDE (BIT3) (reset interruption)

	sei();
}

void WDT_start()
{
	cli(); // disable interrupts, SREG-I = 0

	wdt_reset();
	WDTCSR |= BIT4 | BIT3; // set WDCE
	WDTCSR = BIT6 | BIT2; // change prescaler

	sei(); // enable interrupts, SREG-I = 1
}

