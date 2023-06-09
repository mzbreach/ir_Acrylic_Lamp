/* 
 * File:   IR_lib.c
 * Project: IR Acrylic Lamp
 */

#include "xc.h"
#include "IR_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "I2C_LCD.h"
#include "LedStrip_lib.h"

volatile unsigned long long int overflow = 0;
volatile unsigned long long int currRiseTime = 0;
volatile unsigned long long int prevRiseTime = 0;
volatile unsigned long long int elaspedRiseTime = 0;

volatile int leadSignal = 0;
volatile int endSignal = 1;

volatile char IR_Signal[32];
volatile int writeIdx = 0;

/*
 * This function works to ensure that our code is getting to the desired point
 * By calling this function in another function, we can determine if
 * the uC has successfully gotten into that function
 */
void ledTest(void){
    int currStat = 0;
    
    while(1){
    
        delay_ms(250);
        LATBbits.LATB7 = currStat;
        LATBbits.LATB6 = currStat;
       
        if(currStat){
            currStat = 0;
        } 
        else{
            currStat = 1;
        }
    }
}

/**
 * This functions sets up the Input Capture 1 & Timer 2 Peripheral for the IR communication
 */
void IR_Setup(void) {
    TRISBbits.TRISB8 = 1;  //Sets pin RB8 / 17 to an input pin
    CNPU2bits.CN22PUE = 1; // pin RB8 / 17 pull-up enable
    
    __builtin_write_OSCCONL(OSCCON & 0xBF); //Unlock to update IC pin
    RPINR7bits.IC1R = 8; // Sets RP/B 8 for IC1
    __builtin_write_OSCCONL(OSCCON | 0x40); //Lock to update IC pin
    
    T2CON = 0; //Resets Timer 2 bits
    T2CONbits.TCKPS = 0b10; //prescaler of 1:1.  If we use the 62.5ns of Tcy and 15 cycles per period, we get 1us periods
    PR2 = 65535; //max PR
    TMR2 = 0;

    IC1CON = 0;
    IC1CONbits.ICTMR = 1; //use Timer 2 for IC1
    IC1CONbits.ICI = 0; //Interrupt every capture
    IC1CONbits.ICM = 0b010; //010 for falling edge,011 for rising edge pg.134

    IPC0bits.IC1IP = 6;//second highest IP
    IPC1bits.T2IP = 7;//highest IP

    _IC1IF = 0;
    _IC1IE = 1; //Enables IC1 interrupt
    _T2IE = 1; //T2 interrupt enable
    _T2IF = 0; //T2 interrupt flag reset
    T2CONbits.TON = 1; //turn on T2
}

/**
 * Configures the LEDs on pins 15 and 16 as outputs
 */
void TesterLEDSetup(void) {
    TRISBbits.TRISB7 = 0; //Sets pin RB7 / pin 16 to an output pin
    TRISBbits.TRISB6 = 0; //Sets pin RB6 / pin 15 to an output pin
}

/**
 * Timer 2 Interrupt - Sets flag to 0 and increments the number of overflows
 */
void __attribute__((interrupt, auto_psv)) _T2Interrupt() {
    _T2IF = 0; //T2 interrupt flag reset
    overflow++; //gets incremented every us    
}

/**
 * Input Capture Interrupt -
 * Captures the IR Signal and converts it to a pattern of 32 0 & 1s & sends the signal to
 * the decrypt function
 */
