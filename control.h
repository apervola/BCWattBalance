/*
 * control.h
 * All control function prototypes
 *
 */

#ifndef CONTROL_H_
#define CONTROL_H_

/*
 * Declare Board Initialization Functoin
 */

extern void board_INIT();

/*
 * Declare Laser Control Functions
 */

extern void disableLaserA();
extern void disableLaserB();
extern void enableLaserA();
extern void enableLaserB();

/*
 * Declare UART Initialization Function
 */

extern void ConfigureUART(void);

#endif /* CONTROL_H_ */
