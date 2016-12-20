#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <sys/time.h>
#include <time.h>

/*
float timediff(struct timeval *begin, struct timeval *end) {
	int n;

	n = (end -> tv_sec - begin->tv_sec) * 1000000 
		+ (end -> tv_usec - begin -> tv_usec);

	return (float)(n / 1000);
}

int main(void) {
	struct timeval begin, end;
	gettimeofday(&begin, 0);

	printf("sleep for 1 sec...");
	sleep(1);

	gettimeofday(&end, 0);

	printf("running time: %fms\n", timediff(&begin, &end));

	return 0;
}
*/  

void test(char *stamp) {
	printf("%s\n", stamp);
}

int main() {
	time_t rawtime = time(NULL);
	//struct tm *timeinfo;
	
	
	//timeinfo = localtime(&rawtime);
	/*
	char timestamp[32];
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&rawtime));
	printf("Current local time and date: %s\n", timestamp);
	for(int i = 0; i < 32; i++) {
		printf("%c\n", timestamp[i]);
	}
	*/
	char timestamp[32];
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&rawtime));
	printf("%d\n", sizeof(timestamp));
	test(timestamp);
	printf("Current local time and date: %s\n", timestamp);

	return 0;
}