/*
 * File:   IR_lib.c
 * Author: jimen
 *
 * Created on March 25, 2023, 3:42 PM
 */

#include "xc.h"
#include "IR_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "I2C_LCD.h"
#include "LedStrip_lib.h"

volatile int LedStatus = 0;
volatile unsigned long long int overflow = 0;
volatile unsigned long long int currRiseTime = 0;
volatile unsigned long long int prevRiseTime = 0;
volatile unsigned long long int elaspedRiseTime = 0;
volatile unsigned long long int myCounter1 = 0;

volatile unsigned int leftShiftCounter = 0;

volatile int leadSignal = 0;
volatile int endSignal = 1;

volatile char IR_Signal[32];
volatile int readIdx = 0;
volatile int writeIdx = 0;

volatile int rainbowFunction = 0;


//


//
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
    
 
    _IC1IF = 0;

    _IC1IE = 1; //Enables IC1 interrupt
    
    _T2IE = 1; //T2 interrupt enable
    
    _T2IF = 0; //T2 interrupt flag reset
    
    T2CONbits.TON = 1; //turn on T2
    
}

/**
 * Tester Code
 */
void TesterLEDSetup(void) {
    TRISBbits.TRISB7 = 0; //Sets pin RB7 / pin 16 to an output pin
    TRISBbits.TRISB6 = 0; //Sets pin RB8 / pin 17 to an output pin
}

void rainbow(void) {
    while(1) {
        writeColorToPanel(previousPanel, red);
        wait(250);
        writeColorToPanel(previousPanel, red_orange);
        wait(250);
        writeColorToPanel(previousPanel, orange);
        wait(250);
        writeColorToPanel(previousPanel, light_orange);
        wait(250);
        writeColorToPanel(previousPanel, yellow);
        wait(250);
        writeColorToPanel(previousPanel, green);
        wait(250);
        writeColorToPanel(previousPanel, light_green);
        wait(250);
        writeColorToPanel(previousPanel, cyan);
        wait(250);
        writeColorToPanel(previousPanel, light_blue);
        wait(250);
        writeColorToPanel(previousPanel, blue);
        wait(250);
        writeColorToPanel(previousPanel, dark_blue);
        wait(250);
        writeColorToPanel(previousPanel, purple);
        wait(250);
        writeColorToPanel(previousPanel, magenta);
        wait(250);
        writeColorToPanel(previousPanel, pink);
        wait(250);
    }
}

/**
 * Timer 2 Interrupt - Sets flag to 0 and counts the number of overflows
 */
