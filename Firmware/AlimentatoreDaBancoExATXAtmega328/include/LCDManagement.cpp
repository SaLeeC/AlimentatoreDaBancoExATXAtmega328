

/**
 * Inizializza il display LCD
*/
void LCDSetup()
{
//Prepara i sei "pacman" che presenteranno il messaggio di apertura e il simbolo freccia per la corrente di picco
  uint8_t LCDSprite1[8] = {PacMan00, PacMan01, PacMan02, PacMan03, PacMan04, PacMan05, PacMan06, PacMan07};
  uint8_t LCDSprite2[8] = {PacMan10, PacMan11, PacMan12, PacMan13, PacMan14, PacMan15, PacMan16, PacMan17};
  uint8_t LCDSprite3[8] = {PacMan20, PacMan21, PacMan22, PacMan23, PacMan24, PacMan25, PacMan26, PacMan27};
  uint8_t LCDSprite4[8] = {PacMan30, PacMan31, PacMan32, PacMan33, PacMan34, PacMan35, PacMan36, PacMan37};                          
  uint8_t LCDSprite5[8] = {PacMan40, PacMan41, PacMan42, PacMan43, PacMan44, PacMan45, PacMan46, PacMan47};
  uint8_t LCDSprite6[8] = {PacMan50, PacMan51, PacMan52, PacMan53, PacMan54, PacMan55, PacMan56, PacMan57};
  uint8_t LCDSprite7[8] = {UpArrow00, UpArrow01, UpArrow02, UpArrow03, UpArrow04, UpArrow05, UpArrow06, UpArrow07};
//Inizializza il display
  lcd.begin(COLUMS, ROWS, LCD_5x8DOTS);
//Accende il retroilluminatore
  lcd.backlight();
  lcd.clear();

//Carica nella memoria del display i sei "pacman" e il simbolo freccia per la corrente di picco
  lcd.createChar(0,LCDSprite1);
  lcd.createChar(1,LCDSprite2);
  lcd.createChar(2,LCDSprite3);
  lcd.createChar(3,LCDSprite4);
  lcd.createChar(4,LCDSprite5);
  lcd.createChar(5,LCDSprite6);
  lcd.createChar(6,LCDSprite7);
}

/**
 * Presenta il messaggio di apertura
*/
void LCDWelcomeMsg()
{
  lcd.clear();

//Carica la prima riga
  lcd.setCursor(0,0);
  lcd.write(0);
  delay(PacManDelay);

  for(uint8_t ii=0; ii<4; ii++)
  {
    lcd.setCursor(0+(ii*4),0);
    lcd.write(LCDWelcomeT1[0+(ii*4)]);
    lcd.write(1);
    delay(PacManDelay);
  
    lcd.setCursor(1+(ii*4),0);
    lcd.write(LCDWelcomeT1[1+(ii*4)]);
    lcd.write(2);
    delay(PacManDelay);
  
    lcd.setCursor(2+(ii*4),0);
    lcd.write(LCDWelcomeT1[2+(ii*4)]);
    lcd.write(1);
    delay(PacManDelay);
  
    lcd.setCursor(3+(ii*4),0);
    lcd.write(LCDWelcomeT1[3+(ii*4)]);
    lcd.write(0);
    delay(PacManDelay);
  }

  //Carica la seconda riga
  lcd.setCursor(15,1);
  lcd.write(3);
  delay(PacManDelay);

  for(uint8_t ii=4; ii>0; ii--)
  {
    lcd.setCursor(3+((ii-1)*4),1);
    lcd.write(LCDWelcomeT2[3+((ii-1)*4)]);
    lcd.setCursor(2+((ii-1)*4),1);
    lcd.write(4);
    delay(PacManDelay);
  
    lcd.setCursor(2+((ii-1)*4),1);
    lcd.write(LCDWelcomeT2[2+((ii-1)*4)]);
    lcd.setCursor(1+((ii-1)*4),1);
    lcd.write(5);
    delay(PacManDelay);
  
    lcd.setCursor(1+((ii-1)*4),1);
    lcd.write(LCDWelcomeT2[1+((ii-1)*4)]);
    lcd.setCursor(0+((ii-1)*4),1);
    lcd.write(4);
    delay(PacManDelay);
  
    lcd.setCursor(0+((ii-1)*4),1);
    lcd.write(LCDWelcomeT2[0+((ii-1)*4)]);
    if(ii>1)
    {
      lcd.setCursor(-1+((ii-1)*4),1);
      lcd.write(3);
    }
    delay(PacManDelay);
  }

  delay(LCDWelcomeDelay);

//Carica la grafica di presentazione dei valori
  lcd.setCursor(0,0);
  for(uint8_t cursor=0; cursor<16; cursor++)
  {
    lcd.print(LCDBuff0[cursor]);
  }
  lcd.setCursor(0,1);
  for(uint8_t cursor=16; cursor<32; cursor++)
  {
    lcd.print(LCDBuff0[cursor]);
  }
  lcd.setCursor(9,1);
  lcd.write(6);

}

