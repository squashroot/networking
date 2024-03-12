// Title:			http.c
// Creator:			John Coleman
// Creation Date:		02/27/2024
// Modification Date:		02/27/2024
// Desscription:  
// A basic socket that sends HTTP header with HTML data.
//
// Status: Work-In-Progress

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#define RBUF 512

int main(int argc, char *argv[])
{
	int i = 0;
	char response[RBUF];
	int lsock = socket(AF_INET, SOCK_STREAM, 0);
	int psock, psize;
	struct sockaddr_in hostaddr, peeraddr;
	
	hostaddr.sin_family		= AF_INET;
	hostaddr.sin_port		= htons(50080);
	hostaddr.sin_addr.s_addr	= INADDR_ANY;

	bind(lsock, (struct sockaddr*)&hostaddr, sizeof(hostaddr));

	listen(lsock, 100);

	psize = sizeof(struct sockaddr_in);
	while(1)
	{
		psock = accept(lsock, (struct sockaddr*)&peeraddr, &psize);
		sprintf(response, "HTTP/1.1 200 OK\r\ncontent-type: text/html\r\ncontent-length: %d\r\n\n<html>\r\n<title>\r\n\tTesting\r\n</title>\r\n<body>\r\n\tThis is a test.\r\n</body>\r\n</html>\r\n", RBUF);
		send(psock, response, sizeof(response), 0);

		sleep(180);

		close(psock);
	}

	return 0;
}