void __attribute__((interrupt, auto_psv)) _T2Interrupt() {
    _T2IF = 0; //T2 interrupt flag reset
    overflow++; //gets incremented every us    
    if(rainbowFunction){
        rainbowFunction = 0;
        rainbow();
    }
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

//
//void __attribute__((interrupt, auto_psv))_IC1Interrupt() {
//    _IC1IF = 0; //T1 interrupt flag reset
//    
//    
//    if(endSignal == 1 && leadSignal == 0) {
//        //Enters at the start of a signal to try to capture a lead
//        TMR2 = 0;
//        overflow = 0;
//        currRiseTime = 0;
//        endSignal = 0;
//        
//    } else {
//        
//        //Lead signal has been received so elaspedRiseTime is calculated.
//        prevRiseTime = currRiseTime;
//        currRiseTime = (unsigned long long int)((PR2 + 1)*(overflow) + IC1BUF);
//        elaspedRiseTime = currRiseTime - prevRiseTime;   
//        
//        if(elaspedRiseTime < 250 || elaspedRiseTime > 625) {
//            //Do nothing, Debounce tester
//            endSignal = 1;
//        } else if(endSignal == 0 && leadSignal == 0 && elaspedRiseTime > 3300 && elaspedRiseTime < 3450) {
//            //No LeadSignal received
//            leadSignal = 1;
//            
//        } else if(leadSignal == 1 && elaspedRiseTime < 625) {
//            //LeadSignal has been received
//            
//            if(elaspedRiseTime > 250 && elaspedRiseTime < 350) {
//                //0
//                IR_Signal[writeIdx] = '0';
//            } else if(elaspedRiseTime > 500 && elaspedRiseTime < 625) {
//                //1
//                IR_Signal[writeIdx] = '1';
//            }
//            
//            writeIdx++;
//            
//            if(writeIdx == 32) {
//                //32 zeros and ones have been written
//                writeIdx = 0;
//                leadSignal = 0;
//                endSignal = 1;
//                currRiseTime = 0;
//                prevRiseTime = 0;
//                decrypt();
//            }
//            
//        }
//    }   
//}

/**
 * This function takes the IR Signal array and finds the button that was pressed and triggers the
 * appropriate LED functions in the LedStrip_lib  
 */
void decrypt(void) {
    //Clears LCD
    lcd_cmd(0b00000001);
    lcd_setCursor(0,0);
    
    char possibleVals[32][32] = {
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
            break; //lmao - what I say not to do lol
        }
        else
            numMatch = 0;
    }//when this breaks, the button pressed should be the value of a..
    
    
    switch(a){
        case 0:
            lcd_printStr("Btn 0");
            break;
        
        case 1:
            lcd_printStr("Btn 1");
            writeColorToPanel(previousPanel, off);
            break;

        case 2:
            lcd_printStr("Btn 2");
            break;
        
        case 3:
            lcd_printStr("Btn 3");
            break;
        
        case 4:
            lcd_printStr("Btn 4");
            writeColorToPanel(previousPanel, red);
            break;
        
        case 5:
            lcd_printStr("Btn 5");
            writeColorToPanel(previousPanel, green);
            break;
        
        case 6:
            lcd_printStr("Btn 6");
            writeColorToPanel(previousPanel, blue);
            break;

        case 7:
            lcd_printStr("Btn 7");
            writeColorToPanel(previousPanel, white);
            break;

        case 8:
            lcd_printStr("Btn 8");
            writeColorToPanel(previousPanel, red_orange);
            break;

        case 9:
            lcd_printStr("Btn 9");
            writeColorToPanel(previousPanel, light_green);
            break;

        case 10:
            lcd_printStr("Btn 10");
            writeColorToPanel(previousPanel, light_blue);
            break;
            
        case 11:
            lcd_printStr("Btn 11");
//            rainbow();
            rainbowFunction = 1;
            break;

        case 12:
            lcd_printStr("Btn 12");
            writeColorToPanel(previousPanel, orange);
            break;

        case 13:
            lcd_printStr("Btn 13");
            writeColorToPanel(previousPanel, cyan);
            break;

        case 14:
            lcd_printStr("Btn 14");
            writeColorToPanel(previousPanel, purple);
            break;

        case 15:
            lcd_printStr("Btn 15");
            break;

        case 16:
            lcd_printStr("Btn 16");
            writeColorToPanel(previousPanel, light_orange);
            break;

        case 17:
            lcd_printStr("Btn 17");
            writeColorToPanel(previousPanel, dark_blue);
            break;

        case 18:
            lcd_printStr("Btn 18");
            writeColorToPanel(previousPanel, magenta);
            break;

        case 19:
            lcd_printStr("Btn 19");
            break;

        case 20:
            lcd_printStr("Btn 20");
            writeColorToPanel(previousPanel, yellow);
            break;

        case 21:
            lcd_printStr("Btn 21");
            writeColorToPanel(previousPanel, faint_blue);
            break;

        case 22:
            lcd_printStr("Btn 22");
            writeColorToPanel(previousPanel, pink);
            break;

        case 23:
            lcd_printStr("Btn 23");
            break;

        case 24:
            lcd_printStr("Btn 24");
            break;

        case 25:
            lcd_printStr("Btn 25");
            break;

        case 26:
            lcd_printStr("Btn 26");
            break;

        case 27:
            lcd_printStr("Btn 27");
            break;

        case 28:
            lcd_printStr("Btn 28");
            previousPanel = 1;
            break;

        case 29:
            lcd_printStr("Btn 29");
            previousPanel = 2;
            break;

        case 30:
            lcd_printStr("Btn 30");
            previousPanel = 3;
            break;

        case 31:
            lcd_printStr("Btn 31");
            previousPanel = 4;
            break;
            
        default:
            lcd_printStr("notFound");
            break;
    }
    delay_ms(1000);
    
    
    lcd_cmd(0b00000001);
    
//    lcd_setCursor(0,0);
//    int i = 0;
//    int j;
//    int k;
//    int l;
//    for(i = 0; i < 8; i++){
//        lcd_printChar(IR_Signal[i]);
//    }
//    lcd_setCursor(1,0);
//    for(j = 0; j < 8; j++){
//        lcd_printChar(IR_Signal[j + 8]);
//    }
//    delay_ms(1000);
//    lcd_setCursor(0,0);
//    for(k = 0; k < 8; k++){
//        lcd_printChar(IR_Signal[k + 16]);
//    }
//    lcd_setCursor(1,0);
//    for(l = 0; l < 8; l++){
//        lcd_printChar(IR_Signal[l + 24]);
//    }
//    delay_ms(1000);
//    lcd_cmd(0b00000001);
    
}