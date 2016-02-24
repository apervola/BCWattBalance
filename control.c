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

void disableLaserA(){

	//Enable pin, current to the transistor collector turns laser OFF
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);

}

void disableLaserB(){

	//Enable pin, current to the transistor collector turns laser OFF
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);

}

void enableLaserA(){

	//Disable pin, no current to transistor collector turns laser ON
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
}

void enableLaserB(){
	//Disable pin, no current to transistor collector turns laser ON
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
}


