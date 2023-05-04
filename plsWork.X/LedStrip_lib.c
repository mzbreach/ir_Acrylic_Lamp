/* 
 * File:   LedStrip_lib.c
 * Project: IR Acrylic Lamp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LedStrip_lib.h"
#include "IR_lib.h"
#include "xc.h"

#define PERIOD 5

int panel = 0; // Change this to change the LED strip

// These are the colors (kind of, not really) that should be used as parameters in combination with "panel"
// With these two parameters, it is a matter of calling functions to produce the correct combination/event
// Currently these color arrays have not been tested, so some colors might not be accurate
int color[ARRAY_SIZE] = {0};
int staticColor[ARRAY_SIZE] = {0};
int off[ARRAY_SIZE] = {0};

int speed1[ARRAY_SIZE] = {0};
int speed2[ARRAY_SIZE] = {0};

int twinkle1[ARRAY_SIZE] = {0};
int twinkle2[ARRAY_SIZE] = {0};
int twinkleRestore[ARRAY_SIZE] = {0};

int invert1[ARRAY_SIZE] = {0};

int wave1[ARRAY_SIZE] = {0};
int wave2[ARRAY_SIZE] = {0};
int wave3[ARRAY_SIZE] = {0};
int wave4[ARRAY_SIZE] = {0};
int wave5[ARRAY_SIZE] = {0};

int asynWave1[ARRAY_SIZE] = {0};
int asynWave2[ARRAY_SIZE] = {0};
int asynWave3[ARRAY_SIZE] = {0};
int asynWave4[ARRAY_SIZE] = {0};
int asynWave5[ARRAY_SIZE] = {0};
int asynWave6[ARRAY_SIZE] = {0};
int asynWave7[ARRAY_SIZE] = {0};
int asynWave8[ARRAY_SIZE] = {0};

// Testing LED strip color arrays
// Set one of these equal to a pre-made color array for easy access to colors
// For example, "memcpy(grb1, green, sizeof(grb1));" will output green to LED Strip 1

int grb1[ARRAY_SIZE] = {0};
int grb2[ARRAY_SIZE] = {0};
int grb3[ARRAY_SIZE] = {0};
int previousPanel = 4;
int previousColor[ARRAY_SIZE] = {0};

// These arrays hold the converted values of the 27-element color array into the binary representation for easy access
// to writing HIGH or LOW to the LED pixels to actually output the correct color for each LED

int binaryGRB1[ARRAY_SIZE * 24] = {0};
int binaryGRB2[ARRAY_SIZE * 24] = {0};
int binaryGRB3[ARRAY_SIZE * 24] = {0};

int check = 0;

char dynamicFctn = 'a';
volatile unsigned long long int LEDOverflow = 0;
volatile unsigned long long int currentTime = 0;
volatile unsigned long long int prevTime = 0;
volatile int rainbowCounter = 0;
volatile int speedCounter = 0;
volatile int seizureCounter = 0;
volatile int twinkleCounter = 0;
volatile int asynWaveCounter = 0;
volatile int fadeCounter = 0;
volatile int waveCounter = 0;

volatile int fadeColor[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int fadeR = 0;

/* LED strip setup fnction
 */

void LedStrip_Setup(void){
    
    TRISA = 0b1111111111100000;  //and port A to outputs
    LATA = 0x0010;               //Set all of port A to HIGH
    
    writeColorToPanel(4, off);
    wait(500);
    
    //We want to initialize timer 1 for the color function
    T1CON = 0;
    T1CONbits.TCKPS = 0b01; //1:: prescaler
    PR1 = 19999;//10 ms period
    TMR1 = 0;
    IPC0bits.T1IP = 5;
    
    _T1IE = 1;
    _T1IF = 0;
    T1CONbits.TON = 1;
    
}

/* This ISR handles the dynamic functions - allows them to activate on their required
 * delays in 10ms oeriods
 */

