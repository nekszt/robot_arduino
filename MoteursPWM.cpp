#include"MoteursPWM.h"


/***********************************
		FONCTION INIT
***********************************/
void InitPort(void){
	DDRC = 0b01000000;
	DDRD = 0b10010000;
	DDRE = 0b01000000;
	DDRF = 0x00;
}

void InitPWM(void){
	//MOTEUR DROIT (2) Timer 4 
	TCCR4A = 0b00000010;
	TCCR4B = 0b00001110;
	TCCR4C = 0b00001001;
	TCCR4D = 0b00000000;
	TCCR4E = 0b00100000;
	//OCR4D = 0; <---Registre de comparaison

	//MOTEUR GAUCHE (1) Timer3
	TCCR3A = 0b10000001;
	TCCR3B = 0b00001101;
	TCCR3C = 0b00000000;
	//OCR3AL = 0; <---Registre de comparaison
}
/***********************************
		CONTROLE MOTEURS
***********************************/
void MoteurGauche(int iAlpha, bool bSens){
	if(bSens == 1){
		PORTD = PORTD | BIT4;
	}
	if(bSens == 0){
		PORTD = PORTD &~BIT4;
	}

	iAlpha = iAlpha*2.55;
	OCR3AL = iAlpha;
}


void MoteurDroit(int iAlpha, bool bSens){
	if(bSens == 1){
		PORTE = PORTE | BIT6;
	}
	if(bSens == 0){
		PORTE = PORTE &~ BIT6;
	}

	iAlpha = iAlpha*2.55;
	OCR4D = iAlpha;
}





/***********************************
		CAPTEURS INFRA-ROUGE
***********************************/
bool CapteurArriere(void){
	//PF4
	bool bTest = 0;
	bTest = ((PINF & BIT4) == BIT4);
	bTest = !bTest;
	return bTest;
}

bool CapteurGauche(void){
	//PF5
	bool bTest = 0;
	bTest = ((PINF & BIT5) == BIT5);
	bTest = !bTest;
	return bTest;
}

bool CapteurDroit(void){
	//PF1
	bool bTest = 0;
	bTest = ((PINF & BIT1) == BIT1);
	return bTest;
}



/***********************************
		FONCTIONS TEST
***********************************/
void Test(void){
	//MOTEUR DROIT
	PORTD = PORTD | BIT7;
	PORTE = PORTE | BIT6;
	//MOTEUR GAUCHE
	PORTD = PORTD | BIT4;
	PORTC = PORTC | BIT6;
}