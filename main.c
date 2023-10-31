#include <msp430.h> 
#include <stdio.h>
#include "LCD.h"
#include "Simple-PWM.h"
#include "Serial.h"
#include "Keypad.h"

#define period 10


/**
 * main.c
 */

int main(void)
{
     WDTCTL = WDTPW | WDTHOLD;                 // Stop watchdog timer

     Serial_Init();                 // Inbuilt function for initializing serial communication

     // I2C communication – Used B1 from eUSCI (Universal Serial Communication Interface
             UCB1CTLW0 |= UCSWRST;                   // Reset eUSCI register to
                                                     //default
             UCB1CTLW0 |= UCSSEL_3;                  // Select clock input SMCLK i.e., 1MHz clock
             UCB1BRW = 10;                           // Control the Bit Rate and baud rate = SMCLK / 10  for SMCLK=100 KHz)
             UCB1CTLW0 |= UCMODE_3;                  //Select mode as I2C
             UCB1CTLW0 |= UCMST;                     //Select Master mode enabled
             UCB1CTLW0 |= UCTR;                      //Transmission enabled
             UCB1I2CSA = 0x0027;                     // Slave address for data transmission
             UCB1CTLW1 |= UCASTP_2;                  // Automatic stop generated
                                                 // after 0x0001 is reached and 
                                               // set interrupt flag 
             UCB1TBCNT = 0x0001;                     // Send 1 byte of data
             UCB1CTL1 &= ~UCSWRST;                   // Removes from Reset mode
             UCB1IE |= UCTXIE0;                      //Enable interrupt to indicate completion of transmission

         // Configure GPIO
             // Interface LCD to I2C
                 P4SEL1 &= ~BIT7;                         // P4.7  SCL
                 P4SEL0 |= BIT7;
                 P4SEL1 &= ~BIT6;                         // P4.6   SDA
                 P4SEL0 |= BIT6;

                 P4DIR |= BIT0;
                 LCD_Screen &= ~BIT0;

         // Configure Keypad Interface
                 P1DIR = 0x0F; // 00001111 - > Set P1.0, P1.1, P1.2 and P1.3 as Output and P1.4, P1.5, P1.6 and 1.7 as Input pin
                 P1REN = 0xFF; // Set all P1 pins as Pull up Register enable
                 P1OUT = 0xF0; // Set P1 MSB 4 bits as Out Register.

     PM5CTL0 &= ~LOCKLPM5;  \\ Remove from high impedance mode
     __enable_interrupt();

     
     unsigned char string[17] = "         ";
     unsigned int digits[3] = {0,0,0};
     unsigned int duty = 0;
     unsigned int count=0;
     unsigned int buffer = 0;

     // Initialize PWM 
         PWM myPWM = Init_PWM(0, period, "P5.1");

     // Initialize LCD Display for default print status
         LCD_init(0);
         LCD_Clear(0);
         sprintf(string, "Waiting for");
         LCD_print_string(string);
         LCD_line(2);
         sprintf(string, "input...");
         LCD_print_string(string);

     // Main 
     while(1){
         // Wait for button to be pushed (Keypad input)
         while((Serial_Received != 1)&&(buffer != END))
             {
             // Poll for key
              count = get_key();
              if(count != 0) // If a key is pressed
                  {
                      // Store it in the buffer
                      buffer = __Key_Val[count];

                      // Storing value as digits
                     if(buffer != END){
                      digits[2] = digits[1];
                      digits[1] = digits[0];
                      digits[0] = buffer;
                      }
                  }
             }

         // Set Max input as 100
             if((Serial_Received == 1 )&&(Serial_In > 100)) duty = 100;
             else duty = Serial_In;
             if(buffer == END){
                 if((duty = digits[2]*100 + digits[1]*10 + digits[0]) >100){
                     duty = 100;
                 }
             }
         // Reset Buffer and digits[]
             buffer = 0;
             digits[0]=0;
             digits[1]=0;
             digits[2]=0;

         // Display keypad input percentage on LCD
             LCD_Clear();
             LCD_line(1);

             // Display speed %
             sprintf(string, "%d%%", duty);
             LCD_print_string(string);

         // Set PWM duty cycle
             Adjust_DutyCycle(duty/100.0, myPWM);
             Serial_Received = 0;

     }
     return 0;
}
