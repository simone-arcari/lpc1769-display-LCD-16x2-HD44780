/*
===============================================================================
 Name        : lpc1769_HD44780.c
 Author      : Simone Arcari
 Version     :
 Copyright   : none
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "HD44780.h"
#include "lpcio.h"


int main(void) {
	/* SETUP LCD */
	lcd_pin(13, 28, 27, 22, 21, 3, 2, two, zero, zero, zero, zero, zero, zero);
	init_LCD();

	putCommand(DISPLAY_CLEAR_CMD);          					// clear display
	setCursor(0,0);    											// first line, first column, 1st position
	writeString((unsigned char*)"Display LCD 4bit", false);		// message

	delayMs(1000);

    while(1) {
    	static int number = 0;

    	setCursor(1,0);    										// second line, fist column
    	writeString((unsigned char*)"Count: ", false);			// message
    	writeNumber(number);									// send number

    	number++;

    	delayMs(500);
    }
    return 0 ;
}
