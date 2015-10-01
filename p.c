#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 10000
#define SOCK_PATH "/tmp/circuits"

int
main(void)
{
	int s, t, len, done;
	struct sockaddr_un server;
	char request[MAX_BUF];
	char response[MAX_BUF];
	
	if((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	
  printf("Trying to connect");

	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, SOCK_PATH);
	len = strlen(server.sun_path) + sizeof(server.sun_family);
	
	if (connect(s, (struct sockaddr *)&server, len) == -1) {
		perror("connect");
		exit(1);
	}
	
	printf("\nconnected\n");
	
	while (1)	{

		done = 0;

		printf(">");
		fgets(request, 1000, stdin);

		if (send(s, request, strlen(request), 0) == -1)	 {
			perror("send");
			exit(1);
		}
		
		if((t = recv(s, response, 100, 0)) > 0) {
			response[t] = '\0';
			printf("echo> %s\n", response);
			done = 1;
		} else {
			if (t < 0) perror("recv");
			else printf("server closed connection");
			exit(1);
		}
	
	//	if (done) close(s);
	}
	
	close(s);
	return 0;
}
