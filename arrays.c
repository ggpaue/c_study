#include <stdio.h>
#include <string.h>
//#include <bsd/string.h>


size_t strlcpy(dst, src, siz)
	char *dst;
	const char *src;
	size_t siz;
{
	int ret;

	if (src == NULL)
		return 0;
	if (dst == NULL || siz == 0)
		return strlen(src);

	ret = strlen(src);
	if (ret >= siz)
	{
		memcpy(dst, src, siz - 1);
		dst[siz-1] = '\0';
	}
	else
	{
		memcpy(dst, src, ret+1);
	}
	return ret;
}

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
	/*
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
	*/

	/*
	int i, a[10];
	for(i = 0; i < 10; i++) {
		a[i] = i + 1;
	}
	for(i = 9; i >= 0; i--) {
		printf("%d\n", a[i]);
	}
	*/

	/*
	int i, j, t, LearnTime[10];
	printf("please enter 10 number: \n");
	
	for(i = 0; i < 10; i++) {
		scanf("%d", &LearnTime[i]);
	}

	for(j = 0; j < 9; j++) {
		for(i = 0; i < 9 - j; i++) {
			if(LearnTime[i] > LearnTime[i + 1]) {
				t = LearnTime[i];
				LearnTime[i] = LearnTime[i + 1];
				LearnTime[i + 1] = t;
			}
		}
	}

	printf("the sorted number: \n");
	for(i = 0; i < 10; i++) {
		printf("%d\t", LearnTime[i]);
	}
	*/

	/*
	int i, j, row = 0, colum = 0, max;
	int a[3][4] = {{3,4,16,2}, {7,5,1,9}, {11,23,3,8}};
	max = a[0][0];
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 4; j++) {
			if(a[i][j] > max) {
				max = a[i][j];
				row = i;
				colum = j;
			}
		}
	}
	printf("max = %d\nrow=%d\ncolum=%d\n", max, row, colum);
	*/

	/*
	char c[][5] = {{'*', '*', '*', '*', '*'}, {'*', ' ', ' ', ' ', '*'}, {'*', ' ', ' ', ' ', '*'}, {'*', ' ', ' ', ' ', '*'}, {'*', '*', '*', '*', '*'}};
	int i, j;
	for(i = 0; i < 5; i++) {
		for(j = 0; j < 5; j++) {
			printf("%c", c[i][j]);
		}
		printf("\n");
	}
	*/
	/*
	char c[] = "Shiyanlou";
	printf("%s\n", c);
	printf("%c\n", c[0]);
	*/

	/*
	char str[] = "China\nChengdu";
	puts(str);
	*/
	/*
	char str[100];
	gets(str);
	printf("%s\n", str);
	*/

	/*
	char str1[30] = "People's Republic of ";
	char str2[] = "China";
	printf("%s\n", strcat(str1, str2));
	printf("%d\n", strlen(str2));
	*/
	/*
	char str1[10], str2[] = "China";
	strcpy(str1, str2);
	printf("%s\n", str1);

	strcmp("Chengdu", "Beijing");
	*/
	/*
	char string[30];
	char ch[3][30];
	int i;
	for(i = 0; i < 3; i++) {
		gets(ch[i]);
	}	
	strcpy(string, ch[0]);
	
	for(i = 1; i < 3; i++) {
		if(strcmp(ch[i], string) < 0) {
			strcpy(string, ch[i]);
		}
	}
	printf("the result is: \n%s\n", string);
	*/
	/*
	const char *sn = "Hello";
	char *result = strdup(sn);
	printf("%s\n", result);
	*/

	char *sn = "FTKMOB6B6BBA44E2";

	char buf[16];

	strlcpy(buf, sn, sizeof(buf) + 1);
	printf("%s\n", buf);

	return 0;
}