void __attribute__((interrupt, auto_psv))_IC1Interrupt() {
    _IC1IF = 0; //T1 interrupt flag reset
    
    
    if(endSignal == 1 && leadSignal == 0) {
        //Enters at the start of a signal to try to capture a lead
        TMR2 = 0;
        overflow = 0;
        currRiseTime = 0;
        endSignal = 0;
        
    } else {
        
        //Lead signal has been received so elaspedRiseTime is calculated.
        prevRiseTime = currRiseTime;
        currRiseTime = (unsigned long long int)((PR2 + 1)*(overflow) + IC1BUF);
        elaspedRiseTime = currRiseTime - prevRiseTime;   
        
        if(elaspedRiseTime < 250 ) {
            //Do nothing, Debounce tester
        } else if(endSignal == 0 && leadSignal == 0 && elaspedRiseTime > 3300 && elaspedRiseTime < 3450) {
            //No LeadSignal received
            leadSignal = 1;
            
        } else if(leadSignal == 1 && elaspedRiseTime < 625) {
            //LeadSignal has been received
            
            if(elaspedRiseTime > 250 && elaspedRiseTime < 350) {
                IR_Signal[writeIdx] = '0';
            } else if(elaspedRiseTime > 500 && elaspedRiseTime < 625) {
                IR_Signal[writeIdx] = '1';
            }
            
            writeIdx++;
            
            if(writeIdx == 32) {
                //32 zeros and ones have been written
                writeIdx = 0;
                leadSignal = 0;
                endSignal = 1;
                currRiseTime = 0;
                prevRiseTime = 0;
                decrypt();
            }
            
        }
    }   
}

/*
 * This function allows the user to display the recieved IR signal from the remote
 * to facilitate decryption of the signal.
 * 
 * Displays two panes of 16 bits (1/2 of the 32-bit signal, respectively)
 * sequentially for user to extract bitsequence of pressed button.
 */

void displayDecypher(void){
    //Clears LCD
    lcd_cmd(0b00000001);
    lcd_setCursor(0,0);
    
    int i = 0;
    int j;
    int k;
    int l;
    for(i = 0; i < 8; i++){//display first 8 bits on top row
        lcd_printChar(IR_Signal[i]);
    }
    lcd_setCursor(1,0);
    for(j = 0; j < 8; j++){//display next 8 bits on bottom row
        lcd_printChar(IR_Signal[j + 8]);
    }
    delay_ms(1000);//wait 1s to allow user to look at first half of signal

    lcd_setCursor(0,0);
    for(k = 0; k < 8; k++){//display bits 16-23 on top row after delay
        lcd_printChar(IR_Signal[k + 16]);
    }
    lcd_setCursor(1,0);
    for(l = 0; l < 8; l++){//display bits 24-31 on bottom row
        lcd_printChar(IR_Signal[l + 24]);
    }
    delay_ms(1000);//wait 1s for user to look at second half of signal

    lcd_cmd(0b00000001);//clear display
}

/**
 * This function takes the IR Signal array and finds the button that was pressed and triggers the
 * appropriate LED functions in the LedStrip_lib  
 */
