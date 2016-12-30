int sock_control;

int read_reply() {
	int retcode = 0;
	if(recv(sock_control, &retcode, sizeof(retcode), 0) < 0) {
		perror("client: error reading message from server \n");
		return -1;
	}
	return ntohl(retcode);
}

void print_reply(int rc) {
	switch(rc)
	{
		case 220:
			printf("220 Welcome, server ready. \n");
			break;
		case 221:
			printf("221 Goodbye! \n");
			break;
		case 226:
			printf("226 Closing data connection. Requested file action successful. \n");
			break;
		case 550:
			printf("550 Requested action not taken. File unavailable. \n");
			break;
	}
}

int ftclient_read_command(char *buf, int size, struct command *cstruct) {
	memset(cstruct -> code, 0, sizeof(cstruct -> code));
	memset(cstruct -> arg, 0, sizeof(cstruct -> arg));

	printf("ftclient> ");
	fflush(stdout);
	read_input(buf, size);
	char *arg = NULL;
	arg = strtok(buf, " ");
	arg = strtok(NULL, " ");

	if(arg != NULL) {
		strncpy(cstruct -> arg, arg, strlen(arg));
	}

	if(strcmp(buf, "list") == 0) {
		strcpy(cstruct -> code, "LIST");
	} else if(strcmp(buf, "get") == 0) {
		strcpy(cstruct -> code, "RETR");
	} else if(strcmp(buf, "quit") == 0) {
		strcpy(cstruct -> code, "QUIT");
	} else {
		return -1;
	}

	memset(buf, 0, 400);
	strcpy(buf, cstruct -> code);

	if(arg != NULL) {
		strcat(buf, " ");
		strncat(buf, cstruct -> arg, strlen(cstruct -> arg));
	}
	return 0;
}

int ftclient_get(int data_sock, int sock_control, char *arg) {
	char data[MAXSIZE];
	int size;
	FILE *fd = fopen(arg, "w");

	while((size = recv(data_sock, data, MAXSIZE, 0)) > 0) {
		fwrite(data, 1, size, fd);
	}

	if(size < 0) {
		perror("error \n");
	}
	fclose(fd);
	return 0;
}

int ftclient_open_conn(int sock_con) {
	int sock_listen = socket_create(CLIENT_PORT_ID);

	int ack = 1;
	if((send(sock_con, (char *)&ack, sizeof(ack), 0)) < 0) {
		printf("client: ack write error: %d\n", errno);
		exit(1);
	}

	int sock_conn = socket_accept(sock_listen);
	close(sock_listen);
	return sock_conn;
}

int ftclient_list(int sock_data, int sock_con) {
	size_t num_recvd;
	char buf[MAXSIZE];
	int tmp = 0;

	if(recv(sock_con, &tmp, sizeof(tmp), 0) < 0) {
		perror("client: error reading message from server \n");
		return -1;
	}

	memset(buf, 0, sizeof(buf));

	while((num_recvd = recv(sock_data, buf, MAXSIZE, 0)) > 0) {
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}

	if(num_recvd < 0) {
		perror("error");
	}

	if(recv(sock_con, &tmp, sizeof(tmp), 0) < 0) {
		perror("client: error reading message from server \n");
		return -1;
	}
	return 0;
}