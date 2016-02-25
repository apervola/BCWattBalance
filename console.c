/*
 * console.c
 * Console function declarations
 * Command definitions
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
 * Structure of valid command strings, functions calls, and help descriptions.
 * This format is specified and used by the Command Line Processor to parse
 * and call commands. A command can have a maximum of 8 arguments. The structure
 * must be terminated by a null entry.
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

	int32_t cmdIndex; //index for the beginning of the command array

	cmdIndex = 0;

	/*
	 * Print a newline and begin formatted output for help table
	 */

	UARTprintf("\nAvailable Commands\n------------------\n\n");

	/*
	 * Display a formatted table of the command array with descriptions
	 * A 'help' table
	 */

	while(g_psCmdTable[cmdIndex].pcCmd)
	{
		UARTprintf("%17s %s\n", g_psCmdTable[cmdIndex].pcCmd,
				g_psCmdTable[cmdIndex].pcHelp);
		cmdIndex++;
	}

	/*
	 * Leave blank line after the help table
	 */

	UARTprintf("\n>");

	return 0;
}

int CMD_laserAon(int argc, char **argv){

	enableLaserA();
	UARTprintf("\n>");

	return 0;
}

int CMD_laserAoff(int argc, char **argv){

	disableLaserA();
	UARTprintf("\n>");

	return 0;
}

int CMD_laserBon(int argc, char **argv){

	enableLaserB();
	UARTprintf("\n>");

	return 0;
}

int CMD_laserBoff(int argc, char **argv){

	disableLaserB();
	UARTprintf("\n>");

	return 0;
}

int CMD_shutdown(int argc, char **argv){

	disableLaserA();
	disableLaserB();
	UARTprintf("\n>");

	return 0;
}
