#include <stdio.h>

#define M_PI 3.14159265358979323846

void sine_table();
float iter_table(int quadrant);

int main(int argc, char *argv[]) {
	double ar[256];
	double half_PI = (M_PI/2);	// 1.57079632679
	int count = 0;
	int quadrant = 1;			// placeholder for global var
	int * p = ar[0];			// pointer to sine table

	return 0;
}	
void sine_table() {
	for(int i=0;i<=256;i++) {
		ar[i] = (half_PI*i/256);
//		printf("%f = %.2f\n", ar[i], (ar[i]/half_PI)*100);
}

float iter_table(int quadrant) {
	switch(quadrant) {
		case 1:
			if (p <= 256) 
				p++;
			percent = (((*p)/half_PI)*100);	
			signal_pwm(percent);	
			break;
		case 2:
			if (p >= 0)
				p--;
			percent = (((*p)/half_PI)*100);	
			signal_pwm(percent);	
			break;
		case 3:
			*p = ar[0];
			for(int a = 1; a <= 256; a++) {
				ar[a] = -(ar[a]);
				p++;
			}
			percent = (((*p)/half_PI)*100);
			signal_pwm(percent);	
			break;
		case 4:
			if (p >= 0)
				p--;	
			percent = (((*p)/half_PI*100);
			signal_pwm(percent);	
			break;
	}
}

//	for(int j=0;j<=256;j++) {
//		printf("%20.18lf\n", ar[j]);
//	}

/*	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			if(count > 257)
				break;	
			table[i][j] = ar[count];  
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