void __attribute__((interrupt, auto_psv)) _T1Interrupt(){//ideally should trigger once every 10ms
    _T1IF = 0;
    switch(dynamicFctn){
        case 'g'://rainbow function called
//            currentTime - prevTime >= 250
            if(LEDOverflow >= 25){
                rainbow(rainbowCounter);
                rainbowCounter = (rainbowCounter + 1) % 14;
                LEDOverflow = 0;
            }
            break;
            
        case 's'://speed function called
            if(LEDOverflow >= 3){
                speed(speedCounter);
                speedCounter = (speedCounter + 1) % 8;
                LEDOverflow = 0;
            }
            break;
            
        case 'v'://strobe function called
            if(LEDOverflow >= 3){
                seizure(seizureCounter);
                seizureCounter = (seizureCounter + 1) % 2;
                LEDOverflow = 0;
            }
            break;
        
        case 't'://twinkle function called
            if(LEDOverflow >= 100){
                twinkle(twinkleCounter);
                twinkleCounter = (twinkleCounter + 1) % 4;
                LEDOverflow = 0;
            }
            break;
            
        case 'y'://asynWave
            if(LEDOverflow >= 10){
                asynWave(asynWaveCounter);
                asynWaveCounter = (asynWaveCounter + 1) % 14;
                LEDOverflow = 0;
            }
            break;
            
        case 'f'://fade
            if(LEDOverflow >= 10){
                fade(fadeCounter);
                fadeCounter = (fadeCounter + 1) % 3;
                LEDOverflow = 0;
            }
            break;
            
        case 'i'://invert
            invert();
            LEDOverflow = 1;
            break;
            
        case 'w'://Wave
            if(LEDOverflow >= 10){
                wave(waveCounter);
                waveCounter = (waveCounter + 1) % 8;
                LEDOverflow = 0;
            }
            break;
            
            
        default:
            break;
    }
    LEDOverflow++;

}


/* This function converts the decimal representation of a color from an array 
 * grb[ARRAY_SIZE] and places it into another array binaryGRB[24 * ARRAY_SIZE] as the binary 
 * representation of the same color. */

void convertDecToBin(int grb[], int binaryGRB[]) {
    int i;
    int j;
    
    int check = 0b11111111;
    int binaryIndex = 0;
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 7; j >= 0; j--) {
            if (((grb[i] >> j) && check) == 0b000000001) {
                binaryGRB[binaryIndex++] = 1;
            }
            
            else {
                binaryGRB[binaryIndex++] = 0;
            }
        }
    }
    
}

/* This function displays the correct color selected using the binary 
 * representation of the selected color to LED Strip 1. */

void writeBinToLED1(int binaryGRB[]) {
  int i;
    for (i = 0; i < (24 * ARRAY_SIZE); i++) {
        if (binaryGRB[i] == 1) {
            write_1();
        }
        
        else {
            write_0();
        }
    }
}

/* This function displays the correct color selected using the binary 
 * representation of the selected color to LED Strip 2. */

void writeBinToLED2(int binaryGRB[]) {
  int i;
    for (i = 0; i < 648; i++) {
        if (binaryGRB[i] == 1) {
            write_1_p2();
        }
        
        else {
            write_0_p2();
        }
    }
}

/* This function displays the correct color selected using the binary 
 * representation of the selected color to LED Strip 3. */

void writeBinToLED3(int binaryGRB[]) {
  int i;
    for (i = 0; i < 648; i++) {
        if (binaryGRB[i] == 1) {
            write_1_p3();
        }
        
        else {
            write_0_p3();
        }
    }
}

/* This function takes an integer parameter for the desired milliseconds to 
 * delay the program. */

void wait(int ms){
    int i = 0;
    for(i = 0; i < ms; i++){
        wait_1ms();
    }
}

/* this function works to edit the volatile staticColor array such that it 
 * stores the appropriate color before calling writeColorToPanel
 * 
 * This function works for n number of LEDs (as defined by ARRAY_SIZE / n)
 */
