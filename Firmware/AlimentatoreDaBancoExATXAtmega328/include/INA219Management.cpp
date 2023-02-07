/*
Il chip INA219 ha una velocità di conversione massima (12 bit e caso più sfavorevole) di 0,6mS
ne deriva che non è opportuno campionare più di 1000 volte al secondo.
Per questa applicazione manterremo la frequenza di campionamento a 100CPS ovvero un ciclo di lettura ogni 10mS
*/

/**
 * Gestisce il ciclo di acquisizione dei valori di tensione, corrente e potenza da tutti i sensori
 * Il ciclo di lettura produce per ogni parametro tre uscite:
 * - Valore istantaneo (il valore reso dai sensori è già frutto di una media effettuata tramite
 * letture multiple gestite dal sensore stesso)
 * - Valore di picco (il valore massimo letto dall'ultimo azzeramento. L'azzeramento si ottiene 
 * agendo sul pulsante dell'encoder)
 * - Valore filtrato (ai singoli valori istantanei si applica un filtro passa basso ottenendo un valore
 * meno soggetto a sbalzi. Questo è il valore presentato come valore corrente)
*/
uint32_t UpdateValue()
{
  digitalWrite(8,HIGH);

  for(uint8_t ii=0; ii<NumINA219; ii++)
  {
    VoltageLastValue[ii] = INA219[ii].getBusVoltage_V()*KCorrection[ii];//Tensione valore istantaneo
    VoltagePeakValue[ii] = max(VoltageLastValue[ii],VoltagePeakValue[ii]);
    VoltageAverageValue[ii] = (VoltageAverageValue[ii] * (1.0-KFiltro)) + (VoltageLastValue[ii] * KFiltro);
    CurrentLastValue[ii] = (INA219[ii].getCurrent_mA() - OffsetCurrent[ii]) / 1000.0;//Corrente valore istantaneo
    //Se non è richiesto i valori negativi di corrente non vengono memorizzati e non vengono sottoposti al filtro
    if ((CurrentLastValue[ii]<0) && (ShowNegativeCurrent==0))
    {
      CurrentLastValue[ii]=0;
    }
    CurrentPeakValue[ii] = max(CurrentLastValue[ii],CurrentPeakValue[ii]);
    CurrentAverageValue[ii] = (CurrentAverageValue[ii] * (1.0-KFiltro)) + (CurrentLastValue[ii] * KFiltro);
    //Potenza valore istantaneo
    //la potenza è corretta per il fattore di correzione della tensione ma NON per la compensazione di corrente
    PowerLastValue[ii] = (INA219[ii].getPower_mW() - (VoltageLastValue[ii]*OffsetCurrent[ii])) / 1000.0;
    //I valori di potenza negativa non vengono memorizzati ne contribuiscono agli altri calcoli
    if (PowerLastValue[ii]<0)
    {
      PowerLastValue[ii]=0;
    }
    PowerPeakValue[ii] = max(PowerLastValue[ii],PowerPeakValue[ii]);
    PowerAverageValue[ii] = (PowerAverageValue[ii] * (1.0-KFiltro)) + (PowerLastValue[ii] * KFiltro);
  }

  digitalWrite(8,LOW);

  return(0);

}