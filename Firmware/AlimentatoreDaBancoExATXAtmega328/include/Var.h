//=========================================================
// sistema
//=========================================================

uint16_t EEPromAddress = EEPromStartAddress;
uint16_t EEPromAddressStep = sizeof(float);


String Help[RigheHelp] = {"  TESTO  GUIDA  ",
                          "Usa l'Encoder   ",
                          "per scorrere il ",
                          "testo. Premi per",
                          "     avanzare   ",
                          "  CALIBRAZIONE  "
                          "Usa l'encoder   ",
                          "per calibrare i ",
                          "valori e premi  ",
                          "per passare al  ",
                          "prossimo  valore",
                          "Per procedere   ",
                          "sono necessari  ",
                          "un multimetro e ",
                          "un carico       "};

uint8_t ShowNegativeCurrent=0;
//=========================================================
// sistema
//=========================================================

uint8_t ina219Address[NumINA219] = {INA219_Address33,
                                    INA219_Address5,
                                    INA219_Address12};
float RShunt[NumINA219]          = {RShunt33,
                                    RShunt5,
                                    RShunt12};
uint16_t VOut[NumINA219]       = {VShunt33,
                                    VShunt5,
                                    VShunt12};
uint8_t CurrentMAX[NumINA219]    = {CurrentMAX33,
                                    CurrentMAX5,
                                    CurrentMAX12};
uint8_t CurrentLSB[NumINA219]    = {CurrentLSB33,
                                    CurrentLSB5,
                                    CurrentLSB12};
uint8_t VoltMAX[NumINA219]       = {Volt33,
                                    Volt5,
                                    Volt12};
float KCorrection[NumINA219]     = {KCorrectionV33,
                                    KCorrectionV5,
                                    KCorrectionV12};
float OffsetCurrent[NumINA219]   = {OffsetCurrentV33,
                                    OffsetCurrentV5,
                                    OffsetCurrentV12};
float CurrentLastValue[NumINA219];
float VoltageLastValue[NumINA219];
float PowerLastValue[NumINA219];

float CurrentPeakValue[NumINA219];
float VoltagePeakValue[NumINA219];
float PowerPeakValue[NumINA219];

float CurrentAverageValue[NumINA219];
float VoltageAverageValue[NumINA219];
float PowerAverageValue[NumINA219];

float shuntvoltage = 0;
float busvoltage = 0;
float current_A = 0;
float loadvoltage = 0;
uint32_t power_mW = 0;


uint16_t Timer1Flag;
uint8_t     UpDisplay=0;

uint32_t TZero = micros();
uint32_t TUno = micros();
char LCDBuff0[32] = {LCDBackPlaneRow0};

//Variabile di servizio per appoggiare il carattere da controllare rispetto al buffer display
  char Buff;


//=========================================================
// encoder
//=========================================================

int EncoderPointer=0;

int newPos;
int EncoderPos = 0;

