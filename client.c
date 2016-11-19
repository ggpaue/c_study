#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <arpa/inet.h>

#define PORT 8888
#define SERV "127.0.0.1"
#define BUFF 1024

int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd == -1) {
		printf("Could not create socket\n");
	}
	puts("Socket created");

	struct sockaddr_in skaddr;
	skaddr.sin_family = AF_INET;
	skaddr.sin_port = htons(PORT);
	skaddr.sin_addr.s_addr = inet_addr(SERV);

	if(connect(sockfd, (struct sockaddr *)&skaddr, sizeof(skaddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	char sendbuff[BUFF];
	char recvbuff[BUFF];

	while(fgets(sendbuff, sizeof(sendbuff), stdin) != NULL) {
		
		if(send(sockfd, sendbuff, strlen(sendbuff), 0) < 0) {
			puts("Send falied");
			exit(1);
		}

		if(strcmp(sendbuff, "exit\n") == 0) break;
		
		if(recv(sockfd, recvbuff, sizeof(recvbuff), 0) < 0) {
			puts("recv falied");
			break;
		}
		
		fputs(recvbuff, stdout);

		memset(sendbuff, 0, sizeof(sendbuff));
		memset(recvbuff, 0, sizeof(recvbuff));
	}

	close(sockfd);
	return 0;
}