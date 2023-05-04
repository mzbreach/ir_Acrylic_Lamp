/* 
 * File:   I2C_LCD.c
 * Project: IR Acrylic Lamp
 */

#include "xc.h"
#include "string.h"
#include <stdlib.h>

void lcd_init(void){
    I2C2BRG = 157;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    
    delay_ms(50); //allow vdd to stabilize
    
    lcd_cmd(0b00111000);
    lcd_cmd(0b00111001);
    lcd_cmd(0b00010100);
    lcd_cmd(0b01110000);
    lcd_cmd(0b01010110);
    lcd_cmd(0b01101100);
    
    delay_ms(200);
    
    lcd_cmd(0b00111000);
    lcd_cmd(0b00001100);
    lcd_cmd(0b00000001);
    
    delay_ms(1);
}

void lcd_cmd(int command){
    //send START
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01111100;//slave address of R/nW bit
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b00000000;//send high byte
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = command;//send package
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1; // send stop
    while(I2C2CONbits.PEN == 1);
    
    //while(IFS3bits.MI2C2IF == 0);
    //^ also an option (general purpose)
    
    //send Address a nd write command
    //send high byte (always 0x00)
    //Send package
    //send stop
}

void delay_ms(unsigned int ms){
    while(ms-- > 0){
        asm("repeat #15998"); //delay 1 ms (every loop))
        asm("nop");
    }
}

void lcd_printChar(char letter){
    
    I2C2CONbits.SEN = 1;//start sequence
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01111100;//slave address of R/nW bit
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = 0b01000000;//send high byte RS = 1
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = letter;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1; // send stop
    while(I2C2CONbits.PEN == 1);
    
}

void lcd_setCursor(char x, char y){
    lcd_cmd(((0x40 * x) + y) + 0b10000000);
}

void lcd_printStr(const char myStr[]){
    int i;
    for(i = 0; i < strlen(myStr); i++){
        lcd_printChar(myStr[i]);
    }
}

void moveRight(void){
    lcd_cmd(0b00011100);
}

void moveLeft(void){
    lcd_cmd(0b00011000);
}
