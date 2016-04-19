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
		{"coilAon"	,	   CMD_coilAon, 		" : Turn on Coil A"		},
		{"coilBon",	   	   CMD_coilBon, 		" : Turn on Coil B"		},
		{"coilAoff",	   CMD_coilAoff, 		" : Turn off Coil A"	},
		{"coilBoff",	   CMD_coilBoff, 		" : Turn off Coil B"	},
		{"pwmON",          CMD_signalPWM,       " : Activate PWM"		},
		{"pwmOFF",         CMD_PWMoff,      	" : Stop PWM"			},
		{"coilRelayOn",    CMD_coilRelayOn,     " : Coil Relay ON"  	},
		{"coilRelayOff",   CMD_coilRelayOff,    " : Coil Relay OFF"		},
		{"senseRelayOn",   CMD_senseRelayOn,    " : Sense Relay ON"		},
		{"senseRelayOff",  CMD_senseRelayOff,   " : Sense Relay OFF"	},
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

int CMD_coilAon(int argc, char **argv){

	enableCoilA();
	UARTprintf("\n>");

	return 0;
}
int CMD_coilBon(int argc, char **argv){

	enableCoilB();
	UARTprintf("\n>");

	return 0;
}
int CMD_coilAoff(int argc, char **argv){

	disableCoilA();
	UARTprintf("\n>");

	return 0;
}
int CMD_coilBoff(int argc, char **argv){

	disableCoilB();
	UARTprintf("\n>");

	return 0;
}

int CMD_shutdown(int argc, char **argv){

	disableLaserA();
	disableLaserB();
	disableCoilA();
	disableCoilB();
	PWMoff();
	coilRelayDisable();
	senseRelayDisable();
	UARTprintf("All outputs disabled. \n>");

	return 0;
}

int CMD_signalPWM(int argc, char **argv){

	UARTprintf("Argument [1][0] is: %c\n>",argv[1]);
	int percent = atoi(argv[1]);
	UARTprintf("Percent is: %d\n>",percent);
	signalPWM(percent);
	UARTprintf("\n>");

	return 0;
}

int CMD_PWMoff(int argc, char **argv){

	PWMoff();
	UARTprintf("\n>");

	return 0;
}

int CMD_coilRelayOn(int argc, char **argv){

	coilRelayEnable();
	UARTprintf("\n>");

	return 0;
}

int CMD_coilRelayOff(int argc, char **argv){

	coilRelayDisable();
	UARTprintf("\n>");

	return 0;
}

int CMD_senseRelayOn(int argc, char **argv){

	senseRelayEnable();
	UARTprintf("\n>");

	return 0;

}

int CMD_senseRelayOff(int argc, char **argv){

	senseRelayDisable();
	UARTprintf("\n>");

	return 0;
}
