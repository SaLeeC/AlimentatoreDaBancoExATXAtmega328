# PowerSupplyFromATXPowerUnit
Desk power supply made using an ATX power module salvaged from an old computer.

Alimentatore da banco realizzato utilizzando un modulo di alimentazione ATX recuperato da un vecchio computer.

# Firmware
The firmware was developed with PlatformIO.
A modified version of the library developed by Adafruit was used to interface the INA219 chip.
library update request to its developer is in progress.
At the moment, to compile without errors, you must do the following:
1) Copy the project folder to your computer
2) open the "lib\Adafruit INA219-CopiaDiSecurezza" folder inside the project folder and copy its contents
3) open the ".pio\libdeps\uno\Adafruit INA219" folder and paste the copied files into it, authorizing the replacement of all files
This sequence does NOT affect other projects in your folders.
Until you upgrade the libraries this sequence will no longer be needed. 

Il firmware è stato con sviluppato con PlatformIO.
Per l'interfacciamento del chip INA219 è stata utilizzata una versione modificata della libreria sviluppata da Adafruit.
è in corso la richiesta di aggiornamento della libreria al suo sviluppatore.
Al momento per eseguire la compilazione senza errori si deve effettuare le seguenti operazioni:
1) Copiare la cartella di progetto sul vostro computer
2) aprire la cartella "lib\Adafruit INA219-CopiaDiSicurezza" all'interno della cartella di progetto e copiarne il contenuto
3) aprire la cartella ".pio\libdeps\uno\Adafruit INA219" e incollarvi dentro i file copiati autorizzando la sostituzione di tutti i file
Questa sequenza NON influenza gli altri progetti presenti nelle vostre cartelle.
Fino a quando non eseguirete l'aggiornamento delle librerie questa sequenza non sarà più necessaria.