void masterStaticColorCreator(int state){
    int i;
    switch(state) {
        case 1://off
            for (i = 0; i < ARRAY_SIZE; i++) {
                staticColor[i] = 0;
            }
            break;
            
        case 4: // red
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 0;
                }
            }
            break;
            
        case 5: // green
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 255;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 0;
                }
            }
            break;
            
        case 6: // blue
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 255;
                }
            }
            break;
            
        case 7: // white
            for (i = 0; i < ARRAY_SIZE; i++) {
                staticColor[i] = 255;
            }
            break;
            
        case 8: // orange
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 15;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 0;
                }
            }
            break;
            
        case 9: // light_green
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 255;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 20;
                }
            }
            break;
            
        case 10: // light_blue
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 80;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 255;
                }
            }
            break;
            
        case 12: // orange
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 30;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 0;
                }
            }
            break;
            
        case 13: // cyan
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 255;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 255;
                }
            }
            break;
            
        case 14: // purple
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 127;
                }
                else {
                    staticColor[i] = 255;
                }
            }
            break;
            
        case 16: // light_orange
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 50;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 0;
                }
            }
            break;
            
        case 17: // dark_blue
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 75;
                }
            }
            break;
            
        case 18: // magenta
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 255;
                }
            }
            break;
            
        case 20: // yellow
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 255;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 0;
                }
            }
            break;
            
        case 21: // faint_blue
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 0;
                }
                else {
                    staticColor[i] = 15;
                }
            }
            break;
            
        case 22: // pink
            for (i = 0; i < ARRAY_SIZE; i++) {
                if (i % 3 == 0) {
                    staticColor[i] = 0;
                }  
                else if (i % 3 == 1) {
                    staticColor[i] = 255;
                }
                else {
                    staticColor[i] = 127;
                }
            }
            break;
            
        default:
            break;  
    }
}

/* The following will be a library of functions to make certain/all panels 
 * colors given the remote signal. */

void writeColorToPanel(int panel, int color[]){
    // memcpy copies elements from color and places them into grb1, grb2, grb3
    memcpy(grb1, color, sizeof(grb1));
    memcpy(grb2, color, sizeof(grb2));
    memcpy(grb3, color, sizeof(grb3));
    
    // Checks which panel(s) is/are selected and if the LED strip is displaying anything except off in order to save the current color
    if (color != off ){
        memcpy(previousColor, color, sizeof(previousColor));
    }
    
    // Save the selected panel as the previously selected panel for references later
    previousPanel = panel;
    
    // Checks which panel is selected and displays the desired color
    if(panel == 1){
        convertDecToBin(grb1, binaryGRB1);
        asm("CLR LATA");
        wait_100us();
        writeBinToLED1(binaryGRB1);
    }
    
    else if (panel == 2){
        convertDecToBin(grb2, binaryGRB2);
        asm("CLR LATA");
        wait_100us();
        writeBinToLED2(binaryGRB2);
    }
    
    else if (panel == 3){
        convertDecToBin(grb3, binaryGRB3);
        asm("CLR LATA");
        wait_100us();
        writeBinToLED3(binaryGRB3);
    }
    
    else if (panel == 4){
        convertDecToBin(grb1, binaryGRB1);
        convertDecToBin(grb2, binaryGRB2);
        convertDecToBin(grb3, binaryGRB3);
        asm("CLR LATA");
        wait_100us();
        
        writeBinToLED1(binaryGRB1);
        writeBinToLED2(binaryGRB2);
        writeBinToLED3(binaryGRB3);
    }
}

/* The following will allow for dynamic functions such as a rainbow or a 
 * flashing effect. */

void rainbow(int state) {
    switch (state){
        case 0:
            masterStaticColorCreator(4);//red
            break;
        case 1:
            masterStaticColorCreator(8);//red_orange
            break;
        case 2:
            masterStaticColorCreator(12);//orange
            break;
        case 3:
            masterStaticColorCreator(16);//light_orange
            break;
        case 4:
            masterStaticColorCreator(20);//yellow
            break;
        case 5:
            masterStaticColorCreator(5);//green
            break;
        case 6:
            masterStaticColorCreator(9);//light_green
            break;
        case 7:
            masterStaticColorCreator(13);//cyan
            break;
        case 8:
            masterStaticColorCreator(10);//light_blue
            break;
        case 9:
            masterStaticColorCreator(6);//blue
            break;
        case 10:
            masterStaticColorCreator(17);//dark_blue
            break;
        case 11:
            masterStaticColorCreator(14);//purple
            break;
        case 12:
            masterStaticColorCreator(18);//magenta
            break;
        case 13:
            masterStaticColorCreator(22);//pink
            break;
        default:
            
            break;
    }
    writeColorToPanel(previousPanel, staticColor);
}


