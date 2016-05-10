/*
 * control.h
 * All control function prototypes
 *
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#define PWM_FREQUENCY 55

/*
 * Declare Board Initialization Functoin
 */

extern void board_INIT();
extern void systemInit();

/*
 * Declare Laser Control Functions
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
extern void coilRelayEnable();
extern void coilRelayDisable();
extern void senseRelayEnable();
extern void senseRelayDisable();

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
