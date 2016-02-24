/*
 *	board_init.c
 *	Board Initialization Routine
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "control.h"
#include "util/cmdline.h"
#include "util/uartstdio.h"

/******************************************************************************

						Board Intialization Routine

		   TODO: Add intialization functions as development continues

 *******************************************************************************/

void board_INIT(){

	/*
	 * Setup the system clock to run at 50 Mhz from PLL with crystal reference
	 */

	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*
	 * Enable and configure the GPIO port A for laser control and UART
	 */

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	ConfigureUART();

	/*
	 * Configure Laser Controls Pins
	 */

	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);

	/*
	 * Assure initial laser state is OFF
	 */

	disableLaserA();
	disableLaserB();

}

/*
 * Enable and initialize UART
 */

void ConfigureUART(void){

	/*
	 * Enable UART 0.
	 */

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	/*
	 * Configure Pins
	 */

	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	/*
	 * Use internal oscillator for UART
	 */

	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

	/*
	 * Enable terminal I/O
	 */

	UARTEnable(UART0_BASE);
	UARTStdioConfig(0, 115200, 16000000);

	/*
	 * Print Welcome Message to terminal
	 */

	UARTprintf("Welcome to the BC Watt Balance Controller ! \n");
	UARTprintf("------------------------------------------- \n");
	UARTprintf("Type 'help' for a list of function commands.\n");
	UARTprintf("> ");


}


