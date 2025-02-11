#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// #define LISTENADDR "0.0.0.0"
#define LISTENADDR "127.0.0.1"

/* global variables */
char *error;

/* return 0 on error, or it returns a socet fd*/
int srv_init(int portno) {
	int s;
	struct sockaddr_in srv;
	
	s = socket(AF_INET, SOCK_STREAM, INADDR_ANY);
	if (s < 0) {
		error = "socket() error"; 
		return 0;
	} 

	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(LISTENADDR);
	srv.sin_port = htons(portno);

	if (bind(s, (struct sockaddr *)&srv, sizeof(srv))) {
		error = "bind() error";
		close(s);
		return 0;
	}

	if (listen(s, 5)) {
		close(s);
		error = "listen() error";
		return 0;
	}

	return s;
}

/* returns 0 on error, or returns the new client's socked fd */
int cli_accept(int s) {
	int c;
	socklen_t addrlen;
	struct sockaddr_in cli;

	addrlen = 0;
	memset(&cli, 0, sizeof(cli));
	c = accept(s, (struct sockaddr *)&cli, &addrlen);
	if (c < 0) {
		error = "accept() error";
		return 0;
	}

	return c;
}

void cli_conn(int s, int c) {};

int main(int argc, char *argv[]) {
	int s, c; // socket file descriptor
	char *port;
	
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <listening port>\n", argv[0]);
		return -1;
	} else {
		port = argv[1];
	}

	s = srv_init(atoi(port));

	if(!s) {
		fprintf(stderr, "%s\n", error);
		return -1;
	}

	printf("Listening on %s:%s\n", LISTENADDR, port);
	while(1) {
		c = cli_accept(s);
		if (!c) {
			fprintf(stderr, "%s\n", error);
			continue;
		}

		printf("Incoming connection\n");
		if (!fork()) 
			cli_conn(s, c);
		/* 
			for the main process: return the new process id 
			for the new process: return 0
		*/

	}
	return -1;
}
