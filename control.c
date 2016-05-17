/*
 *	control.c
 *	Control function declarations
 *
 *BOARD PIN DESIGNATION
 *
 *PORT	PIN(s)	-	Descriptioin
 *
 *PORT A 0,1	-	UART/Serial TXRX
 *PORT A 5,6	-	Laser Control Signals
 *PORT D 0		- 	PWM1 Output
 *PORT E 1,2	- 	Coil Drivers InA/InB
 *PORT E 4,5	- 	Relay Drivers
 *
 *PWM1 Base		-	Coil Output
 *PWM1 Gen		- 	Coil Output
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "control.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "util/cmdline.h"
#include "util/uartstdio.h"
#include "driverlib/uart.h"

int PWMfactor = 9.99; //default PWM factor (default PWM frequency is 999) 999/100

void disableLaserA(){

	//Enable pin, current to the transistor base turns laser OFF
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
	UARTprintf("Laser A disabled.\n");
}

void disableLaserB(){

	//Enable pin, current to the transistor base turns laser OFF
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
	UARTprintf("Laser B disabled.\n");
}

void enableLaserA(){

	//Disable pin, no current to the transistor base turns laser ON
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
	UARTprintf("Laser A enabled.\n");
}

void enableLaserB(){

	//Disable pin, no current to the transistor base turns laser ON
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
	UARTprintf("Laser B disabled.\n");
}

void disableCoilA(){

	//disable output A by applying current
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
	//UARTprintf("Coil A disabled.\n");
}

void disableCoilB(){

	//disable output B by applying current
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
	//UARTprintf("Coil B disabled.\n");
}

void enableCoilA(){

	disableCoilB(); //assure coilB turns off
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
	//UARTprintf("Coil A enabled.\n");
}

void enableCoilB(){

	disableCoilA(); //assure coilA turns off
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
	//UARTprintf("Coil B enabled.\n");
}

/*
 * Signals PWM generator to output a signal at the given percentage p
 * Since we are driving the balance over a sine wave we need to alternate
 * the polarity of the PWM output through the different quadrants of the
 * sine wave. That is why we enable either A or B when we are cycling through
 * the percentages, depending on whether the sinve wave is in a positive or
 * negative quadrant.
 *
 * The PWM output has been tested to be stable from 55 - 2500 HZ minimum
 * Higher frequencies may be possible but require testing
 *
 * The perentage requires the negative/positive inverse because the PWM signal
 * is reversed in the electronic circuit. (See kicker circuit schematic)
 *
 */


void signalPWM(int p){

	int percent;

	/*
	 * Quadrants 1 and 2
	 */

	if(p > 0){
		enableCoilA();
		if(p == 0) percent = 100;
		else if (p == 100) percent = 1;
		else{percent =  100 - p;} //to correct for reverse bias on kicker circuit output
	}

	/*
	 * Quadrants 3 and 4
	 */

	if(p < 0){
		enableCoilB();
		if(p == 0) percent = 100;
		else if (p == -100) percent = 1;
		else{percent = 100 + p;} //to correct for reverse bias on kicker circuit output
	}

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, percent * PWMfactor);
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
	//UARTprintf("PWM On. Duty Cycle: %d.\n", p);
}

void PWMoff(){

	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, false);
	UARTprintf("PWM off.\n");

}

/*
 * Set PWM frequency and factor from command line
 */

void PWMfrequency(int f){

	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, f);
	PWMfactor = f/100;

}

/*
 * Sense/Force Relay Signals
 *
 */

void relayEnable(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5 );
	UARTprintf("Relay On.\n");

}
void relayNormal(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0 );
	UARTprintf("Relay Normal.\n");

}


