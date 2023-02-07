#include "Arduino.h"

//===============================================================
//Generali
//===============================================================

uint32_t UpdateValue();
void IntSetup();
ISR(TIMER0_COMPA_vect);


void IICScann();

void ReadCalibration();
void Calibrate();
float TestNAN();
void ShowHelp();
void CalVolt(uint8_t indice);
void CalZeroI(uint8_t indice);

uint8_t TestEncoder(uint8_t min, uint8_t Max);
void InitEncoder(int ThisPoint);

void checkPosition();

//===============================================================
//Display IIC 20x2
//===============================================================

void LCDSetup();
void LCDWelcomeMsg();
void LCDShowValue();

void AnalogSetup();
void CurrentRead();

void LCDUpdateBuffer(uint8_t colonna, uint8_t riga, uint8_t posizione);