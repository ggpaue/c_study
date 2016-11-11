#include <stdio.h>

int main() {
	/*
	for(int j = 0; j <= 8; j++) {
		if(j == 4) {
			continue;
		}
		printf("%d\n", j);
	}
	*/

	/*
	int counter = 10;
	while(counter >= 0) {
		if(counter == 7) {
			counter--;
			continue;
		}
		printf("%d\n", counter);
		counter--;
	}
	*/
	
	int j = 0; 
	do {
		if(j == 7) {
			j++;
			continue;
		}
		printf("\nvalue of j: %d", j);
		j++;
	} while(j < 10);


	return 0;
}