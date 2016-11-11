#include <stdio.h>

int main() {
	/*
	int disp[3][5];

	int i, j;

	for(i = 0; i <= 2; i++) {
		for(j = 0; j <= 4; j++) {
			printf("Enter value for disp[%d][%d]: ", i ,j);
			scanf("%d", &disp[i][j]);
		}
	}
	*/

	//int abc[][2] = {1,2,3,4};
	
	/*
	int abc[5][4] = {
		{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11},
		{12,13,14,15},
		{16,17,18,19}
	};

	for(int i = 0; i <= 4; i++) {
		//for(int j = 0; j <= 3; j++) {
			printf("%u\n", abc[i]);

		//}
	}
	*/

	int avg = 0;
	int sum = 0; 
	int x = 0;

	int num[20];

	for(x = 0; x <= 19; x++) {
		printf("enter the integer number %d\n", x);
		scanf("%d", &num[x]);
	}

	for(x = 0; x <= 19; x++) {
		sum = sum + num[x];
	}

	avg = sum/20;
	printf("%d\n", avg);

	return 0;
}