# pwm-msp430

Title: **PWM Motor Control**

Objective:

To control the speed of the motor by varying PWM based on the Keypad input using the **MSP-EXP430FR2355** microcontroller. i.e., 100% is full speed rotation and 50% is motor rotates with half the initial speed and 0% is stop. 


## Pseudocode for pwm-msp430

### Steps:

**Step 1**: Configure eUSCI register to enable I2C communication and set-up B1 register for I2C communication as interface between the system and LCD Display.\
**Step 2**: Configure 2x16 LCD Display to print the input string value and include the .h extension file to access in the main program.\
**Step 3**: Set-up a simple Pulse Width Modulator to determine the speed of the motor based on the varied input for duty cycle of the PWM.\
**Step 4**: Set-up Keypad interface to take input from the user and output to the microcontroller. This input decides the dutycycle for the PWM.\
**Step 5**: Interface all the modules in the above steps (‘LCD’, ‘PWM’, and ‘Keypad’ ) to communicate with one another.\
**Step 6**: Set the GPIO pins for Keypad and get the output from the user.\
**Step 7**: The Keypad output is used as input to PWM and also LCD display to show that duty cycle.\
**Step 8**: An interrupt is triggered every time a keypad input is detected, and the display screen changes based on the interrupt to display the current duty cycle.



## Output

[Video link](https://usfedu-my.sharepoint.com/:v:/g/personal/dobariya_usf_edu/EboUycxe2hJOmvgTOdpgy_YBDt9yOrQp6OCZDuuN1eTIeg)