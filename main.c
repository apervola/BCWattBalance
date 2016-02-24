
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
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "control.h"
#include "console.h"
#include "util/cmdline.h"
#include "util/uartstdio.h"

/*
 * Input buffer for the command line interpreter.
 */

static char g_cInput[CONSOLE_BUF_SIZE];

int main(void){

	int32_t commandStatus;

	board_INIT();

	while(1){

		/*
		 * Commandline input routine from UART
		 */

		UARTgets(g_cInput,sizeof(g_cInput));

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
