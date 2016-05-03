#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define HALF_PI (M_PI/2)

void generateSineTable();
float increment();

static double sineTable[256];
static int quadrant = 1;
static double *p = sineTable;			// pointer to sine table

void generateSineTable() {
	int i;
	for(i=0; i <= 256; i++) {
		sineTable[i] = sin(i * HALF_PI / 256);

	}
//		printf("%f = %.2f\n", sineTable[i], (sineTable[i]/HALF_PI)*100);
}

float increment() {
	switch(quadrant) {
		case 1:
			if (p <= 256) 
				p++;
			percent = (((*p)/HALF_PI)*100);
			signal_pwm(percent);
			break;
		case 2:
			if (p >= 0)
				p--;
			percent = (((*p)/HALF_PI)*100);
			signal_pwm(percent);	
			break;
		case 3:
			*p = sineTable[0];
			int a;
			for(a = 1; a <= 256; a++) {
				sineTable[a] = -(sineTable[a]);
				p++;
			}
			percent = (((*p)/HALF_PI)*100);
			signal_pwm(percent);	
			break;
		case 4:
			if (p >= 0)
				p--;	
			percent = (*p)/HALF_PI*100;
			signal_pwm(percent);	
			break;
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
