/*
 * console.h
 * Console fuction prototypes
 *
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#define CONSOLE_BUF_SIZE      128

int CMD_help(int argc, char **argv);
int CMD_laserAon(int argc, char **argv);
int CMD_laserAoff(int argc, char **argv);
int CMD_laserBon(int argc, char **argv);
int CMD_laserBoff(int argc, char **argv);
int CMD_shutdown(int argc, char **argv);

#endif /* CONSOLE_H_ */
