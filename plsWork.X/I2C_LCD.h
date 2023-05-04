/* 
 * File:   I2C_LCD.h
 * Project: IR Acrylic Lamp
 */

#ifndef I2C_LCD_H
#define	I2C_LCD_H

#include <xc.h> 
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void lcd_init(void);
    
    void ledTest(void);

    void lcd_cmd(int command);

    void delay_ms(unsigned int ms);

    void lcd_printChar(char letter);

    void lcd_setCursor(char x, char y);

    void lcd_printStr(const char myStr[]);

    void moveRight(void);

    void moveLeft(void);

    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

