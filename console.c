/*
 * console.c
 * Console function declarations
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/uart.h"
#include "console.h"
#include "control.h"
#include "util/cmdline.h"
#include "util/uartstdio.h"
#include "util/ustdlib.h"

/*****************************************************************************
 *
 * Table of valid command strings, functions calls, and help descriptions.
 * This format (array name and type) is specified and used by
 * the Command Line Processor to parse and call commands. A command can have
 * a maximum of 8 arguments.
 *
 *****************************************************************************/

tCmdLineEntry g_psCmdTable[] =
{
		{"laserAon" ,      CMD_laserAon,        " : Turn on Laser A" 	},
		{"laserBon" ,      CMD_laserBon,        " : Turn on Laser B"	},
		{"laserAoff",      CMD_laserAoff,       " : Turn off Laser A"	},
		{"laserBoff",	   CMD_laserBoff, 		" : Turn off Laser B"	},
		{"help",       	   CMD_help,       		" : Help Table"			},
		{"shutdown",       CMD_shutdown,       	" : Shutdown"			},
		{ 0, 0, 0 }
};



/*
 * Command: help
 * Print the help strings for all commands.
 */

int CMD_help(int argc, char **argv){

	int32_t i32Index;

	//
	// Start at the beginning of the command table
	//

	i32Index = 0;

	//
	// Get to the start of a clean line on the serial output.
	//
	UARTprintf("\nAvailable Commands\n------------------\n\n");

	//
	// Display strings until we run out of them.
	//
	while(g_psCmdTable[i32Index].pcCmd)
	{
		UARTprintf("%17s %s\n", g_psCmdTable[i32Index].pcCmd,
				g_psCmdTable[i32Index].pcHelp);
		i32Index++;
	}

	//
	// Leave a blank line after the help strings.
	//
	UARTprintf("\n");
	UARTprintf(">");

	return (0);
}

int CMD_laserAon(int argc, char **argv){

	enableLaserA();
	UARTprintf("\n");
	UARTprintf(">");

	return(0);
}

int CMD_laserAoff(int argc, char **argv){

	disableLaserA();
	UARTprintf("\n");
	UARTprintf(">");

	return 0;
}

int CMD_laserBon(int argc, char **argv){

	enableLaserB();
	UARTprintf("\n");
	UARTprintf(">");

	return 0;
}

int CMD_laserBoff(int argc, char **argv){

	disableLaserB();
	UARTprintf("\n");
	UARTprintf(">");

	return 0;
}

int CMD_shutdown(int argc, char **argv){

	disableLaserA();
	disableLaserB();
	UARTprintf("\n");
	UARTprintf(">");

	return(0);
}
