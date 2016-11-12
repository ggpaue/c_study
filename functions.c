#include <stdio.h>

int max(int x, int y) {
	int z;
	z = x > y ? x : y;
	return z;
}


int max2(int a, int b) {
	if(a >= b) 
		return a;
	else
		return b;
}

int max4(int a, int b, int c, int d) {
	int max2(int a, int b);
	int m;
	m = max2(a, b);
	m = max2(m, c);
	m = max2(m, d);
	return m;
}

int fac(int n) {
	int f;
	if(n == 0 || n == 1)
		f = 1;
	else
		f = fac(n - 1) * n;
	return f;
}


float average(float array[10]) {
	int i;
	float aver, sum = 0;
	for(int i = 0; i < 10; i++) {
		sum = sum + array[i];
	}
	aver = sum / 10;
	return aver;
}



int fun1(int m) {
	int n = 0;

	for(int i = 1; i <= m; i++) {
		int result = i % 7;
		if(result == 0) {
			printf("%d, ", i);
			n++;
		}
	}
	printf("\n");
	return n;
}



int fun2(int a, int b) {
	int c = 0;
	
	int a10 = a / 10;
	c += a10 * 10;
	
	int a1 = a % 10;
	c += a1 * 1000;

	int b10 = b / 10;
	c += b10 * 100;

	int b1 = b % 10;
	c += b1;

	return c;
}

int main() {
	//int max(int x, int y);
	/*
	int a = 10, b = 20;
	int c;
	c = max(a, b);
	printf("%d\n", c);
	*/

	/*
	int max4(int a, int b, int c, int d);
	int a, b, c, d, max;
	printf("please enter 4 integer number:");
	scanf("%d%d%d%d", &a, &b, &c, &d);
	max = max4(a, b, c, d);
	printf("max = %d\n", max);
	*/

	/*
	int fac(int n);
	int n, y;
	printf("please input an integer number: ");
	scanf("%d", &n);
	if(n < 0) {
		printf("data error\n");
	} else {
		y = fac(n);
		printf("%d!=%d\n", n, y);
	}
	*/

	/*
	int max(int x, int y);
	int a[10], m, n, i;
	printf("please enter 10 integer number:");
	for(i = 0; i < 10; i++) {
		scanf("%d", &a[i]);
	}
	printf("\n");

	for(i = 1, m = a[0], n = 0; i < 10; i++) {
		if(max(m, a[i]) > m) {
			m = max(m, a[i]);
			n = i;
		}
	}

	printf("the largest number is %d\n it is the %dth number \n", m, n + 1);
	*/

	/*
	float average(float array[10]);
	float score[10], aver;
	int i;
	printf("please enter 10 scores: ");
	for(int i = 0; i < 10; i++) {
		scanf("%f", &score[i]);
	}
	printf("\n");

	aver = average(score);
	printf("average score is %5.2f\n", aver);
	*/

	int m = 50;
	int n = fun1(m);
	printf("%d\n", n);

	int a = 45, b = 12;
	int c = fun2(a, b);
	printf("%d\n", c);


	return 0;
}