void decrypt(void) {
    //Clears LCD
    lcd_cmd(0b00000001);
    lcd_setCursor(0,0);
    
    
    char possibleVals[32][32] = { //32x32 char array storing all possible button values for us to match against
        "00000000111101110011100011000111",
        "00000000111101111011100001000111",
        "00000000111101110111100010000111",
        "00000000111101111111100000000111",
        "00000000111101110000000011111111",
        "00000000111101111000000001111111",
        "00000000111101110100000010111111",
        "00000000111101111100000000111111",
        "00000000111101110010000011011111",
        "00000000111101111010000001011111",
        "00000000111101110110000010011111",
        "00000000111101111110000000011111",
        "00000000111101110001000011101111",
        "00000000111101111001000001101111",
        "00000000111101110101000010101111",
        "00000000111101111101000000101111",
        "00000000111101110011000011001111",
        "00000000111101111011000001001111",
        "00000000111101110111000010001111",
        "00000000111101111111000000001111",
        "00000000111101110000100011110111",
        "00000000111101111000100001110111",
        "00000000111101110100100010110111",
        "00000000111101111100100000110111",
        "00000000111101110010100011010111",
        "00000000111101111010100001010111",
        "00000000111101110110100010010111",
        "00000000111101111110100000010111",
        "00000000111101110001100011100111",
        "00000000111101111001100001100111",
        "00000000111101110101100010100111",
        "00000000111101111101100000100111"};
    
    int numMatch = 0;
    int a;
    int b;
    for(a = 0; a < 32; a++){//handles looping through all possible buttons
        for(b = 0; b < 13; b++){//handles looping through the pertinent characters
            if(possibleVals[a][16 + b] == IR_Signal[16 + b]){
                numMatch++;
            }
        }
        if(numMatch == 13){
            numMatch = 0;
            break;//leave outer for loop when button is found ==> a is the integer of the
                  //located button
        }
        else
            numMatch = 0;
    }
    
    if(a < 32)
        LATBbits.LATB7 = 1;//turn on status LED when signal is recieved
    
    switch(a){
        case 0:
            lcd_printStr("Btn 0");
            break;
        
        case 1:
            lcd_printStr("Btn 1");
            break;

        case 2:
            lcd_printStr("Btn 2");
            break;
        
        case 3:
            lcd_printStr("Btn 3");//speed functiton
            dynamicFctn = 's';
            break;
        
        case 4:
            lcd_printStr("Btn 4");
            dynamicFctn = 'a';
            break;
        
        case 5:
            lcd_printStr("Btn 5");
            break;
        
        case 6:
            lcd_printStr("Btn 6");
            break;

        case 7:
            lcd_printStr("Btn 7");
            break;

        case 8:
            lcd_printStr("Btn 8");
            break;

        case 9:
            lcd_printStr("Btn 9");
            break;

        case 10:
            lcd_printStr("Btn 10");
            break;
            
        case 11:
            lcd_printStr("Btn 11");//rainbow/wheel function
            dynamicFctn = 'g';
            break;

        case 12:
            lcd_printStr("Btn 12");
            break;

        case 13:
            lcd_printStr("Btn 13");
            break;

        case 14:
            lcd_printStr("Btn 14");
            break;

        case 15:
            lcd_printStr("Btn 15");//fade funtion
            dynamicFctn = 'f';
            break;

        case 16:
            lcd_printStr("Btn 16");
            break;

        case 17:
            lcd_printStr("Btn 17");
            break;

        case 18:
            lcd_printStr("Btn 18");
            break;

        case 19:
            lcd_printStr("Btn 19");
            break;

        case 20:
            lcd_printStr("Btn 20");
            break;

        case 21:
            lcd_printStr("Btn 21");
            break;

        case 22:
            lcd_printStr("Btn 22");
            break;

        case 23:
            lcd_printStr("Btn 23");
            break;

        case 24:
            lcd_printStr("Btn 24");//wave function (sorry schrodinger)
            waveSetup();
            dynamicFctn = 'w';
            break;

        case 25:
            lcd_printStr("Btn 25");//strobe function
            dynamicFctn = 'v';
            break;

        case 26:
            lcd_printStr("Btn 26");//twinkle function
            twinkleSetup();
            dynamicFctn = 't';
            break;

        case 27:
            lcd_printStr("Btn 27");//asynWave function
            asynWaveSetup();
            dynamicFctn = 'y';
            break;

        case 28:
            lcd_printStr("Btn 28");//panel 1 select
            previousPanel = 1;
            break;

        case 29:
            lcd_printStr("Btn 29");//panel 2 select
            previousPanel = 2;
            break;

        case 30:
            lcd_printStr("Btn 30");//panel 3 select
            previousPanel = 3;
            break;

        case 31:
            lcd_printStr("Btn 31");//select all panels
            previousPanel = 4;
            break;
            
        default:
            lcd_printStr("notFound");
            break;
    }
    if((a == 1) || (a < 11 && a > 3) || (a < 15 && a > 11) || (a < 19 && a > 15) || (a < 23 && a > 19)){//allows us to check whether or not a dynamic function has been called.  If not, we reset the dynamicFctn variable to a char that will not match any clauses in the switch statement of TMR1.  This way, we can disable a dynamic funciton if we want to change the panel
        dynamicFctn = 'a';//set dynamicFctn select variable to a non-matching char
        masterStaticColorCreator(a);//create static color for the pressed button
        writeColorToPanel(previousPanel, staticColor);//write the static color to the desired panel

    }
    
    delay_ms(1000);//wait 1s for led to sufficiently display
    LATBbits.LATB7 = 0;//turn off status LED
    
    lcd_cmd(0b00000001);//reset the LCD
}