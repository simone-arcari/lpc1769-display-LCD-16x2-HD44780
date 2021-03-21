/*
 * HD44780.c
 *
 *  Created on: 20 march 2021
 *      Author: Simone Arcari
 */

#include "HD44780.h"
#include "lpcio.h"

int RegisterSelect, ReadWrite, Enable;
int DataLine4, DataLine5, DataLine6, DataLine7;
int rs_Port, rw_Port, en_Port;
int d4_Port, d5_Port, d6_Port, d7_Port;

void lcd_pin(int rs, int rw, int en, int d4, int d5, int d6, int d7, pin_port rsP, pin_port rwP, pin_port enP, pin_port d4P, pin_port d5P, pin_port d6P, pin_port d7P) {
/*****************************************************************************
 *
 * Description:
 *    Attach the pins of the LCD to the desired pins of the lpc1769 board
 *
 * Parameters:
 *    [in] rs - pin number to be connect to LCD register select pin
 *    [in] rw - pin number to be connect to LCD read/write pin
 *    [in] en - pin number to be connect to LCD enable pin
 *    [in] d4 - pin number to be connect to LCD data4 pin
 *    [in] d5 - pin number to be connect to LCD data5 pin
 *    [in] d6 - pin number to be connect to LCD data6 pin
 *    [in] d7 - pin number to be connect to LCD data7 pin
 *    [in] rsP - port of the respective pin to be connect to LCD register select pin
 *    [in] rwP - port of the respective pin to be connect to LCD read/write pin
 *    [in] enP - port of the respective pin to be connect to LCD enable pin
 *    [in] d4P - port of the respective pin to be connect to LCD data4 pin
 *    [in] d5P - port of the respective pin to be connect to LCD data5 pin
 *    [in] d6P - port of the respective pin to be connect to LCD data6 pin
 *    [in] d7P - port of the respective pin to be connect to LCD data7 pin
 *
 ****************************************************************************/
	RegisterSelect = rs;
	ReadWrite = rw;
	Enable = en;

	DataLine4 = d4;
	DataLine5 = d5;
	DataLine6 = d6;
	DataLine7 = d7;

	rs_Port = rsP;
	rw_Port = rwP;
	en_Port = enP;

	d4_Port = d4P;
	d5_Port = d5P;
	d6_Port = d6P;
	d7_Port = d7P;
}

void init_LCD(void) {
/*****************************************************************************
 *
 * Description:
 *    Initializes the LCD display with basic settings (4bit mode)
 *
 ****************************************************************************/
	pinMode(RegisterSelect, OUTPUT, rs_Port);
	pinMode(ReadWrite, OUTPUT, rw_Port);
	pinMode(Enable, OUTPUT, en_Port);

	pinMode(DataLine4, OUTPUT, d4_Port);
	pinMode(DataLine5, OUTPUT, d5_Port);
	pinMode(DataLine6, OUTPUT, d6_Port);
	pinMode(DataLine7, OUTPUT, d7_Port);

	putCommand_hf(0x30);						// sequence for initialization
	putCommand_hf(0x30);    					// ----
	putCommand_hf(0x20);    					// ----

	putCommand(FOUR_BIT_TWO_LINE_5x8_CMD);		// selecting 16 x 2 LCD in 4bit mode with 5x7 pixels
    putCommand(DISP_ON_CUR_OFF_BLINK_OFF_CMD);	// display ON cursor OFF blinking OFF
    putCommand(DISPLAY_CLEAR_CMD);          	// clear display
    putCommand(ENTRY_MODE_INC_NO_SHIFT_CMD);    // cursor auto increment
    putCommand(0x80);          					// 1st line 1st location of LCD 0 offset 80h
}