void speedSetup(void){
    masterStaticColorCreator(6);//blue
    int i, j;
    for(i = (ARRAY_SIZE / 2) - 3; i < (ARRAY_SIZE / 2) + 3; i++){//put middle pixel white
        if(i % 3 == 0){//start of a pixel
            for(j = 0; j < 6; j++){
                staticColor[j] = 255;
            }
            break;
        }
    }
    speed1 = staticColor;
    masterStaticColorCreator(4);//red
    for(i = (ARRAY_SIZE / 2) - 3; i < (ARRAY_SIZE / 2) + 3; i++){//put middle pixel white
        if(i % 3 == 0){//start of a pixel
            for(j = 0; j < 6; j++){
                staticColor[j] = 255;
            }
            break;
        }
    }
    speed2 = staticColor;
}

/* Speed function
 */

void speed(int state) {
    switch (state){
        case 0:
            writeColorToPanel(previousPanel, speed1);
            break;
        case 1:
            writeColorToPanel(previousPanel, off);
            break;
        case 2:
            writeColorToPanel(previousPanel, speed1);
            break;
        case 3:
            writeColorToPanel(previousPanel, off);
            break;
        case 4:
            writeColorToPanel(previousPanel, speed2);
            break;
        case 5:
            writeColorToPanel(previousPanel, off);
            break;
        case 6:
            writeColorToPanel(previousPanel, speed2);
            break;
        case 7:
            writeColorToPanel(previousPanel, off);
            break;
        
        default:
            break;
    }
}

/*Invert setup - call once every time button is pressed
 */

void invertSetup(void){
    int i = 0;
    memcpy(invert1, previousColor, sizeof(invert1));
    for (i = 0; i < 27; i++) {
        invert1[i] = invert1[i] - 255;
        if (invert1[i] < 0) {
            invert1[i] = invert1[i] * (-1);
        }
    }
}

/*Invert function
 */
void invert(void) {
    writeColorToPanel(previousPanel, invert1);
}

/* Twinkle setup function - call once every time button is pressed
 */
void twinkleSetup(void){//called once every time twinkle is initialized
    int i = 0;
    memcpy(twinkle2, previousColor, sizeof(twinkleRestore));
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        twinkle2[i] = twinkle2[i] - 255;
        if (twinkle2[i] < 0) {
            twinkle2[i] = twinkle2[i] * (-1);
        }
    }
    
    memcpy(twinkleRestore, previousColor, sizeof(twinkleRestore));
}

/* Twinkle function
 */
void twinkle(int state) {
    switch(state){
        case 0:
            memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
            twinkle1[3] = twinkle2[3];
            twinkle1[4] = twinkle2[4];
            twinkle1[5] = twinkle2[5];
            twinkle1[24] = twinkle2[24];
            twinkle1[25] = twinkle2[25];
            twinkle1[26] = twinkle2[26];
            writeColorToPanel(previousPanel, twinkle1);
            break;
            
        case 1:
            memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
            twinkle1[9] = twinkle2[9];
            twinkle1[10] = twinkle2[10];
            twinkle1[11] = twinkle2[11];
            twinkle1[0] = twinkle2[0];
            twinkle1[1] = twinkle2[1];
            twinkle1[2] = twinkle2[2];
            writeColorToPanel(previousPanel, twinkle1);
            break;
            
        case 2:
            memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
            twinkle1[15] = twinkle2[15];
            twinkle1[16] = twinkle2[16];
            twinkle1[17] = twinkle2[17];
            twinkle1[6] = twinkle2[6];
            twinkle1[7] = twinkle2[7];
            twinkle1[8] = twinkle2[8];
            writeColorToPanel(previousPanel, twinkle1);
            break;
            
        case 3:
            memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
            twinkle1[21] = twinkle2[21];
            twinkle1[22] = twinkle2[22];
            twinkle1[23] = twinkle2[23];
            twinkle1[18] = twinkle2[18];
            twinkle1[19] = twinkle2[19];
            twinkle1[20] = twinkle2[20];
            writeColorToPanel(previousPanel, twinkle1);
            break;
            
        default:
            break;
    }
}

