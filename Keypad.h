/*
 * Keypad.h
 *
 *  Created on: Apr 19, 2022
 *      Author: Jake
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

    #define keyport P1OUT //Keypad Port
    #define COL1 (0x10 & P1IN)
    #define COL2 (0x20 & P1IN)
    #define COL3 (0x40 & P1IN)
    #define COL4 (0x80 & P1IN)

    #define END 69

    // Functions
        unsigned int get_num(void);
        unsigned char get_key(void);
        extern unsigned int __Key_Val[];
        //void DelayMs(int Ms);


#endif /* KEYPAD_H_ */
