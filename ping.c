#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
/*
struct icmp {
	unsigned char type;
	unsigned char code;

	unsigned short checksum;
	unsigned short id;
	unsigned short sequence;

	struct timeval timestamp;
};

struct ip {
	unsigned char version: 4;
	unsigned char hlen: 4;
	unsigned char tos;
	unsigned short len;
	unsigned short id;
	unsigned short offset;
	unsigned char ttl;
	unsigned char protocol;
	unsigned short checksum;
	struct in_addr ipsrc;
	struct in_addr ipdst;
};
*/
/*
struct hostent {
	char *h_name;
	char **h_aliases;
	char h_addrtype;
	char h_length;
	char **h_addr_list;
};
*/

unsigned short checkSum(unsigned short *addr, int len) {
	unsigned int sum = 0;
	
	while(len > 1) {
		sum += *addr++;
		len -= 2;
	}

	if(len == 1) {
		sum += *(unsigned char *)addr;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);

	return (unsigned short) ~sum;
}

int main(int argc, char *argv[]) {
	/*
	unsigned short hosts = 0x1234;
	unsigned short nets;
	unsigned long hostl = 0x12345678;
	unsigned long netl;

	nets = htons(hosts);
	netl = htonl(hostl);

	printf("Host ordered short: %#x \n", hosts);
	printf("Netwrok ordered short: %#x \n", nets);

	printf("Host ordered long: %#x \n", hostl);
	printf("Netwrok ordered long: %#x \n", netl);
	*/
	/*
	char *addr1 = "1.2.3.4";
	char *addr2 = "192.168.1.1";

	in_addr_t data;

	data = inet_addr(addr1);
	printf("%s -> %#lx \n", addr1, (long)data);

	data = inet_addr(addr2);
	printf("%s -> %#lx \n", addr2, (long)data);
	*/
	/*
	struct in_addr addr1, addr2;
	char *str1, *str2;

	char buf[20];

	addr1.s_addr = htonl(0x1020304);
	addr2.s_addr = htonl(0xc0a80101);

	str1 = inet_ntoa(addr1);
	memcpy(buf, str1, sizeof(str1));
	
	str2 = inet_ntoa(addr2);

	printf("%#lx -> %s \n", (long)addr1.s_addr, buf);
	printf("%#lx -> %s \n", (long)addr2.s_addr, str2);
	*/

	int i;
	struct hostent *host;

	if(argc < 2) {
		printf("Use: %s <hostname> \n", argv[0]);
		exit(1);
	}

	host = gethostbyname(argv[1]);

	for(i = 0; host -> h_addr_list[i]; i++) {
		printf("IP address %d : %s \n", i+1, 
			inet_ntoa(*(struct in_addr *)host-> h_addr_list[i]));
	}

	return 0;
}