/* This function is a dynamic function that blinks a selected LED strip, acting
 * as a strobe event for the LEDs. */

void seizure(int state) { 
    switch(state){
        case 0:
            writeColorToPanel(previousPanel, previousColor);
            break;
        case 1:
            writeColorToPanel(previousPanel, off);
            break;
    }
}

/* Fade function - a little scuffed, but it works
 */

void fade(int state){
    int i, j;

    switch (state) {
        case 0: 
            for(i = 1; i < 255; i+= 2) {
                for (j = 0; j <= 25; j+=3){
                    fadeColor[j] = i;
                }
                writeColorToPanel(previousPanel, fadeColor);

            } 
            for(i = 255; i > 0; i -=2) {
                for (j = 0; j <= 25; j+=3){
                    fadeColor[j] = i;
                }
                writeColorToPanel(previousPanel, fadeColor);
            }
            break;
            
        case 1:
            for(i = 1; i < 255; i+=2) {
                for (j = 1; j <= 26; j+=3){
                    fadeColor[j] = i;
                }
                writeColorToPanel(previousPanel, fadeColor);
            } 

            for(i = 255; i > 1; i-=2) {
                for (j = 1; j <= 26; j+=3){
                    fadeColor[j] = i;
                }
                writeColorToPanel(previousPanel, fadeColor);
            }
            break;

        case 2:
            for(i = 1; i < 255; i+=2) {
                for (j = 2; j <= 27; j+=3){
                    fadeColor[j] = i;
                }
                writeColorToPanel(previousPanel, fadeColor);
            } 
            for(i = 255; i > 1; i-=2) {
                for (j = 2; j <= 27; j+=3){
                    fadeColor[j] = i;
                }
                writeColorToPanel(previousPanel, fadeColor);
            }

            break;
        default:
            break;
    }
}

/*Wave setup - call once every time wave button is pressed
 */

void waveSetup(void){
    int i = 0;
    memcpy(wave1, previousColor, sizeof(wave1));
    memcpy(wave2, previousColor, sizeof(wave1));
    memcpy(wave3, previousColor, sizeof(wave1));
    memcpy(wave4, previousColor, sizeof(wave1));
    memcpy(wave5, previousColor, sizeof(wave1));
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (i < 3 || i > 24) {
            wave1[i] = 0;
            wave2[i] = 0;
            wave3[i] = 0;
            wave4[i] = 0;
        }
        
        else if (i < 6 || i > 21) {
            wave1[i] = 0;
            wave2[i] = 0;
            wave3[i] = 0;
        }
        
        else if (i < 9 || i > 18) {
            wave1[i] = 0;
            wave2[i] = 0;
        }
        
        else if (i < 12 || i > 14) {
            wave1[i] = 0;
        }
    }
}

/*Wave function
 */

void wave(int state) {
    switch(state){
        case 0:
            writeColorToPanel(previousPanel, wave1);
            break;
            
        case 1:
            writeColorToPanel(previousPanel, wave2);
            break;
            
        case 2:
            writeColorToPanel(previousPanel, wave3);
            break;
            
        case 3:
            writeColorToPanel(previousPanel, wave4);
            break;
            
        case 4:
            writeColorToPanel(previousPanel, wave5);
            break;
            
        case 5:
            writeColorToPanel(previousPanel, wave4);
            break;
            
        case 6:
            writeColorToPanel(previousPanel, wave3);
            break;
            
        case 7:
            writeColorToPanel(previousPanel, wave2);
            break;
            
        default:
            break;
    }
}

/*
 * Asyn wave setup function - call once every time this button is pressed
 */

