/* 
 * File:   LedStrip_lib.h
 * Author: jimen
 *
 * Created on April 26, 2023, 9:51 PM
 */

#ifndef LEDSTRIP_LIB_H
#define	LEDSTRIP_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
extern int panel; // Change this to change the LED strip

// These are the colors (kind of, not really) that should be used as parameters in combination with "panel"
// With these two parameters, it is a matter of calling functions to produce the correct combination/event
// Currently these color arrays have not been tested, so some colors might not be accurate

extern int green[27];
extern int red[27];
extern int blue[27];
extern int white[27];

extern int red_orange[27];
extern int light_green[27];
extern int light_blue[27];

extern int orange[27];
extern int cyan[27];
extern int purple[27];

extern int light_orange[27];
extern int dark_blue[27];
extern int magenta[27];

extern int yellow[27];
extern int faint_blue[27];
extern int pink[27];
extern int off[27];

extern int speed1[27];
extern int speed2[27];

extern int twinkle1[27];
extern int twinkle2[27];
extern int twinkleRestore[27];

extern int invert1[27];

extern int wave1[27];
extern int wave2[27];
extern int wave3[27];
extern int wave4[27];
extern int wave5[27];

extern int asynWave1[27];
extern int asynWave2[27];
extern int asynWave3[27];
extern int asynWave4[27];
extern int asynWave5[27];
extern int asynWave6[27];
extern int asynWave7[27];
extern int asynWave8[27];

// Testing LED strip color arrays
// Set one of these equal to a pre-made color array for easy access to colors
// For example, "memcpy(grb1, green, sizeof(grb1));" will output green to LED Strip 1

extern int grb1[27];
extern int grb2[27];
extern int grb3[27];
extern int previousPanel;
extern int previousColor[27];

// These arrays hold the converted values of the 27-element color array into the binary representation for easy access
// to writing HIGH or LOW to the LED pixels to actually output the correct color for each LED

extern int binaryGRB1[648];
extern int binaryGRB2[648];
extern int binaryGRB3[648];

extern int check;

void convertDecToBin(int grb[], int binaryGRB[]);
void writeBinToLED1(int binaryGRB[]);
void writeBinToLED2(int binaryGRB[]);
void writeBinToLED3(int binaryGRB[]);
void wait(int ms);
void writeColorToPanel(int panel, int color[]);
//void rainbow(void);
void invert(void);
void twinkle(void);
void seizure(void);
void fade();
void wave(void);
void asynWave(void);
void LedStrip_Setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDSTRIP_LIB_H */