void clear_line(void) {
/*****************************************************************************
 *
 * Description:
 *    Sets all data lines to a low logic level
 *
 ****************************************************************************/
	int dataLine[4] = {DataLine4, DataLine5, DataLine6, DataLine7};
	int dataLinePort[4] = {d4_Port, d5_Port, d6_Port, d7_Port};

	for(int i=0; i<=3; i++) {
		digitalWrite(dataLine[i], LOW, dataLinePort[i]);
	}
}

void toggle(void) {
/*****************************************************************************
 *
 * Description:
 *     Latching data in to LCD data register using high to Low signal
 *
 ****************************************************************************/
	digitalWrite(Enable, HIGH, en_Port);
	delayMs(2);
    digitalWrite(Enable, LOW, en_Port);
}

void sendUpperByte(char data_to_LCD) {
/*****************************************************************************
 *
 * Description:
 *     Sends only the upper part of a byte
 *
 * Parameters:
 *    [in] data_to_LCD - byte to be sent to the LCD
 *
 ****************************************************************************/
    if(data_to_LCD & 0x10)
    	digitalWrite(DataLine4, HIGH, d4_Port);
    else
    	digitalWrite(DataLine4, LOW, d4_Port);

    if(data_to_LCD & 0x20)
    	digitalWrite(DataLine5, HIGH, d5_Port);
    else
    	digitalWrite(DataLine5, LOW, d5_Port);

    if(data_to_LCD & 0x40)
    	digitalWrite(DataLine6, HIGH, d6_Port);
    else
    	digitalWrite(DataLine6, LOW, d6_Port);

    if(data_to_LCD & 0x80)
    	digitalWrite(DataLine7, HIGH, d7_Port);
    else
    	digitalWrite(DataLine7, LOW, d7_Port);
}

void sendLowerByte(char data_to_LCD) {
/*****************************************************************************
 *
 * Description:
 *     Sends only the lower part of a byte
 *
 * Parameters:
 *    [in] data_to_LCD - byte to be sent to the LCD
 *
 ****************************************************************************/
    if(data_to_LCD & 0x01)
    	digitalWrite(DataLine4, HIGH, d4_Port);
    else
    	digitalWrite(DataLine4, LOW, d4_Port);

    if(data_to_LCD & 0x02)
    	digitalWrite(DataLine5, HIGH, d5_Port);
    else
    	digitalWrite(DataLine5, LOW, d5_Port);

    if(data_to_LCD & 0x04)
    	digitalWrite(DataLine6, HIGH, d6_Port);
    else
    	digitalWrite(DataLine6, LOW, d6_Port);

    if(data_to_LCD & 0x08)
    	digitalWrite(DataLine7, HIGH, d7_Port);
    else
    	digitalWrite(DataLine7, LOW, d7_Port);
}

void putCommand_hf(char data_to_LCD) {
/*****************************************************************************
 *
 * Description:
 *    Sends only the upper part of its command
 *
 * Parameters:
 *    [in] data_to_LCD - byte to be sent to the LCD
 *
 ****************************************************************************/
    digitalWrite(RegisterSelect, LOW, rs_Port); 	// selecting register as Command register
    digitalWrite(ReadWrite, LOW, rw_Port);			// selecting write mode
    clear_line();              						// clearing the 4 bits data line
    sendUpperByte(data_to_LCD);

    toggle();
}

void putCommand(char data_to_LCD) {
/*****************************************************************************
 *
 * Description:
 *    Sends the whole command
 *
 * Parameters:
 *    [in] data_to_LCD - byte to be sent to the LCD
 *
 ****************************************************************************/
    digitalWrite(RegisterSelect, LOW, rs_Port);		// selecting register as command register
    digitalWrite(ReadWrite, LOW, rw_Port);			// selecting write mode
    clear_line();                    				// clearing the 4 bits data line
    sendUpperByte(data_to_LCD);

    toggle();

    clear_line();                    				// clearing the 4 bits data line
    sendLowerByte(data_to_LCD);

    toggle();
}

