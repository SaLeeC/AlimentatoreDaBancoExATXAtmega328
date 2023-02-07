//Gestisce l'encoder


/**Gestisce il funzionamento dell'encoder
 * definendo il range reso nella variabile EncoderPointer
 * (min -> valore minimo, Max -> valore massimo
 * In uscita rende lo stato del pulsante
*/
int TestEncoder(int min, int Max)
{
  int SwitchStatus = 0;
  
//  encoder.tick(); // just call tick() to check the state.
  encoder->tick(); // just call tick() to check the state.
  
//  EncoderPointer =+ encoder.getPosition();
  EncoderPointer =+ encoder->getPosition();
  if (EncoderPointer >= Max) 
  {
    EncoderPointer = min;
//    encoder.setPosition(EncoderPointer);
    encoder->setPosition(EncoderPointer);
  }
  if (EncoderPointer < min) 
  {
    EncoderPointer = Max;
   // encoder.setPosition(EncoderPointer);
    encoder->setPosition(EncoderPointer);
  }

  /**Controlla lo stato del pulsante dell'encoder e rimane
   * in attesa che venga rilasciato
  */ 
  while (digitalRead(EncoderSwitch)==0)
  {
    SwitchStatus=1;
  }
  if (digitalRead(DebugOn) == 0)
  {
    Serial.print("Encoder ");
    Serial.println(EncoderPointer);
  }

  return(SwitchStatus);
}

/**Inizializza l'encoder con il valore utile alla funzione che lo sta utilizzando
*/
void InitEncoder(int ThisPoint)
{
//  encoder.setPosition(ThisPoint);
  encoder->setPosition(EncoderPointer);
}