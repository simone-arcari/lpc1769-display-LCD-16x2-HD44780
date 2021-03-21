/*
 *  lpc1769_registri.h
 *
 *  Created on: 20 march 2021
 *      Author: Simone Arcari
 */

#ifndef LPC1769_REGISTRI_H_
#define LPC1769_REGISTRI_H_


#define CORE_CLK 96000000	// ARM core clock


// PORT 0 REGISTERS
#define FIO0DIR *(volatile unsigned long*) 0x2009C000		// set the pins in output(1) or in input(0)
#define FIO0MASK *(volatile unsigned long*) 0x2009C010		// set a mask on the desired pins
#define FIO0SET *(volatile unsigned long*) 0x2009C018		// set the pins to logic level high(1)
#define FIO0CLR *(volatile unsigned long*) 0x2009C01C		// set the pins to low logic level(1)
#define FIO0PIN *(volatile unsigned long*) 0x2009C014		// set the pins to high logic level(1) and to low logic level(0), it is used to check the status of the pins 1 = on 0 = off


// PORT 1 REGISTERS
#define FIO1DIR *(volatile unsigned long*) 0x2009C020		// set the pins in output(1) input(0)
#define FIO1MASK *(volatile unsigned long*) 0x2009C030		// set a mask on the desired pins
#define FIO1SET *(volatile unsigned long*) 0x2009C038		// set the pins to logic level high(1)
#define FIO1CLR *(volatile unsigned long*) 0x2009C03C		// set the pins to low logic level(1)
#define FIO1PIN *(volatile unsigned long*) 0x2009C034		// set the pins to high logic level(1) and to low logic level(0), it is used to check the status of the pins 1 = on 0 = off


// PORT 2 REGISTERS
#define FIO2DIR *(volatile unsigned long*) 0x2009C040		// set the pins in output(1) input(0)
#define FIO2MASK *(volatile unsigned long*) 0x2009C050		// set a mask on the desired pins
#define FIO2SET *(volatile unsigned long*) 0x2009C058		// set the pins to logic level high(1)
#define FIO2CLR *(volatile unsigned long*) 0x2009C05C		// set the pins to low logic level(1)
#define FIO2PIN *(volatile unsigned long*) 0x2009C054		// set the pins to high logic level(1) and to low logic level(0), it is used to check the status of the pins 1 = on 0 = off



// PORT 3 REGISTERS
#define FIO3DIR *(volatile unsigned long*) 0x2009C060		// set the pins in output(1) input(0)
#define FIO3MASK *(volatile unsigned long*) 0x2009C070		// set a mask on the desired pins
#define FIO3SET *(volatile unsigned long*) 0x2009C078		// set the pins to logic level high(1)
#define FIO3CLR *(volatile unsigned long*) 0x2009C07C		// set the pins to low logic level(1)
#define FIO3PIN *(volatile unsigned long*) 0x2009C074		// set the pins to high logic level(1) and to low logic level(0), it is used to check the status of the pins 1 = on 0 = off



// PORT 4 REGISTERS
#define FIO4DIR *(volatile unsigned long*) 0x2009C080		// set the pins in output(1) input(0)
#define FIO4MASK *(volatile unsigned long*) 0x2009C090		// set a mask on the desired pins
#define FIO4SET *(volatile unsigned long*) 0x2009C098		// set the pins to logic level high(1)
#define FIO4CLR *(volatile unsigned long*) 0x2009C09C		// set the pins to low logic level(1)
#define FIO4PIN *(volatile unsigned long*) 0x2009C094		// set the pins to high logic level(1) and to low logic level(0), it is used to check the status of the pins 1 = on 0 = off



// TIMER 1 REGISTERS
#define TIMER1_IR *(volatile unsigned long*) 0x40008000		// Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending
#define TIMER1_TCR *(volatile unsigned long*) 0x40008004	// Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR
#define TIMER1_PR  *(volatile unsigned long*) 0x4000800C	// Prescale Register. When the Prescale Counter (below) is equal to this value, the next clock increments the TC and clears the PC
#define TIMER1_MCR *(volatile unsigned long*) 0x40008014	// Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs
#define TIMER1_MR0 *(volatile unsigned long*) 0x40008018	// Match Register 0. MR0 can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR0 matches the TC


#endif /* LPC1769_REGISTRI_H_ */
