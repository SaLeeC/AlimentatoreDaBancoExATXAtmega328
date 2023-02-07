

//===============================================================
//Costanti di sistema
//===============================================================
#define EEPromStartAddress 0x0000

#define RigheHelp 15

#define TMinCiclo 1000 //Microsecondi
#define CPS 400.0
#define FTaglio 1.0
//#define KFiltro (FTaglio/CPS)
#define KFiltro 0.05

#define DebugOn 9
//===============================================================
//Costanti INA219_33
//===============================================================

//3.3 volt 30A -> 
#define NumINA219 3
#define DefaultKConvCurrentCalibration 0.04096

#define INA219_Address33 0x40
#define KCorrectionV33 1.35// K
#define OffsetCurrentV33 60// K
#define Volt33 16// V
#define CurrentMAX33 30
#define CurrentLSB33 1// mA
#define RShunt33 0.00265// Ohm
#define VShunt33 80

#define INA219_Address5 0x41
#define KCorrectionV5 1.45// K
#define OffsetCurrentV5 80// K
#define Volt5 16// V
#define CurrentMAX5 30
#define CurrentLSB5 1// mA
#define RShunt5 0.00265// Ohm
#define VShunt5 80

#define INA219_Address12 0x42
#define KCorrectionV12 1.015// K
#define OffsetCurrentV12 140// K
#define Volt12 16// V
#define CurrentMAX12 22
#define CurrentLSB12 1// mA
#define RShunt12 0.00265// Ohm
#define VShunt12 80


//===============================================================
//Costanti LCD
//===============================================================

//Il valore assegnato alle costanti NON è il pin o il bit della porta ma
//è un valore simbolico il quale, posizionato nelle otto posizioni dopo 
//l'indirizzo, indica alla libreria il ruolo del bit
#define RS 4
#define RW 5
#define En 6

#define D4 11
#define D5 12
#define D6 13
#define D7 14

#define BackLite 16

#define COLUMS           16   //LCD columns
#define ROWS             2    //LCD rows
#define LCD_SPACE_SYMBOL 0x20 //space symbol from LCD ROM, see p.9 of GDM2004D datasheet

#define LCDWelcomeT1 " NutriMento ATX "
#define LCDWelcomeT2 "Firm.r2  Hard.r0"

#define LCDBackPlaneRow0 "+00.0V    00.00A000.0W   ^00.00A"
#define LCDBackPlaneRow1 "000.0W   ^00.00A"

#define LCDWelcomeDelay 5000

#define PacMan00 0x04
#define PacMan01 0x0A
#define PacMan02 0x11
#define PacMan03 0x11
#define PacMan04 0x17
#define PacMan05 0x11
#define PacMan06 0x11
#define PacMan07 0x0E

#define PacMan10 0x04
#define PacMan11 0x0A
#define PacMan12 0x11
#define PacMan13 0x13
#define PacMan14 0x14
#define PacMan15 0x13
#define PacMan16 0x11
#define PacMan17 0x0E

#define PacMan20 0x04
#define PacMan21 0x0A
#define PacMan22 0x13
#define PacMan23 0x14
#define PacMan24 0x18
#define PacMan25 0x14
#define PacMan26 0x13
#define PacMan27 0x0E

#define PacMan30 0x04
#define PacMan31 0x0A
#define PacMan32 0x11
#define PacMan33 0x11
#define PacMan34 0x1D
#define PacMan35 0x11
#define PacMan36 0x11
#define PacMan37 0x0E

#define PacMan40 0x04
#define PacMan41 0x0A
#define PacMan42 0x11
#define PacMan43 0x19
#define PacMan44 0x05
#define PacMan45 0x19
#define PacMan46 0x11
#define PacMan47 0x0E

#define PacMan50 0x04
#define PacMan51 0x0A
#define PacMan52 0x19
#define PacMan53 0x05
#define PacMan54 0x03
#define PacMan55 0x05
#define PacMan56 0x19
#define PacMan57 0x0E

#define UpArrow00 0x04
#define UpArrow01 0x0E
#define UpArrow02 0x15
#define UpArrow03 0x04
#define UpArrow04 0x04
#define UpArrow05 0x04
#define UpArrow06 0x04
#define UpArrow07 0x04

#define PacManDelay 250


//===============================================================
//Costanti Encoder
//===============================================================

#define PIN_IN1 2
#define PIN_IN2 3
#define EncoderSwitch 4