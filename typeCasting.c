#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

int factorial(unsigned int i) {
	if(i <= 1) {
		return 1;
	}
	return i * factorial(i - 1);
}

int fibonacci(int i) {
	if(i == 0){
		return 0;
	}

	if(i == 1) {
		return 1;
	}

	return fibonacci(i - 1) + fibonacci(i - 2);
}

int main() {
	/**
	int sum = 17, count = 5;
	double mean;

	mean = (double)sum / count;
	printf("Value of mean: %f\n", mean);
	**/
	/*
	int i = 17;
	char c = 'c';

	float sum;
	sum = i + c;
	printf("Value of sum: %f\n", sum);
	**/

	/*
	FILE * pf;
	int errnum;
	pf = fopen("unexist.txt", "rb");

	if(pf == NULL) {
		errnum = errno;
		fprintf(stderr, "Value of error: %d\n", errno);

		perror("Error printed by perror");
		fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
	} else {
		fclose(pf);
	}
	*/
	/*
	int dividend = 20;
	int divisor = 0;
	int quotient;

	if(divisor == 0) {
		fprintf(stderr, "Division by zero! Exiting...\n");
		 exit(EXIT_FAILURE);
	}

	quotient = dividend / divisor;
	fprintf(stderr, "Value of quotient: %d\n", quotient);
	exit(EXIT_SUCCESS);
	*/
	/*
	int i = 15;
	printf("Factorial of %d is %d\n", i, factorial(i));
	*/
	/*
	int i;
	for(int i = 0; i < 10; i++) {
		printf("%d\t\n", fibonacci(i));
	}
	*/

	/*
	printf("Size of char: %d\n", sizeof(char));
	printf("Size of unsigned char: %d\n", sizeof(unsigned char));
	printf("Size of signed char: %d\n", sizeof(signed char));
	printf("Size of int: %d\n", sizeof(int));
	printf("Size of unsigned int: %d\n", sizeof(unsigned int));
	printf("Size of short: %d\n", sizeof(short));
	printf("Size of unsigned short: %d\n", sizeof(unsigned short));
	printf("Size of long: %d\n", sizeof(long));
	printf("Size of unsigned long: %d\n", sizeof(unsigned long));
	*/
	/*
	printf("The size of the smallest positive non-zero value of type float is %.3e\n", FLT_MIN);
	printf("The size of the largest value of type float is %.3e\n", FLT_MAX);
	*/
	/*
	double a, b;
	a = 123456.789e5;
	b = a + 20;
	printf("%f\n", a);
	printf("%f\n", b);
	*/
	/*
	char a, b;
	a = 'c';
	b = 121;
	printf("%c, %c\n", a, b);
	printf("%d, %d\n", a, b);
	*/
	/*
	char a, x;
	int b;
	a = 'c';
	b = 1;
	x = a + b;
	printf("%c\n", x);
	printf("%d\n", x);
	*/
	/*
	float a = 22.5;
	int b = 3;
	printf("%d\n", a%b);
	*/
	/*
	int i = 3;
	float f = 4.3;
	double d = 7.5;
	double sum;
	sum = 10 + 'a' + i*f - d/3;
	*/
	/*
	char c1, c2;
	printf("Please enter a capital letter:");
	scanf("%c", &c1);
	c2 = c1 + 32;
	printf("%c\n", c2);
	*/

	double a, b, c, disc, x1, x2, p, q;
	scanf("%lf%lf%lf", &a, &b, &c);
	disc = b * b - 4 * a *c;
	p = -b / (2.0 * a);
	q = sqrt(disc) / (2.0 * a);
	x1 = p + q, x2 = p - q;
	printf("x1 = %7.2f\nx2 = %7.2f\n", x1, x2);
	return 0;
} 