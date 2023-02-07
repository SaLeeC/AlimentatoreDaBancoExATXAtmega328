#include <Arduino.h>

//Caricamenti necessari per poter realizzare il reset via software
//(utilizzato quando è stata effettuata una calibrazione)
#include <avr/io.h>
#include <avr/wdt.h>
#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {}

#include <Wire.h>
#include <EEPROM.h>
#include <RotaryEncoder.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_INA219.h>

#include <Constant.h>
#include <Var.h>
#include <Sub.h>

//Serve solo in fase di messa a punto e di diagnostica
//per verificare la presenza dei dispositivi IIC operativi sul bus
#include <IICScanner.cpp>

// Setup a RotaryEncoder with 2 steps per latch for the 2 signal input pins:
//RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

// A pointer to the dynamic created rotary encoder instance.
// This will be done in setup()
RotaryEncoder *encoder = nullptr;


#include <EncoderManagement.cpp>

// This interrupt routine will be called on any change of one of the input signals
void checkPosition()
{
  encoder->tick(); // just call tick() to check the state.
}




// set the LCD address to LCDAddress for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(PCF8574_ADDR_A20_A10_A00, RS, RW, En, BackLite, D4, D5, D6, D7, POSITIVE);

#include <LCDManagement.cpp>

//Crea le istanze per i misuratori di tensione e corrente
Adafruit_INA219 INA219[NumINA219] = {{Adafruit_INA219(ina219Address[0])},
                                     {Adafruit_INA219(ina219Address[1])},
                                     {Adafruit_INA219(ina219Address[2])}};

#include <INA219Management.cpp>

#include <CalibrationManagement.cpp>

void setup() 
{
  Serial.begin(115200);//Utilizzata solo in fase di messa a punto e test

  LCDSetup();//Inizializza il display LCD

  LCDWelcomeMsg();//Presenta il messaggio di accensione

//Inizializza le istanze dei sensori tensione/corrente
  for (uint8_t ii=0; ii < NumINA219; ii++)
  {
    INA219[ii].begin();
    INA219[ii].setCalibration_vvV_aaA(RShunt[ii], VOut[0],
                                      CurrentMAX[ii], CurrentLSB[ii],
                                      VoltMAX[ii],
                                      INA219_CONFIG_BADCRES_12BIT,
                                      INA219_CONFIG_BADCRES_12BIT_16S_8510US);
  }

//Inizializza il TIMER1 in maniera che generi le chiamate per l'effetuazione delle letture 
//del campo (tensione, corrente e potenza) e il ciclo di aggiornamento del display LCD
/*Calculations : 
  System clock 16 Mhz and Prescalar 8 (CS12 0, CS11 1, CS10 0);
  Timer 1 speed = 16000khz/1   = 16000.0 Khz    
  Pulse time = 1/16000 Khz =  0.0625us  
  Count up to =  2500us /  0.0625us = 40000 (so this is the value the OCR register should have)
*/
  cli();//stop interrupts

//set timer1 interrupt at 10mS (100 campioni al secondo)
  TCCR1A = 0;// Reset entire TCCR1A to 0
  TCCR1B = 0;// Reset entire TCCR1B to 0

  TCCR1B |= (1 << CS02) | (0 << CS01) | (0 << CS00);   
  // enable timer compare interrupt
  TIMSK1 |= B00000010;
  OCR1A = 620;//Finally we set compare register A to this value  
  sei();//Enable back the interrupts
  

  pinMode(8, OUTPUT);//riferisce sullo stato di lettura dei sensori tensione/corrente
  pinMode(9, OUTPUT);//riferisce sullo stato del ciclo di aggiornamento del display LCD
  pinMode(EncoderSwitch, INPUT);//Pulsante dell'encoder
  pinMode(DebugOn, INPUT_PULLUP);


  // use TWO03 mode when PIN_IN1, PIN_IN2 signals are both LOW or HIGH in latch position.
  encoder = new RotaryEncoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(PIN_IN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_IN2), checkPosition, CHANGE);


//Test dei device IIC. Da attivare in fase di test
//  IICScann();

  //Se il pulsante è premuto in fase di accensione, al rilascio va a fare la calibrazione
  if (digitalRead(EncoderSwitch)==0)
  {
    lcd.clear();
    lcd.print(" Rilasciare per ");
    lcd.setCursor(0,1);
    lcd.print("    iniziare    ");
    while(digitalRead(EncoderSwitch)==0)
    {
    }
    Calibrate();
  }

  //Carica i valori di calibrazione nelle variabili di servizio
  ReadCalibration();

  //Informa sullo stato dello switch che attiva il Debug
  Serial.println("Debug Attivo");
}

//Reagisce alla chiamata dell'interrupt generato dal TIMER1, setta la
//variabile di servizio e azzera il TIMER per il prossimo ciclo
ISR(TIMER1_COMPA_vect)
{
  TCNT1  = 0;
  Timer1Flag=1;
  TCNT1  = 0;
}

void loop() 
{
int EncoderAppo; 

  if(UpDisplay==25)
  {
    LCDShowValue();//Presenta i valori correnti
    UpDisplay=0;//Azzera il contatore
    
    //Verifica se deve azzerare il registro dei valori di picco
    EncoderAppo = (TestEncoder(0, NumINA219));
    
    if(EncoderAppo == 1)
    {
      for(uint8_t i=0; i<NumINA219; i++)
      {
        CurrentPeakValue[i]=0;
      }
    }
  }

//Cilo di misura
  if (Timer1Flag==1)
  {
    UpdateValue();
    UpDisplay++;
    Timer1Flag=0;
  }
  
}


