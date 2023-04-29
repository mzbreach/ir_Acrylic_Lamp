
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LedStrip_lib.h"
#include "IR_lib.h"
#include"xc.h"
#define PERIOD 5

int panel = 0; // Change this to change the LED strip

// These are the colors (kind of, not really) that should be used as parameters in combination with "panel"
// With these two parameters, it is a matter of calling functions to produce the correct combination/event
// Currently these color arrays have not been tested, so some colors might not be accurate

int green[27] = {255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0};
int red[27] = {0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0};
int blue[27] = {0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255};
int white[27] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

int red_orange[27] = {15, 255, 0, 15, 255, 0, 15, 255, 0, 15, 255, 0, 15, 255, 0, 15, 255, 0, 15, 255, 0, 15, 255, 0, 15, 255, 0};
int light_green[27] = {255, 0, 20, 255, 0, 20, 255, 0, 20, 255, 0, 20, 255, 0, 20, 255, 0, 20, 255, 0, 20, 255, 0, 20, 255, 0, 20};
int light_blue[27] = {80, 0, 255, 80, 0, 255, 80, 0, 255, 80, 0, 255, 80, 0, 255, 80, 0, 255, 80, 0, 255, 80, 0, 255, 80, 0, 255};

int orange[27] = {30, 255, 0, 30, 255, 0, 30, 255, 0, 30, 255, 0, 30, 255, 0, 30, 255, 0, 30, 255, 0, 30, 255, 0, 30, 255, 0,};
int cyan[27] = {255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255};
int purple[27] = {0, 127, 255, 0, 127, 255, 0, 127, 255, 0, 127, 255, 0, 127, 255, 0, 127, 255, 0, 127, 255, 0, 127, 255, 0, 127, 255};

int light_orange[27] = {50, 255, 0, 50, 255, 0, 50, 255, 0, 50, 255, 0, 50, 255, 0, 50, 255, 0, 50, 255, 0, 50, 255, 0, 50, 255, 0};
int dark_blue[27] = {0, 0, 75, 0, 0, 75, 0, 0, 75, 0, 0, 75, 0, 0, 75, 0, 0, 75, 0, 0, 75, 0, 0, 75, 0, 0, 75,};
int magenta[27] = {0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255};

