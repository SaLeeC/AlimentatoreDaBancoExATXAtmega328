//Gestisce la calibrazione degli INA219

//Legge i valori salvati nella EEPROM interna al microcontrollore
//relativi alle calibrazioni e li mette nelle variabili di servizio
//Se i valori NON sono presenti o sono corrotti lancia il processo
//di calibrazione
void ReadCalibration()
{
  Serial.println("Read Calibration");

  EEPromAddress = EEPromStartAddress;

  for (uint8_t ii=0; ii<NumINA219; ii++)
  {
    KCorrection[ii] = TestNAN();
    EEPromAddress += EEPromAddressStep;
    OffsetCurrent[ii] = TestNAN();
    EEPromAddress += EEPromAddressStep;
  }
}

//Gestisce il processo di calibrazione.
//Questo processo è chiamato in automatico se la EEPROM è vuota
//o se i valori salvati sono danneggiati oppure può essere
//chiamato dall'operatorepremento tenedo premuto l'encoder durante
//la fase di avvio
void Calibrate()
{
  //Presenta le istruzioni per l'esecuzione della calibrazione
  ShowHelp();

  int16_t AppoEncoder = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Cal. V 3.3   ");

  EEPromAddress = EEPromStartAddress;
  //Calibra i 3.3 volt
  CalVolt(0);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cal. ZERO I 3.3");

  EEPromAddress += EEPromAddressStep;
  //Calibra lo zero della I dei 3.3 volt
  CalZeroI(0);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Cal. V 5   ");

  EEPromAddress += EEPromAddressStep;
  //Calibra i 3.3 volt
  CalVolt(1);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cal. ZERO I 5");

  EEPromAddress += EEPromAddressStep;
  //Calibra lo zero della I dei 3.3 volt
  CalZeroI(1);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Cal. V 12   ");

  EEPromAddress += EEPromAddressStep;
  //Calibra i 3.3 volt
  CalVolt(2);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cal. ZERO I 12");

  EEPromAddress += EEPromAddressStep;
  //Compensa lo zero della I dei 12 volt
  CalZeroI(2);

  //Completato il ciclo di calibrazione riavvia il controllore
  Reset_AVR();//Reset il controller
}

//Verifica se nella EEPROM è contenuto un numero o un Non Numero (nan)
//Nel caso di Non Numero esegue la calibrazione in maniera forzata
//Restituisce il valore letto se è valido 
float TestNAN()
{
  float Appo=0;

  EEPROM.get(EEPromAddress,Appo);
  if (!(Appo == Appo))
  {
    Calibrate();
  }
  return (Appo);
}


//Gestione della calibrazione dei voltmetri
void CalVolt(uint8_t indice)
{
  KCorrection[indice]=1;
  EncoderPointer = KCorrection[indice] * 100.0;
  InitEncoder(EncoderPointer);

  while((TestEncoder(-10000,10000))==0)
  { 
    UpdateValue();
    KCorrection[indice] = float(EncoderPointer/100.0);  
    lcd.setCursor(0,1);
    lcd.print("          ");
    lcd.setCursor(0,1);
    lcd.print(VoltageAverageValue[indice],3);
    delay(10);
  }
  EEPROM.put(EEPromAddress,KCorrection[indice]);
}

//Gestione della compensazione dello zero del sensore della corrente
void CalZeroI(uint8_t indice)
{
  OffsetCurrent[indice]=0;
  EncoderPointer = OffsetCurrent[indice];
  InitEncoder(EncoderPointer);
  //Sblocca la presentazione dei valori negativi di corrente
  //Normalmente i valori negativi della corrente NON sono presntati.
  //In fase di azzeramento devono essere visibili
  ShowNegativeCurrent=1;
  while((TestEncoder(-600,600))==0)
  { 
    UpdateValue();
    OffsetCurrent[indice] = float(EncoderPointer);  
    lcd.setCursor(0,1);
    lcd.print("          ");
    lcd.setCursor(0,1);
    int appo1 = (int(CurrentAverageValue[indice]*1000.0)/5)*5;
    lcd.print(appo1);
    delay(10);
  }
  EEPROM.put(EEPromAddress,OffsetCurrent[indice]);
}