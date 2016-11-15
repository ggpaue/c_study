#include <stdio.h>
#include <string.h>
int var = 1;

void swap(int *point_1, int *point_2) {
	int temp;
	temp = *point_1;
	*point_1 = *point_2;
	*point_2 = temp;
}

void swap2(int p, int q) {
	int temp;
	temp = p;
	p = q;
	q = temp;
}

void exchange(int *q1, int *q2, int *q3) {
	void swap(int *pt1, int *pt2);
	if(*q1 < *q2) swap(q1, q2);
	if(*q1 < *q3) swap(q1, q3);
	if(*q2 < *q3) swap(q2, q3);
}

void change(int x[], int n) {
	int temp, i, j, m = (n-1)/2;
	for(i = 0; i <= m; i++) {
		j = n - 1 -i;
		temp = x[i];
		x[i]  = x[j];
		x[j] = temp; 
	}
}

void change2(int *x, int n) {
	int *p, temp, *i, *j, m = (n-1)/2;
	i = x;
	j = x + n - 1;
	p = x + m;
	for(; i <= p; i++, j--) {
		temp = *i;
		*i = *j;
		*j = temp;
	}
}

void copy_string(char from[], char to[]) {
	int i = 0;
	while(from[i] != '\0') {
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
}

void copy_string2(char *from, char *to) {
	
	for(; *from != '\0'; from++, to++) {
		*to = *from;
	}
	//to[i] = '\0';
}

int main() {
	/*
	int num = 10;
	printf("Values of var is: %d\n", num);
	printf("Address of value is: %p\n", &num);
	*/
	/*
	int *p;
	int var = 10;

	p = &var;
	*/

	//printf("Value of var is: %d\n", var);
	//printf("Address of var is: %p\n", p);
	/*
	printf("Address of var is: %p\n", &var);
	printf("Address of var is: %p\n", p);

	printf("Address of pointer p is: %p\n", &p);


	printf("Value of pointer p is: %p\n", p);

	printf("Value of var is: %d\n", var);
	printf("Value of var is: %d\n", *p);
	printf("Value of var is: %d\n", *(&var));
	*/
	/*
	char ch = 'a';
	char *pr;
	pr = &ch;

	*pr = 'b';
	printf("Value of ch: %c\n", ch);
	printf("Value of ch: %c\n", *pr);
	*/

	/*
	int a = 100, b = 10;
	int *pointer_1, *pointer_2;
	pointer_1 = &a;
	pointer_2 = &b;
	printf("a = %d, b = %d\n", a, b);
	printf("%ld, %ld\n", pointer_1, pointer_2);
	printf("*pointer1=%d, *pointer_2=%d\n", *pointer_1, *pointer_2);
	*/
	/*
	int *p1, *p2, *p, a, b;
	printf("please enter two integer number: ");
	scanf("%d,%d", &a, &b);
	//printf("a=%d,b=%d\n", a, b);

	p1 = &a;
	p2 = &b;

	swap2(a, b);
	printf("a=%d,b=%d\n", a, b);

	if(a < b) {
		//p = p1;
		//p1 = p2;
		//p2 = p;
		swap(p1, p2);
	}

	printf("a=%d,b=%d\n", a, b);
	printf("max=%d,min=%d\n", *p1, *p2);
	*/

	/*
	int a,b,c,*p1,*p2,*p3;
	printf("please enter 3 integer number:");
	scanf("%d%d%d", &a, &b, &c);
	p1=&a;
	p2=&b;
	p3=&c;
	exchange(p1,p2,p3);
	printf("the order is: %d,%d,%d\n", a, b, c);
	*/

	/*
	int a[10];
	int *p, i;
	printf("please enter 3 integer numbers: ");
	for(i = 0; i < 3; i++) {
		//scanf("%d", &a[i]);
		scanf("%d", a + i);
	}

	for(i = 0; i < 3; i++) {
		printf("%d\t", a[i]);
	}
	printf("\n");
	for(i = 0; i < 3; i++) {
		printf("%d\t", *(a + i));
	}
	printf("\n");
	for(p = a; p < (a + 3); p++) {
		printf("%d\t", *p);
	}
	printf("\n");

	//for(p = a; a < (p + 10); a++) {
	//	printf("%d", *a);
	//}
	*/
	/*
	int *p, i, a[10];
	p = a;
	printf("please enter 3 integer number: ");
	for(i = 0; i < 3; i++) {
		scanf("%d", p++);
	}

	p = a;
	for(i = 0; i < 3; i++, p++) {
		printf("%d ", *p);
	}
	printf("\n");
	*/
	/*
	int i, a[10] = {3,7,9,11,0,6,7,5,4,2};
	printf("the original array: \n");
	for(i = 0; i < 10; i++) {
		printf("%d\t", a[i]);
	}
	printf("\n");

	change2(a, 10);
	printf("the array has been inverted: \n");
	for(i = 0; i < 10; i++) {
		printf("%d\t", a[i]);
	}
	printf("\n");
	*/

	/*
	//char string[] = "I love Shiyanlou!";
	char *string = "I love Shiyanlou!";
	printf("%s\n", string);
	printf("%c\n", string[9]);
	printf("%d\n", strlen(string));
	*/
	/*
	char a[] = "I am a programmer", b[20];
	int i;
	for(i = 0; *(a + i) != '\0'; i++) {
		*(b + i) = *(a + i);
	}
	*(b + i) = '\0';
	printf("string a is: %s\n", a);
	
	printf("string b is: ");
	for(i = 0; b[i] != '\0'; i++) {
		printf("%c", b[i]);
	}
	printf("\n");
	*/
	/*
	char a[] = "I am a programmer", b[20], *p1, *p2;
	p1=a, p2=b;
	for(; *p1 != '\0'; p1++, p2++) {
		*p2 = *p1;
	}
	*p2 = '\0';
	printf("string a is: %s\n", a);
	printf("string b is: %s\n", b);
	*/
	/*
	char a[] = "I am a teacher";
	char b[] = "You are a programmer";
	printf("string a = %s\nstring b = %s\n", a, b);
	printf("copy string a to string b: \n");
	copy_string(a, b);
	printf("\nstring a = %s\nstring b = %s\n", a ,b);
	*/
	/*
	char a[] = "I am a teacher";
	char b[] = "You are a programmer";
	char *from = a, *to = b;
	printf("string a = %s\nstring b = %s\n", a, b);
	printf("copy string a to string b: \n");
	copy_string(from, to);
	printf("\nstring a = %s\nstring b = %s\n", a ,b);
	*/

	char *a = "I am a teacher";
	char b[] = "You are a programmer";
	char *p = b;
	printf("string a = %s\nstring b = %s\n", a, b);
	printf("copy string a to string b: \n");

	copy_string2(a, p);
	printf("\nstring a = %s\nstring b = %s\n", a ,b);
	
	return 0;
}