void asynWaveSetup(void){
    int i = 0;
    memcpy(asynWave1, previousColor, sizeof(asynWave1));
    memcpy(asynWave2, previousColor, sizeof(asynWave1));
    memcpy(asynWave3, previousColor, sizeof(asynWave1));
    memcpy(asynWave4, previousColor, sizeof(asynWave1));
    memcpy(asynWave5, previousColor, sizeof(asynWave1));
    memcpy(asynWave6, previousColor, sizeof(asynWave1));
    memcpy(asynWave7, previousColor, sizeof(asynWave1));
    memcpy(asynWave8, previousColor, sizeof(asynWave1));
    
        for (i = 26; i >= 0; i--) {
            if (i > 23) {
                asynWave1[i] = 0;
                asynWave2[i] = 0;
                asynWave3[i] = 0;
                asynWave4[i] = 0;
                asynWave5[i] = 0;
                asynWave6[i] = 0;
                asynWave7[i] = 0;
            }

            else if (i > 20) {
                asynWave1[i] = 0;
                asynWave2[i] = 0;
                asynWave3[i] = 0;
                asynWave4[i] = 0;
                asynWave5[i] = 0;
                asynWave6[i] = 0;
            }

            else if (i > 17) {
                asynWave1[i] = 0;
                asynWave2[i] = 0;
                asynWave3[i] = 0;
                asynWave4[i] = 0;
                asynWave5[i] = 0;
                asynWave8[i] = 0;
            }

            else if (i > 14) {
                asynWave1[i] = 0;
                asynWave2[i] = 0;
                asynWave3[i] = 0;
                asynWave4[i] = 0;
                asynWave7[i] = 0;
                asynWave8[i] = 0;
            }

            else if (i > 11) {
                asynWave1[i] = 0;
                asynWave2[i] = 0;
                asynWave3[i] = 0;
                asynWave6[i] = 0;
                asynWave7[i] = 0;
                asynWave8[i] = 0;
            }

            else if (i > 8) {
                asynWave1[i] = 0;
                asynWave2[i] = 0;
                asynWave5[i] = 0;
                asynWave6[i] = 0;
                asynWave7[i] = 0;
                asynWave8[i] = 0;
            }

            else if (i > 5) {
                asynWave1[i] = 0;
                asynWave4[i] = 0;
                asynWave5[i] = 0;
                asynWave6[i] = 0;
                asynWave7[i] = 0;
                asynWave8[i] = 0;
            }

            else if (i > 2) {
                asynWave3[i] = 0;
                asynWave4[i] = 0;
                asynWave5[i] = 0;
                asynWave6[i] = 0;
                asynWave7[i] = 0;
                asynWave8[i] = 0;
            }

            else {
                asynWave2[i] = 0;
                asynWave3[i] = 0;
                asynWave4[i] = 0;
                asynWave5[i] = 0;
                asynWave6[i] = 0;
                asynWave7[i] = 0;
                asynWave8[i] = 0;
            }
        }
}

/*
 * Wave function for the asyncrounous wave
 */

void asynWave(int state) {
    switch (state) {
        case 0:
        writeColorToPanel(previousPanel, asynWave1);
        break;
        
        case 1:
        writeColorToPanel(previousPanel, asynWave2);
        break;
        
        case 2:
        writeColorToPanel(previousPanel, asynWave3);
        break;
            
        case 3:    
        writeColorToPanel(previousPanel, asynWave4);
        break;
        
        case 4:
        writeColorToPanel(previousPanel, asynWave5);
        break;
        
        case 5:
        writeColorToPanel(previousPanel, asynWave6);
        break;        
        
        case 6:
        writeColorToPanel(previousPanel, asynWave7);
        break;        
        
        case 7:
        writeColorToPanel(previousPanel, asynWave8);
        break;   
        
        case 8:
        writeColorToPanel(previousPanel, asynWave7);
        break;
        
        case 9:
        writeColorToPanel(previousPanel, asynWave6);
        break;
        
        case 10:
        writeColorToPanel(previousPanel, asynWave5);
        break;
        
        case 11:
        writeColorToPanel(previousPanel, asynWave4);
        break;
        
        case 12:
        writeColorToPanel(previousPanel, asynWave3);
        break;
        
        case 13:
        writeColorToPanel(previousPanel, asynWave2);
        break;
        
        default:
            break;
    }
}
