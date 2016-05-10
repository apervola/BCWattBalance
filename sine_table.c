#include <stdio.h>
#include <math.h>
#include "control.h"

#define M_PI	3.14159265358979323846
#define HALF_PI	(M_PI/2)

static double sineTable[256];
static int quadrant = 1;
static double *p = sineTable;			// pointer to sine table

/*
 * Populate sineTable with the appropriate values
 */
void generateSineTable(void) {
	int i;
	for(i=0; i < 256; i++) {
		sineTable[i] = sin(i * HALF_PI / 256);

	}
//		printf("%f = %.2f\n", sineTable[i], (sineTable[i]/HALF_PI)*100);
}

void increment(void)
{
	//int percent = ((*p) / HALF_PI) * 100;
	int percent = (*p) * 100;

	switch(quadrant)
	{
		case 1:
		{
			signalPWM(percent);

			p++;

			if(*p == sineTable[255])
			{
				quadrant++;
			}

		} break;
		case 2:
		{
			signalPWM(percent);

			p--;

			if(*p == sineTable[0])
			{
				quadrant++;
			}

		} break;
		case 3:
		{
			signalPWM(-percent);

			p++;

			if(*p == sineTable[255])
			{
				quadrant++;
			}

		} break;
		case 4:
		{
			signalPWM(-percent);

			p--;

			if(*p == sineTable[0])
			{
				quadrant = 1;
			}

		} break;
	}

}

//	for(int j=0;j<=256;j++) {
//		printf("%20.18lf\n", sineTable[j]);
//	}

/*	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			if(count > 257)
				break;	
			table[i][j] = sineTable[count];
			count++;
		}
	}
	
	for(int k = 0; k < x; k++) {
		for(int l = 0; l < y; l++) {
			printf("%f  ", table[k][l]);
		}
		printf("\n");
	}
*/