/**
 * Presenta i valori di tensione, corrente e potenza
 * questa routines ha la caratteristica di aggiornare sul display SOLO i 
 * caratteri che sono cambiati
*/
void LCDShowValue()
{
  digitalWrite(9,HIGH);
  //Aggiorna SOLO i caratteri del display che sono cambiati
  if((VoltageAverageValue[EncoderPointer]>0) && (LCDBuff0[0] != "+"))
  {
    lcd.setCursor(0,0);
    lcd.print("+");
  }
  if ((VoltageAverageValue[EncoderPointer]<0) && (LCDBuff0[0] != "-"))
  {
    lcd.setCursor(0,0);
    lcd.print("-");
  }
  //Setta le decine della tensione
  Buff = char((int(VoltageAverageValue[EncoderPointer]/10))+48);
  if(Buff != LCDBuff0[1])
  {
    LCDUpdateBuffer(1,0,1);
  }
  //Setta le unità della tensione
  Buff = char((int(VoltageAverageValue[EncoderPointer])%10)+48);
  if((Buff) != LCDBuff0[2])
  {
    LCDUpdateBuffer(2,0,2);
  }
  //Setta i decimi della tensione
  Buff = char((int(VoltageAverageValue[EncoderPointer]*10)%10)+48);
  if(Buff != LCDBuff0[4])
  {
    LCDUpdateBuffer(4,0,4);
  }
  //Setta le decine della corrente media
  Buff = char((int(CurrentAverageValue[EncoderPointer]/10))+48);
  if(Buff != LCDBuff0[10])
  {
    LCDUpdateBuffer(10,0,10);
  }
  //Setta le unità della corrente media
  Buff = char((int(CurrentAverageValue[EncoderPointer])%10)+48);
  if((Buff) != LCDBuff0[11])
  {
    LCDUpdateBuffer(11,0,11);
  }
  //Setta i decimi della corrente media
  Buff = char((int(CurrentAverageValue[EncoderPointer]*10)%10)+48);
  if(Buff != LCDBuff0[13])
  {
    LCDUpdateBuffer(13,0,13);
  }
  //Setta i centesimi della corrente media
  Buff = char((int(CurrentAverageValue[EncoderPointer]*100)%10)+48);
  if(Buff != LCDBuff0[14])
  {
    LCDUpdateBuffer(14,0,14);
  }
  //Setta le centinaia della potenza
  Buff = char((int(PowerAverageValue[EncoderPointer]/100))+48);
  if(Buff != LCDBuff0[16])
  {
    LCDUpdateBuffer(0,1,16);
  }
  //Setta le decine della potenza
  Buff = char((int(PowerAverageValue[EncoderPointer]/10))+48);
  if(Buff != LCDBuff0[17])
  {
    LCDUpdateBuffer(1,1,17);
  }
  //Setta le unità della potenza
  Buff = char((int(PowerAverageValue[EncoderPointer])%10)+48);
  if((Buff) != LCDBuff0[18])
  {
    LCDUpdateBuffer(2,1,18);
  }
  //Setta i decimi della potenza
  Buff = char((int(PowerAverageValue[EncoderPointer]*10)%10)+48);
  if(Buff != LCDBuff0[20])
  {
    LCDUpdateBuffer(4,1,20);
  }
  //Setta le decine della corrente di picco
  Buff = char((int(CurrentPeakValue[EncoderPointer]/10))+48);
  if(Buff != LCDBuff0[26])
  {
    LCDUpdateBuffer(10,1,26);
  }
  //Setta le unità della corrente corrente di picco
  Buff = char((int(CurrentPeakValue[EncoderPointer])%10)+48);
  if((Buff) != LCDBuff0[27])
  {
    LCDUpdateBuffer(11,1,27);
  }
  //Setta i decimi della corrente di picco
  Buff = char((int(CurrentPeakValue[EncoderPointer]*10)%10)+48);
  if(Buff != LCDBuff0[29])
  {
    LCDUpdateBuffer(13,1,29);
  }
  //Setta i centesimi della corrente di picco
  Buff = char((int(CurrentPeakValue[EncoderPointer]*100)%10)+48);
  if(Buff != LCDBuff0[30])
  {
    LCDUpdateBuffer(14,1,30);
  }
//Stampa la freccia per la corrente di picco
  lcd.setCursor(9,1);
  lcd.write(6);
}

/**
 * Carica il carattere da aggiornare nel display e aggiorna il buffer locale del display
*/
void LCDUpdateBuffer(uint8_t colonna, uint8_t riga, uint8_t posizione)
{
        lcd.setCursor(colonna,riga);
        lcd.print(Buff);
        LCDBuff0[posizione] = Buff;
}

/**
 * Presenta la guida per effettuare lòa calibrazione
 * Si tratta di un testo presentato in due parti, la prima dice come muoversi nel testo 
 * e avanzare nell'attività, la seconda da informazioni sulla calibrazione vera e propria 
*/
void ShowHelp()
{
  uint8_t AppoEncoder = 255;
  int start = 0;
  int stop = 4;

  for(uint8_t xx=0; xx<2; xx++)
  {
    while((TestEncoder(start,stop))==0)
    { 
        if(AppoEncoder != EncoderPointer)
        {   
          lcd.clear();
          lcd.print(Help[EncoderPointer]);
          lcd.setCursor(0,1);
          lcd.print(Help[EncoderPointer+1]);
          if(EncoderPointer+1<RigheHelp)
          {
            lcd.print(Help[EncoderPointer+1]);
          }
          AppoEncoder = EncoderPointer;
        }
    }
    start = 5;
    stop = 14;
  }

}
