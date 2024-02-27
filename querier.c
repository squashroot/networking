// Author   :     John Coleman
// Creation :     02.01.2024
// Modified :     02.27.2024
// Build    :     gcc -o querier querier.c

// Info     :
// Very simple DNS client that queries a domain name
// then prints the returned IP's to standard out.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define IPBUF 256

int main(int argc, char *argv[])
{
	struct addrinfo ipinfo;
	struct addrinfo *result, *vector;
	int aret;
	size_t len;
	ssize_t nread;
	char ip[IPBUF];

	if(argc<2 || argc>2)
	{
		fprintf(stdout, "Command: %s host\n", argv[0]);
		return 1;
	}

	// Obtain addresses matching host
	memset(&ipinfo, 0, sizeof(struct addrinfo));
	ipinfo.ai_family = AF_UNSPEC;
	ipinfo.ai_socktype = SOCK_DGRAM;
	ipinfo.ai_flags = 0;
	ipinfo.ai_protocol = 0;

	// int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
	aret = getaddrinfo(argv[1], NULL, &ipinfo, &result);
	if(aret!=0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(aret));
		exit(EXIT_FAILURE);
	}

	for(vector=result; vector!=NULL; vector=vector->ai_next)
	{
		// int getnameinfo(const struct sockaddr *addr, socklen_t addrlen, char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags);
		getnameinfo(vector->ai_addr, vector->ai_addrlen, ip, sizeof(ip), NULL, 0, NI_NUMERICHOST);
		fprintf(stdout, "%s\n", ip);
	}

	return 0;
}
