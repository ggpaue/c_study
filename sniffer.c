#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>    


#include "sniffer.h"

int exec_cmd(char *buffer, int len) {
	if(strncmp(buffer, "quit", 4) == 0) {
		return 1;
	}
	return 0;
}

int command_interpreter(int sd) {
	int len;
	char buf[512];

	len = read(0, buf, 512);
	if(len > 0) {
		if(exec_cmd(buf, len) == 1) {
			return 1;
		}
	}
	return 0;
}

void display_time_and_date() {
	INITCOLOR(RED_COLOR);
	printf("[%s]", __DATE__);
	INITCOLOR(GREEN_COLOR);
	printf("[%s] ", __TIME__);
	INITCOLOR(ZERO_COLOR);    
}

void getting_started() {
	CLEARSCREEN();
	display_time_and_date();
	printf("Getting started of Network sniffer \n\n");
}

void signal_white_now(int signum) {
	printf("Bye Bye! \n");
}

void ProcessPacket(unsigned char *buffer, int size, t_sniffer *sniffer) {
	buffer = buffer + 6 + 6 + 2;
	struct iphdr *iph = (struct iphdr *)buffer;
	++sniffer -> prot -> total;

	switch(iph -> protocol) {
		// icmp protocol
		case 1:
			++sniffer -> prot -> icmp;
			print_icmp_packet(buffer, size, sniffer);
			break;

		// igmp protocol
		case 2:
			++sniffer -> prot -> igmp;
			break;

		// tcp protocol
		case 6:
			++sniffer -> prot -> tcp;
			print_tcp_pakcet(buffer, size, sniffer);
			break;

		// UDP protocol
		case 17:
			++sniffer -> prot -> udp;
			print_udp_packet(buffer, size, sniffer);
			break;

		default:
			++sniffer -> prot -> others;
			break;
	}

	display_time_and_date();

	printf("TCP : %d,   UDP : %d   ICMP : %d  IGMP : %d   Others : %d  Total: %d\n", 
		sniffer -> prot -> tcp, sniffer -> prot -> udp, sniffer -> prot -> icmp, sniffer -> prot -> igmp,
		sniffer -> prot -> others, sniffer -> prot -> total);
}

void print_ip_header(unsigned char *buf, int size, t_sniffer *sniffer) {
	unsigned short iphdrlen;
	struct iphdr *iph;
	struct sockaddr_in source;
	struct sockaddr_in dest;

	iph = (struct iphdr *)buf;
	iphdrlen = iph -> ihl * 4;
	(void)iphdrlen;
	(void)size;
	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph -> saddr;

	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = iph -> daddr;

	fprintf(sniffer -> logfile, "\n");
	fprintf(sniffer -> logfile, "IP Header \n");
	fprintf(sniffer -> logfile, "IP Version: %d\n", (unsigned int)iph -> version);
	fprintf(sniffer -> logfile, "IP Header Length: %d DWORDS or %d Bytes \n", (unsigned int)iph -> ihl, ((unsigned int)(iph -> ihl)) * 4);
	fprintf(sniffer -> logfile, "Type Of Service: %d\n", (unsigned int)iph -> tos);
	fprintf(sniffer -> logfile, "IP Total Length: %d Bytes(size of Packet\n", ntohs(iph -> tot_len));
	fprintf(sniffer -> logfile, "Identification: %d\n", ntohs(iph -> id));
	fprintf(sniffer -> logfile, "TTL: %d\n", (unsigned int) iph -> ttl);
	fprintf(sniffer -> logfile, "Protocol: %d\n", (unsigned int)iph -> protocol);
	fprintf(sniffer -> logfile, "Checksum: %d\n", ntohs(iph -> check));
	fprintf(sniffer -> logfile, "Source IP: %s\n", inet_ntoa(source.sin_addr));
	fprintf(sniffer -> logfile, "Destination IP: %s\n", inet_ntoa(dest.sin_addr));
}

void print_tcp_header(unsigned char *buf, int size, t_sniffer *sniffer) {
	unsigned short iphdrlen;
	struct iphdr *iph;
	struct tcphdr *tcph;

	iph = (struct iphdr *)buf;
	iphdrlen = iph -> ihl * 4;
	tcph = (struct tcphdr *)(buf + iphdrlen);
	print_ip_header(buf, size, sniffer);

	fprintf(sniffer -> logfile, "\n");
	fprintf(sniffer -> logfile, "TCP Header\n");
	fprintf(sniffer -> logfile, "Source Port: %u\n", ntohs(tcph -> source));      
}

void printData(unsigned char *buf, int size, t_sniffer *sniffer) {
	int i;

	for(i = 0; i < size; i++) {
		if(i % 16 == 0) {
			fprintf(sniffer -> logfile, "\n");
			fprintf(sniffer -> logfile, "%02X", (unsigned int)buf[i]);
		}

		if(i == size - 1) {
			fprintf(sniffer -> logfile, "\n");
		}
	}
}

int main() {
	int sd;
	int res;
	int saddr_size;
	int data_size;
	struct sockaddr saddr;
	unsigned char *buffer;
	t_sniffer sniffer;
	fd_set fd_read;

	buffer = malloc(sizeof(unsigned char *) * 65536);

	sniffer.logfile = fopen("log.txt", "w");
	fprintf(sniffer.logfile, "***LOGFILE(%s - %s)***\n", __DATE__, __TIME__);
	if(sniffer.logfile == NULL) {
		perror("fopen(): ");
		return (EXIT_FAILURE);
	}

	sniffer.prot = malloc(sizeof(t_protocol *));

	sd = socket(PF_PACKET, SOCK_RAM, htons(ETH_P_TP));
	if(sd < 0) {
		perror("socket(): ");
		return (EXIT_FAILURE);
	}

	getting_started();
	signal(SIGINT, &signal_white_now);
	signal(SIGQUIT, &signal_white_now);

	while(1) {
		FD_ZERO(&fd_read);
		FD_SET(0, &fd_read);
		FD_SET(sd, &fd_read);

		res = select(sd + 1, &fd_read, NULL, NULL, NULL);
		if(res < 0) {
			close(sd);
			if(errno != EINTR) {
				perror("select() ");
				return (EXIT_FAILURE);
			}
		} else {
			if(FD_ISSET(0, &fd_read)) {
				if(command_interpreter(sd) == 1) {
					break;
				}
			} else if(FD_ISSET(sd, &fd_read)) {
				saddr_size = sizeof(saddr);
				data_size = recvfrom(sd, buffer, 65536, 0, &saddr, (socklen_t*)&saddr_size);
				if(data_size <= 0) {
					close(sd);
					perror("recvfrom(): ");
					return (EXIT_FAILURE);
				}

				ProcessPacket(buffer, data_size, &sniffer);
			}
		}
	}
	close(sd);
	return (EXIT_FAILURE);
}