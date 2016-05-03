
/*****************************************************************************

	-> main file of the Brooklyn College Watt Balance software controller <-

	Code written, built, and debugged with TI Code Composer Studio 6.1.2
	Compiled with TI ARM Compiler 5.2.7
	Tested with TI TM4C123GH6PM Microcontroller on Tiva C-Series LaunchPad

	Authors:

	Anthony Pervolarakis
	Stephen Lin
	Daniel Singer

	Faculty Advisor: A. Murray Gross

 ***********

	This software is to be submitted for the partial fulfillment of
	CISC 4900 Project at CUNY Brooklyn College.

	The software will be used to control various hardware peripherals of the
	Tiva C-Series Launchpad via software calls to the TM4C microcontroller.
	The peripherals will control and measure different components of a
	Watt Balance apparatus. The hardware will control the operation of lasers,
	electromagnetic coils, and measurement of electrical signals via their
	respective electronic circuits.

 ***********

	Header Files:
					control.h
					console.h

	Source Files:
					board_init.c
					control.c
					console.c

 ***********

 	main.c:

	A) Calls initialization routine for board peripherals.
	B) Infinite Loop for console I/O
	C) TODO: Analog Measurements ?
	D) TODO: Measurements and Computations ?

 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "control.h"
#include "console.h"
#include "util/cmdline.h"
#include "util/uartstdio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

static int RUNNING;

void initClock(void);

/*
 * Input buffer for the command line interpreter.
 */

static char g_cInput[CONSOLE_BUF_SIZE];

void messages(char * mystring)
{

	UARTprintf("%s \n",mystring);

	return;
}

int main(void){

	int32_t commandStatus;

	systemInit();
	board_INIT();
	initClock();
	RUNNING = true;
	TimerEnable(TIMER0_BASE,TIMER_A);

	while(1){

		/*help
		 * Commandline input routine from UART
		 */

		UARTgets(g_cInput,sizeof(g_cInput));

		RUNNING = false; // Not sure where to put this yet

		/*
		 * Pass the line from the user to the command processor.
		 * It will be parsed and valid commands executed.
		 */

		commandStatus = CmdLineProcess(g_cInput);

		/*
		 * If command is not in command array, bad command
		 */

		if(commandStatus == CMDLINE_BAD_CMD){

			UARTprintf("Bad command!\n>");
		}

		/*
		 * If command has too many arguments(max 8), bad command
		 */

		else if(commandStatus == CMDLINE_TOO_MANY_ARGS){

			UARTprintf("Too many arguments for command processor!\n>");
		}

	}

}

void initClock(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT); /* 32 bits is enough. */
	uint32_t ui32Period = SysCtlClockGet() * 1.5 / 1024;

	TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period-1);

	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

int continueRunning(void)
{

	if(!RUNNING)
	{
		return (true);
	}

	uint32_t ui32Period = SysCtlClockGet() * 1.5 / 1024;
	TimerLoadSet(TIMER0_BASE,TIMER_A,ui32Period-1);
	TimerEnable(TIMER0_BASE, TIMER_A);

	return (false);
}

void clockInterrupt(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	if(continueRunning()) return;

	static int busy=false;                 /* last interrupt request not        */
		                                   /* completely served                 */

	if (busy!=false)
	{
		messages("clockInterrupt: Overrun detected.");
	}

	busy=true;

	// TODO: increment through sine table

	busy=false;

	return;
}
