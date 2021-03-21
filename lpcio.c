/*
 * lpcio.c
 *
 *  Created on: 20 march 2021
 *      Author: Simone Arcari
 */

#include "lpcio.h"
#include "lpc1769_registri.h"

void pinMode(int pin, pin_status status, pin_port port) {
/*****************************************************************************
 *
 * Description:
 *    Set the state of the desired pin in output or input
 *
 * Parameters:
 *    [in] pin - pin number to be set
 *    [in] status - status of the pin to be set (OUTPUT) or (INPUT)
 *    [in] port - port of the respective pin to be set
 *
 ****************************************************************************/
	int number = 1<<pin;

	switch(status)
    {
    	case OUTPUT:
    		switch(port)
    		{
    			case zero:
    				FIO0DIR |= number;
    			break;

    			case one:
    			    FIO1DIR |= number;
    			break;

    			case two:
    			    FIO2DIR |= number;
    			break;

    			case three:
    			    FIO3DIR |= number;
    			break;
    		}
    	break;

    	case INPUT:
    		switch(port)
    		{
    			case zero:
    				FIO0DIR &= ~number;
    			break;

    			case one:
    			    FIO1DIR &= ~number;
    			break;

    			case two:
    			    FIO2DIR &= ~number;
    			break;

    			case three:
    			    FIO3DIR &= ~number;
    			break;
    		}
    	break;
    }
}

void digitalWrite(int pin, pin_value value,  pin_port port) {
/*****************************************************************************
 *
 * Description:
 *    Set the logic state of the desired pin high or low
 *
 * Parameters:
 *    [in] pin - pin number to be set
 *    [in] value - value of the pin to be set (HIGH) or (LOW)
 *    [in] port - port of the respective pin to be set
 *
 ****************************************************************************/
	int number = 1<<pin;

    switch(value)
    {
    	case HIGH:
    		switch(port)
    		{
    			case zero:
    				FIO0SET |= number;
    			break;

    			case one:
    				FIO1SET |= number;
    			break;

    			case two:
    				FIO2SET |= number;
    			break;

    			case three:
    				FIO3SET |= number;
    			break;
    		}
    	break;

    	case LOW:
    		switch(port)
    		{
    			case zero:
    				FIO0CLR |= number;
    			break;

    			case one:
    				FIO1CLR |= number;
    			break;

    			case two:
    				FIO2CLR |= number;
    			break;

    			case three:
    				FIO3CLR |= number;
    			break;
    		}
    	break;
    }
}

void delayMs(unsigned short delayInMs) {
/*****************************************************************************
 *
 * Description:
 *    Delay execution by a specified number of milliseconds by using
 *    timer #1
 *    A polled implementation
 *
 * Parameters:
 *    [in] delayInMs - the number of milliseconds to delay
 *
 ****************************************************************************/
	TIMER1_TCR = 0x02;            					// stop and reset timer
	TIMER1_PR  = 0x00;            					// set prescaler to zero
	TIMER1_MR0 = (CORE_CLK/4) / 1000 * delayInMs;   // load MR0 with the time to delay
	TIMER1_IR  = 0xff;            					// reset all interrupt flags
	TIMER1_MCR = 0x04;            					// stop timer on match
	TIMER1_TCR = 0x01;            					// start timer

    while (TIMER1_TCR & 0x01);	 					//wait until delay time has elapsed
}

void delayUs(unsigned short delayInUs) {
/*****************************************************************************
 *
 * Description:
 *    Delay execution by a specified number of microseconds by using
 *    timer #1
 *    A polled implementation
 *
 * Parameters:
 *    [in] delayInUs - the number of microseconds to delay
 *
 ****************************************************************************/
	TIMER1_TCR = 0x02;          						//stop and reset timer
	TIMER1_PR  = 0x00;          						//set prescaler to zero
	TIMER1_MR0 = (CORE_CLK/4) / 1000000 * delayInUs;    // load MR0 with the time to delay
	TIMER1_IR  = 0xFF;          						//reset all interrupt flags
	TIMER1_MCR = 0x04;          						//stop timer on match
	TIMER1_TCR = 0x01;          						//start timer

	while (TIMER1_TCR & 0x01);	 						//wait until delay time has elapsed
}
