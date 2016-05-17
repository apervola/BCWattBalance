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
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"

/******************************************************************************

						Board Intialization Routine

		   TODO: Add intialization functions as development continues

 *******************************************************************************/

void systemInit(){

	/*
	 * CPU clock speed initialization
	 */
	// Setup the system clock to run at 80 Mhz from PLL with crystal reference
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*
	 * UART initialization
	 */
	// Enable and configure the GPIO port A for laser control and UART
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	// Configure pins 0 and 1
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// Use the system clock for the UART clock speed
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);

	// Enable terminal I/O
	UARTStdioConfig(0, 115200, SysCtlClockGet());

	// Test the setup
	UARTprintf("UART initialized.\n");

	/*
	 * Enable all interrupts
	 */
	IntMasterEnable();
}

void board_INIT(){


	/*
	 * Setup PWM Clock to run at 625KHZ by dividing the system clock (80 mhz) by 32
	 */

	SysCtlPWMClockSet(SYSCTL_PWMDIV_32);

	/*
	 * Enable and configure GPIO port E for coil driver control
	 * Enable and configure GPIO port D for PWM output
	 */

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

	/*
	 * Configure Laser Controls Pins
	 */

	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6);

	/*
	 * Assure initial laser state is OFF
	 *
	 */

	disableLaserA();
	disableLaserB();

	/*
	 * Configure coil drivers
	 */


	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2);

	/*
	 * Assure initial coil state is OFF
	 *
	 */

	disableCoilA();
	disableCoilB();

	/*
	 * Configure relay drivers
	 */


	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);


	UARTprintf("\n>");

	/*
	 * Configure PWM Pins for Coil Output
	 */

	GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
	GPIOPinConfigure(GPIO_PD0_M1PWM0);

	/*
	 * Configure PWM Output Configuration
	 */

	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, PWM_FREQUENCY);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 0);
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, false);
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);

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
	UARTprintf("\n");


}

