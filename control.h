/*
 * control.h
 * All control function prototypes
 *
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#define PWM_FREQUENCY 999 //default PWM Frequency

/*
 * Declare Board Initialization Function
 */

extern void board_INIT();
extern void systemInit();

/*
 * Declare Laser Control, PWM Control, and Relay Control Functions
 */

extern void disableLaserA();
extern void disableLaserB();
extern void enableLaserA();
extern void enableLaserB();
extern void disableCoilA();
extern void disableCoilB();
extern void enableCoilA();
extern void enableCoilB();
extern void signalPWM();
extern void PWMoff();
extern void PWMfrequency();
extern void relayEnable();
extern void relayNormal();


/*
 * Declare UART Initialization Function
 */

extern void ConfigureUART();

/*
 * Declare sine table generation and
 * traversing functions
 */

extern void generateSineTable();
extern void increment();

#endif /* CONTROL_H_ */
