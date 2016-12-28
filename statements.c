#include <stdio.h>
#include <string.h>

typedef struct test {
	char *sn;
}rsp_data;

int test(rsp_data *rsp) {
	rsp -> sn = "hello";
	return 0;
}

int test2(rsp_data rsp) {
	rsp.sn = "world";
	return 0;
}

int test3(rsp_data *rsp) {
	rsp_data rspCopy;
	rspCopy = *rsp;
	rspCopy.sn = "world";
	*rsp = rspCopy;

	return 0;
}

int result = 0;

void func(int type) {
	//int result = 0;
	switch(type) {
		case 1:
			printf("%d, %d\n", type, result);
			break;
		case 2:
			result = 100;
			printf("%d, %d\n", type, result);
			break;
		default:
			result = -100;
			break;
			
	}
}
int main() {
	int type = 2;
	func(type);
	type = 1;
	func(type);
	/*
	rsp_data rsp;
	//memset(&rsp, 0, sizeof(rsp));
	test(&rsp);

	//char *sn = NULL;
	
	printf("sn = %s\n", rsp.sn);


	test2(rsp);
	printf("sn = %s\n", rsp.sn);

	test3(&rsp);
	printf("sn = %s\n", rsp.sn);
	*/
	//printf("rsp.sn = %s\n", rsp.sn);
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
	
	/*
	int j = 0; 
	do {
		if(j == 7) {
			j++;
			continue;
		}
		printf("\nvalue of j: %d", j);
		j++;
	} while(j < 10);
	*/
	/*
	int number = 0;
	printf("\nPlease enter an integer between 1 and 10:");
	scanf("%d", &number);

	if(number > 5)
		printf("You entered %d which is greater than 5\n", number);

	if(number < 6)
		printf("You entered %d which is less then 6\n", number);
	*/


	/*
	char letter;
	printf("Enter an upper case letter: ");
	scanf("%c", &letter);

	if((letter >= 'A') && (letter < 'Z')) {
		letter += 'a' - 'A';
		printf("You entered an uppercase %c.\n", letter);
	} else {
		printf("You did not enter an uppercase letter.\n");
	}
	*/

	/*
	double unit_price = 3.5;
	double discount1 = 0.05;
	double discount2 = 0.1;
	double discount3 = 0.15;
	double total_price = 0.0;
	int quantity = 0;

	printf("Enter the number that you want to buy: ");
	scanf("%d", &quantity);

	total_price = quantity * unit_price * (1.0 - 
		(quantity > 50 ? discount3 : (
			quantity > 20 ? discount2 : (
			quantity > 10 ? discount1 : 0.0))));
	printf("The price for %d is %7.2f\n", quantity, total_price);
	*/
	/*
	char grade;
	scanf("%c", &grade);
	printf("you score: ");
	switch(grade) {
		case 'a': printf("85~100\n"); break;
		case 'b': printf("70~84\n"); break;
		case 'c': printf("60~69\n"); break;
		case 'd': printf("<60\n"); break;
		default: printf("error!\n");
	}
	*/
	/*
	int i = 1, sum = 0;
	while( i <= 100) {
		sum = sum + i;
		i++;
	}
	printf("sum = %d\n", sum);
	*/

	/*
	int i = 1, sum = 0;
	do {
		sum = sum + i;
		i++;
	}while(i <= 100);
	printf("sum = %d\n", sum);
	*/

	/*
	int i, j, n = 0;
	for(i = 1; i <= 4; i++) {
		for(j = 1; j <= 5; j++, n++) {
			if(n % 5 == 0) printf("\n");
			printf("%d\t", i * j);
		}
		printf("\n");
	}*/
	/*
	int i, j , n = 0;
	for(i = 1; i <= 7; i++) {
		for(j = 1; j <= 7; j++, n++) {
			if(n % 7 == 0) printf("\n");
			printf("*");
		}
	}
	*/


	return 0;
}