#include <p24FJ64GA002.h>

#include "xc.h"
#include "stdint.h"
#include "IR_lib.h"
#include "I2C_LCD.h"
#include "asm_lib.h"
#include "LedStrip_lib.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void initPIC24(void){
    CLKDIVbits.RCDIV=0;
    AD1PCFG = 0x9FFF;
}


int main(void) {
//    IR_Setup();
    
    initPIC24();
    LedStrip_Setup();

    lcd_init();
    
        
    lcd_setCursor(0,0);
    lcd_printStr("hello,");
    
    lcd_setCursor(1,0);
    lcd_printStr("world!");
        
    delay_ms(1000);
    lcd_cmd(0b00000001); // Clear Display
    
    IR_Setup();
    TesterLEDSetup();
    LedStrip_Setup();


//    ledTest();
        
    while(1);
    return 0;
}