int yellow[27] = {255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0};
int faint_blue[27] = {0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15};
int pink[27] = {0, 255, 127, 0, 255, 127, 0, 255, 127, 0, 255, 127, 0, 255, 127, 0, 255, 127, 0, 255, 127, 0, 255, 127, 0, 255, 127};
int off[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int speed1[27] = {0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 50, 50, 50, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255};
int speed2[27] = {0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 50, 50, 50, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0};

int twinkle1[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int twinkle2[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int twinkleRestore[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int invert1[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int wave1[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int wave2[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int wave3[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int wave4[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int wave5[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int asynWave1[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave2[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave3[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave4[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave5[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave6[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave7[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int asynWave8[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Testing LED strip color arrays
// Set one of these equal to a pre-made color array for easy access to colors
// For example, "memcpy(grb1, green, sizeof(grb1));" will output green to LED Strip 1

int grb1[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int grb2[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int grb3[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int previousPanel = 4;
int previousColor[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// These arrays hold the converted values of the 27-element color array into the binary representation for easy access
// to writing HIGH or LOW to the LED pixels to actually output the correct color for each LED

int binaryGRB1[648] = {0};
int binaryGRB2[648] = {0};
int binaryGRB3[648] = {0};

int check = 0;

/* This function converts the decimal representation of a color from an array 
 * grb[27] and places it into another array binaryGRB[648] as the binary 
 * representation of the same color. */

void convertDecToBin(int grb[], int binaryGRB[]) {
    int i;
    int j;
    
    int check = 0b11111111;
    int binaryIndex = 0;
    
    for (i = 0; i < 27; i++) {
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
    for (i = 0; i < 648; i++) {
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

void speed(void) {
    while(1) {
        writeColorToPanel(previousPanel, speed1);
        wait(100);
        writeColorToPanel(previousPanel, off);
        wait(100);
        writeColorToPanel(previousPanel, speed1);
        wait(100);
        writeColorToPanel(previousPanel, off);
        wait(100);
        writeColorToPanel(previousPanel, speed2);
        wait(100);
        writeColorToPanel(previousPanel, off);
        wait(100);
        writeColorToPanel(previousPanel, speed2);
        wait(100);
        writeColorToPanel(previousPanel, off);
        wait(100);
    }
}

void invert(void) {
    int i = 0;
    memcpy(invert1, previousColor, sizeof(invert1));
    for (i = 0; i < 27; i++) {
        invert1[i] = invert1[i] - 255;
        if (invert1[i] < 0) {
            invert1[i] = invert1[i] * (-1);
        }
    }
    
    while(1) {
        writeColorToPanel(previousPanel, invert1);
    }
}

void twinkle(void) {
    int i = 0;
    memcpy(twinkle2, previousColor, sizeof(twinkleRestore));
    
    for (i = 0; i < 27; i++) {
        twinkle2[i] = twinkle2[i] - 255;
        if (twinkle2[i] < 0) {
            twinkle2[i] = twinkle2[i] * (-1);
        }
    }
    
    while(1) {
        memcpy(twinkleRestore, previousColor, sizeof(twinkleRestore));
        memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
        
        twinkle1[3] = twinkle2[3];
        twinkle1[4] = twinkle2[4];
        twinkle1[5] = twinkle2[5];
        twinkle1[24] = twinkle2[24];
        twinkle1[25] = twinkle2[25];
        twinkle1[26] = twinkle2[26];
        writeColorToPanel(previousPanel, twinkle1);
        wait(1000);
        
        memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
        twinkle1[9] = twinkle2[9];
        twinkle1[10] = twinkle2[10];
        twinkle1[11] = twinkle2[11];
        twinkle1[0] = twinkle2[0];
        twinkle1[1] = twinkle2[1];
        twinkle1[2] = twinkle2[2];
        writeColorToPanel(previousPanel, twinkle1);
        wait(1000);
        
        memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
        twinkle1[15] = twinkle2[15];
        twinkle1[16] = twinkle2[16];
        twinkle1[17] = twinkle2[17];
        twinkle1[6] = twinkle2[6];
        twinkle1[7] = twinkle2[7];
        twinkle1[8] = twinkle2[8];
        writeColorToPanel(previousPanel, twinkle1);
        wait(1000);
        
        memcpy(twinkle1, twinkleRestore, sizeof(twinkle1));
        twinkle1[21] = twinkle2[21];
        twinkle1[22] = twinkle2[22];
        twinkle1[23] = twinkle2[23];
        twinkle1[18] = twinkle2[18];
        twinkle1[19] = twinkle2[19];
        twinkle1[20] = twinkle2[20];
        writeColorToPanel(previousPanel, twinkle1);
        wait(1000);
    }
}

/* This function is a dynamic function that blinks a selected LED strip, acting
 * as a strobe event for the LEDs. */

void seizure(void) { 
    while(1){
        writeColorToPanel(previousPanel, previousColor);   
        wait(30);

        writeColorToPanel(previousPanel, off);
        wait(30);
    }
}

void fade() {
    int G = 0;
    int R = 0;
    int B = 0;
    int green = 0;
    int red = 0;
    int blue = 0;
    int i = 0;
    //int color[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for(i = 0; i < 2; i++) {
        if(i == 0) {
            int G = previousColor[i];

        }

        else if(i == 1) {
            int R = previousColor[i];

        }

        else{
            int R = previousColor[i];

        } 
    }

    green = G;
    red = R;
    blue = B;
    int j = 0;


    while(1) {
        for(i = 0; i < 255; i++) {

            int color[27] = {G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B};
            writeColorToPanel(previousPanel, color);

            if(G != 255) {
                G++;
            }

            if(R != 255) {
                R++;
            }

            if(B != 255) {
                B++;
            }
        }

        for(i = 255; i > 0; i--) {
            int color[27] = {G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B, G, R, B};
            writeColorToPanel(previousPanel, color);
            if(G != green) {
                G--;
            }

            if(R != red) {
                R--;
            }

            if(B != blue) {
                B--;
            }
        }
        //wait(1000);
    }
}

void wave(void) {
    int i = 0;
    memcpy(wave1, previousColor, sizeof(wave1));
    memcpy(wave2, previousColor, sizeof(wave1));
    memcpy(wave3, previousColor, sizeof(wave1));
    memcpy(wave4, previousColor, sizeof(wave1));
    memcpy(wave5, previousColor, sizeof(wave1));
    
    for (i = 0; i < 27; i++) {
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
    
    while(1){
        writeColorToPanel(previousPanel, wave1);
        wait(200);
        writeColorToPanel(previousPanel, wave2);
        wait(200);
        writeColorToPanel(previousPanel, wave3);
        wait(200);
        writeColorToPanel(previousPanel, wave4);
        wait(200);
        writeColorToPanel(previousPanel, wave5);
        wait(200);
        writeColorToPanel(previousPanel, wave4);
        wait(200);
        writeColorToPanel(previousPanel, wave3);
        wait(200);
        writeColorToPanel(previousPanel, wave2);
        wait(200);
    }
}

//void fade() {
//    int G = 0;
//    int R = 0;
//    int B = 0;
//
//    int i = 0;
//
//    int color[27] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//
//
//    int j = 0;
//
//    while(1) {
//        for(i = 0; i < 255; i++) {
//            for (j = 0; j <= 25; j+=3){
//                color[j] = R;
//            }
//            writeColorToPanel(previousPanel, color);
//            R++; 
//        } 
//        for(i = 255; i > 0; i--) {
//            for (j = 0; j <= 25; j+=3){
//                color[j] = R;
//            }
//            writeColorToPanel(previousPanel, color);
//
//            R--;
//        }

void asynWave(void) {
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
    
    while(1) {
        writeColorToPanel(previousPanel, asynWave1);
        wait(100);
        writeColorToPanel(previousPanel, asynWave2);
        wait(100);
        writeColorToPanel(previousPanel, asynWave3);
        wait(100);
        writeColorToPanel(previousPanel, asynWave4);
        wait(100);
        writeColorToPanel(previousPanel, asynWave5);
        wait(100);
        writeColorToPanel(previousPanel, asynWave6);
        wait(100);
        writeColorToPanel(previousPanel, asynWave7);
        wait(100);
        writeColorToPanel(previousPanel, asynWave8);
        wait(100);
        writeColorToPanel(previousPanel, asynWave7);
        wait(100);
        writeColorToPanel(previousPanel, asynWave6);
        wait(100);
        writeColorToPanel(previousPanel, asynWave5);
        wait(100);
        writeColorToPanel(previousPanel, asynWave4);
        wait(100);
        writeColorToPanel(previousPanel, asynWave3);
        wait(100);
        writeColorToPanel(previousPanel, asynWave2);
        wait(100);
    }
}

/* This function sets up the PIC24FJ64GA002 as needed. Note that the necessary
 RAx pins must be activated in this function. */

void LedStrip_Setup(void){
    
    TRISA = 0b1111111111100000;  //and port A to outputs
    LATA = 0x0010;               //Set all of port A to HIGH
    
    writeColorToPanel(4, off);
    wait(500);
}

///* This is a standard main function to control the operation of the lamp xD */
//
//int main() {
//    setup();
//    previousPanel = 1;
//    writeColorToPanel(previousPanel, blue);
//    previousPanel = 2;
//    writeColorToPanel(previousPanel, green);
//    previousPanel = 3;
//    writeColorToPanel(previousPanel, red);
//    previousPanel = 4;
//    asynWave();
//    //rainbow();
//    //previousPanel = 4;
//    //rainbow();
//    //wait(500);
//    //fade();
//    //invert();
//    //writeColorToPanel(4, blue);
//    
//    
//    while(1);
//}
