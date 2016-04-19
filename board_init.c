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

/******************************************************************************

						Board Intialization Routine

		   TODO: Add intialization functions as development continues

 *******************************************************************************/

void board_INIT(){

	volatile uint32_t ui32Period;
	volatile uint32_t ui32PWMClock;

	/*
	 * Setup the system clock to run at 40 Mhz from PLL with crystal reference
	 * Setup PWM Clock to run at 625KHZ
	 */

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

	/*
	 * Enable and configure the GPIO port A for laser control and UART
	 * Enable and configure GPIO port E for coil driver control
	 * Enable and configure GPIO port D for PWM output
	 */

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	ConfigureUART(); //Port A must be enabled first !

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

	/*
	 * Assure initial relay state is normal
	 *
	 */

	coilRelayDisable();
	senseRelayDisable();

	UARTprintf("\n>");

	/*
	 * Configure PWM Pins
	 */

	GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
	GPIOPinConfigure(GPIO_PD0_M1PWM0);

	/*
	 * Configure PWM Output Configuration
	 */

	ui32PWMClock = SysCtlClockGet() / 64; //625khz
	ui32Period = (ui32PWMClock / PWM_FREQUENCY) - 1;
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Period);
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



