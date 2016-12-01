#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>

#define ICMP_SIZE (sizeof(struct icmp))
#define ICMP_ECHO  8
#define ICMP_ECHOREPLY  0
#define BUF_SIZE 1024
#define NUM    5

#define UCHAR  unsigned char
#define USHORT unsigned short
#define UINT   unsigned int

struct icmp {
	unsigned char type;
	unsigned char code;

	unsigned short checksum;
	unsigned short id;
	unsigned short sequence;

	struct timeval timestamp;
};

struct ip {
	
	#if __BYTE_ORDER == __LITTLE_ENDIAN
	UCHAR hlen: 4;
	UCHAR version: 4;
	#endif

	#if __BYTE_ORDER == __BIG_ENDIAN
	UCHAR version: 4;
	UCHAR hlen: 4;
	#endif

	UCHAR tos;
	USHORT len;
	USHORT id;
	USHORT offset;
	UCHAR ttl;
	UCHAR protocol;
	USHORT checksum;

	struct in_addr ipsrc;
	struct in_addr ipdst;
};

char buf[BUF_SIZE] = {0};

/*
USHORT checkSum(USHORT *, int);
float timediff(struct timeval *, struct timeval *);
void pack(struct icmp *, int);
int unpack(char *, int, char *);
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

float timediff(struct timeval *begin, struct timeval *end) {
	int n;

	n = (end -> tv_sec - begin->tv_sec) * 1000000 
		+ (end -> tv_usec - begin -> tv_usec);

	return (float)(n / 1000);
}

void pack(struct icmp *icmp, int sequence) {
	icmp -> type = ICMP_ECHO;
	icmp -> code = 0;
	icmp -> checksum = 0;
	icmp -> id = getpid();
	icmp -> sequence = sequence;
	gettimeofday(&icmp -> timestamp, 0);
	icmp -> checksum = checkSum((USHORT *)icmp, ICMP_SIZE);
}

int unpack(char *buf, int len, char *addr) {
	int i, ipheadlen;
	struct ip *ip;
	struct icmp *icmp;
	float rtt;
	struct timeval end;

	ip = (struct ip *)buf;

	ipheadlen = ip -> hlen << 2;
	icmp = (struct icmp *)(buf + ipheadlen);

	len -= ipheadlen;

	if(len < 8) {
		printf("ICMP packets\'s length is less that 8 \n");
		return -1;
	}

	if(icmp -> type != ICMP_ECHOREPLY || icmp -> id != getpid()) {
		printf("ICMP pakcets are not sent by us \n");
		return -1;
	}
}

int main(int argc, char *argv[]) {
	
	struct hostent *host;
	struct icmp sendicmp;
	struct sockaddr_in from;
	struct scokaddr_in to;

	int fromlen = 0;
	int sockfd;

	int nsend = 0;
	int nreceived = 0;
	int i, n;
	in_addr_t inaddr;

	memset(&from, 0, sizeof(struct sockaddr_in));
	memset(&to, 0, sizeof(struct sockaddr_in));

	if(argc < 2) {
		printf("use: %s hostname / IP address \n", argv[0]);
		exit(1);
	}

	if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1) {
		printf("socket() error \n");
		exit(1);
	}

	to.sin_family = AF_INET;

	if(inaddr = inet_addr(argv[1]) == INADDR_NONE) {
		if((host = gethostbyname(argv[1])) == NULL) {
			printf("gethostbyname() error \n");
			exit(1);
		}
		to.sin_addr = *(struct in_addr *)host -> h_addr_list[0];
	} else {
		to.sin_addr.s_addr = inaddr;
	}

	printf("ping %s (%s) : %d bytes of data. \n", argv[1], inet_ntoa(to.sin_addr), (int)ICMP_SIZE);
	
	for(i = 0; i < NUM; i++) {
		nsend++;
		memset(&sendicmp, 0, ICMP_SIZE);
		pack(&sendicmp, nsend);

		if(sendto(sockfd, &sendicmp, ICMP_SIZE, 0, (struct sockaddr *)&to, sizeof(to)) == -1) {
			printf("sendto() error \n");
			continue;
		}

		if((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&from, &fromlen)) < 0) {
			printf("recvfrom() error \n");
			continue;
		}
		nreceived++;

		if(unpack(buf, n, inet_ntoa(from.sin_addr)) == -1) {
			printf("unpack() error \n");
		}

		sleep(1);
	}

	printf("---- %s ping statistics ----\n", argv[1]);
	printf("%d packets transmitted, %d received, %%%d packet loss \n", nsend, nreceived,
		(nsend - nreceived) / nsend * 100);
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
	/*
	int i;
	
	
	if(argc < 2) {
		printf("Use: %s <hostname> \n", argv[0]);
		exit(1);
	}

	host = gethostbyname(argv[1]);

	for(i = 0; host -> h_addr_list[i]; i++) {
		printf("IP address %d : %s \n", i+1, 
			inet_ntoa(*(struct in_addr *)host-> h_addr_list[i]));
	}
	*/
	return 0;
}