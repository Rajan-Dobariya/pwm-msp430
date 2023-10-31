/*
 * LCD.h
 *
 *  Created on: Apr 19, 2022
 *      Author: Jake
 */
#ifndef LCD_H_
#define LCD_H_

    #define __delay_time 15
    #define LCD_Screen P4OUT



    unsigned int reverseBits(unsigned int num);
    void _4Bit_Send(unsigned command, unsigned cmd_signals);
    void _send(unsigned char x);
    void LCD_init();
    void LCD_print_string(unsigned char str[]);
    void LCD_line(int n);
    void LCD_Clear();

#endif /*LCD_H_*/
