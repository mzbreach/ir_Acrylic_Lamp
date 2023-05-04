/* 
 * File:   LedStrip_lib.h
 * Project: IR Acrylic Lamp
 */

#ifndef LEDSTRIP_LIB_H
#define	LEDSTRIP_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define ARRAY_SIZE 27
extern int panel; // Change this to change the LED strip

// These are the colors (kind of, not really) that should be used as parameters in combination with "panel"
// With these two parameters, it is a matter of calling functions to produce the correct combination/event
// Currently these color arrays have not been tested, so some colors might not be accurate
extern int color[ARRAY_SIZE];
extern int staticColor[ARRAY_SIZE];
extern int off[ARRAY_SIZE];

extern int speed1[ARRAY_SIZE];
extern int speed2[ARRAY_SIZE];

extern int twinkle1[ARRAY_SIZE];
extern int twinkle2[ARRAY_SIZE];
extern int twinkleRestore[ARRAY_SIZE];

extern int invert1[ARRAY_SIZE];

extern int wave1[ARRAY_SIZE];
extern int wave2[ARRAY_SIZE];
extern int wave3[ARRAY_SIZE];
extern int wave4[ARRAY_SIZE];
extern int wave5[ARRAY_SIZE];

extern int asynWave1[ARRAY_SIZE];
extern int asynWave2[ARRAY_SIZE];
extern int asynWave3[ARRAY_SIZE];
extern int asynWave4[ARRAY_SIZE];
extern int asynWave5[ARRAY_SIZE];
extern int asynWave6[ARRAY_SIZE];
extern int asynWave7[ARRAY_SIZE];
extern int asynWave8[ARRAY_SIZE];

// Testing LED strip color arrays
// Set one of these equal to a pre-made color array for easy access to colors
// For example, "memcpy(grb1, green, sizeof(grb1));" will output green to LED Strip 1

extern int grb1[ARRAY_SIZE];
extern int grb2[ARRAY_SIZE];
extern int grb3[ARRAY_SIZE];
extern int previousPanel;
extern int previousColor[ARRAY_SIZE];

// These arrays hold the converted values of the 27-element color array into the binary representation for easy access
// to writing HIGH or LOW to the LED pixels to actually output the correct color for each LED

extern int binaryGRB1[ARRAY_SIZE * 24];
extern int binaryGRB2[ARRAY_SIZE * 24];
extern int binaryGRB3[ARRAY_SIZE * 24];

extern int check;
extern char dynamicFctn;

void convertDecToBin(int grb[], int binaryGRB[]);
void writeBinToLED1(int binaryGRB[]);
void writeBinToLED2(int binaryGRB[]);
void writeBinToLED3(int binaryGRB[]);
void wait(int ms);
void masterStaticColorCreator(int state);
void writeColorToPanel(int panel, int color[]);
void rainbow(int state);
void speed(int state);
void invertSetup(void);
void invert(void);
void twinkleSetup(void);
void twinkle(int state);
void seizure(int state);
void fade();
void waveSetup(void);
void wave(int state);
void asynWaveSetup(void);
void asynWave(int state);
void LedStrip_Setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDSTRIP_LIB_H */