void writeByte(char data_to_LCD) {
/*****************************************************************************
 *
 * Description:
 *    Sends the whole data to LCD (one byte)
 *
 * Parameters:
 *    [in] data_to_LCD - byte to be sent to the LCD
 *
 ****************************************************************************/
    digitalWrite(RegisterSelect, HIGH, rs_Port);	// selecting register as data register
    digitalWrite(ReadWrite, LOW, rw_Port);			// selecting write mode
    clear_line();                      				// clearing the 4 bits data line
    sendUpperByte(data_to_LCD);

    toggle();

    clear_line();                       			// clearing the 4 bits data line
    sendLowerByte(data_to_LCD);

    toggle();
}

void writeString(unsigned char LineOfCharacters[TOTAL_CHARACTERS_OF_LCD], char OverLenghtCharacters) {
/*****************************************************************************
 *
 * Description:
 *    Prints the desired string on the LCD display (multiple byte)
 *
 * Parameters:
 *    [in] LineOfCharacters[] - array containing the string to be printed
 *    [in] OverLenghtCharacters - flag to enable wrapping (true = wrapping ON) (false = wrapping OFF)
 *
 ****************************************************************************/
	unsigned char i=0, line=-1;

	while(LineOfCharacters[i] && i<TOTAL_CHARACTERS_OF_LCD) {
		if(OverLenghtCharacters) {
			if((i%LCD_LINE_LENGHT)==0)
				setCursor(++line, 0);
		}

		writeByte(LineOfCharacters[i]);
		i++;
	}
}

void writeNumber(int number) {
/*****************************************************************************
 *
 * Description:
 *    Prints the desired number (decimal integer) on the LCD display (multiple byte)
 *
 * Parameters:
 *    [in] number - number to be printed
 *
 ****************************************************************************/
    int index = 0, MAX_NUM_LEN = 10, temp;
    int digit[MAX_NUM_LEN];

    while(number != 0) {
        digit[index] = number%10;
        number/=10;
        index++;
    }

    if(index == 0) {
        writeByte(NUM_TO_CODE(0)); 	// print number zero
    }else {
        /* array inversion algorithm */
        int cycle;
        int comodo = index-1;
        for(cycle = 0; cycle < index-index/2; cycle++) {
            temp = digit[comodo];
            digit[comodo] = digit[cycle];
            digit[cycle] = temp;
            comodo--;
        }

        for(cycle = 0; cycle < index; cycle++) {
            writeByte(NUM_TO_CODE(digit[cycle]));
        }
    }
}

void lcd_rig_sh(void) {
/*****************************************************************************
 *
 * Description:
 *    At each function call the entire content printed on the LCD is shifted
 *    to the right of a box
 *
 ****************************************************************************/
	putCommand(DISPLAY_MOVE_SHIFT_RIGHT_CMD);      // command for right shift
	delayMs(100);
}

void lcd_lef_sh(void) {
/*****************************************************************************
 *
 * Description:
 *    At each function call the entire content printed on the LCD is shifted
 *    to the left of a box
 *
 ****************************************************************************/
	putCommand(DISPLAY_MOVE_SHIFT_LEFT_CMD);      // command for left shift
    delayMs(100);
}

void setCursor(unsigned char line, unsigned char col) {
/*****************************************************************************
 *
 * Description:
 *    Place the cursor in the desired position
 *
 * Parameters:
 *    [in] line - number of the line in which to place the cursor
 *    [in] col - number of the column in which to place the cursor
 *
 ****************************************************************************/
	unsigned char address;

	switch(line){
		case 0:
			address = 0x00;
			break;

		case 1:
			address = 0x40;
			break;

		case 2:
			address = 0x10;
			break;

		case 3:
			address = 0x50;
			break;

		default:
			address = 0x00;
			break;
	}

	if(col >= 0 && col <= LCD_LINE_LENGHT)
		address += col;

	putCommand(DDRAM_ADDRESS(address));
}
