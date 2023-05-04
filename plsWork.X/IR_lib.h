/* 
 * File:   IR_lib.h
 * Project: IR Acrylic Lamp
 */

#ifndef IR_LIB_H
#define	IR_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif


void IR_Setup(void);
void TesterLEDSetup(void);
void decrypt(void);
void displayDecypher(void);
void leadSignalRecieved(unsigned long long int leadSignalTime);

#ifdef	__cplusplus
}
#endif

#endif	/* IR_LIB_H */

