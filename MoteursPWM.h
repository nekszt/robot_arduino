#include <Arduino.h>

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80


void InitPort(void);
void InitPWM(void);
void Test(void);

void MoteurGauche(int iAlpha, bool bSens);
void MoteurDroit(int iAlpha, bool bSens);


bool CapteurArriere(void);
bool CapteurGauche(void);
bool CapteurDroit(void);

