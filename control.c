/*
 *	control.c
 *	Control function declarations
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

	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
	UARTprintf("Laser A enabled.\n");
}

void enableLaserB(){

	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
	UARTprintf("Laser B disabled.\n");
}

void disableCoilA(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
	UARTprintf("Coil A disabled.\n");
}

void disableCoilB(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
	UARTprintf("Coil B disabled.\n");
}

void enableCoilA(){

	disableCoilB();
	PWMoff();
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);
	UARTprintf("Coil A enabled.\n");
}

void enableCoilB(){

	disableCoilA();
	PWMoff();
	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);
	UARTprintf("Coil B enabled.\n");
}

void signalPWM(int p){

	int percent;

	if(p == 0) percent = 100;
	else if (p == 100) percent = 1;
	else{percent =  100 - p;} //to correct for reverse bias on kicker circuit output

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, percent*113.55); //11355 100% Positive ::113.55 multiplication factor for %
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);
	UARTprintf("PWM On. Duty Cycle: %d.\n", p);
}

void PWMoff(){

	signalPWM(0);
	UARTprintf("PWM off.\n");

}

void coilRelayEnable(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5 );
	UARTprintf("Coil Relay On.\n");

}
void coilRelayDisable(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0 );
	UARTprintf("Coil Relay Off.\n");

}
void senseRelayEnable(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4 );
	UARTprintf("Sense Relay On.\n");
}
void senseRelayDisable(){

	GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0 );
	UARTprintf("Sense Relay Off.\n");
}

