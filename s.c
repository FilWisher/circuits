#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 10000
#define MAX_REQUEST 10000
#define SOCK_PATH "/tmp/circuits"

typedef struct sockaddr_un Sock_Address;

#define ADDRSIZE sizeof(Sock_Address)

Sock_Address
make_socket_address(void)
{
  Sock_Address addr;
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, SOCK_PATH);
  return addr;
}

int
create_socket(void)
{
  int fd;
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("create_socket: socket");
    exit(1);
  }
  return fd;
}

void
bind_socket_to_fd(int fd, struct sockaddr *addr)
{
  unlink(SOCK_PATH);     /* unlink path incase already open */ 
  //printf("attempting to bind to %s\n", addr->);
  if (bind(fd, addr, ADDRSIZE) == -1) {
    perror("bind_socket_to_fd: bind");
    exit(1);
  }
}

int
accept_waiting_connection(int server, struct sockaddr *connection, socklen_t *len)
{
  int c_fd; 
  if ((c_fd = accept(server, connection, len)) == -1) {
    perror("accept_waiting_connection: accept"); 
    exit(1);
  } else {
    printf("connected");
  }
  return c_fd;
}

void
send_response(int client_fd, char *response)
{
  if (send(client_fd, response, strlen(response), 0) < 0) {
    perror("send_response: send");
  }
}

int
receive_request(int client_fd, char *request)
{
  return recv(client_fd, request, MAX_REQUEST, 0);
}

int
main(int argc, char *argv[])
{
  
  int s_fd, c_fd; 
  Sock_Address addr, connection;
  socklen_t len = sizeof(Sock_Address);
  char *request;
 
  s_fd = create_socket(); 
  addr = make_socket_address();
  bind_socket_to_fd(s_fd, (struct sockaddr *)&addr);
  
  listen(s_fd, 7);
 
  while (1) {
    
    int err, n, c_fd, done = 0;

    c_fd = accept_waiting_connection(s_fd, 
        (struct sockaddr *)&connection, &len);
        
    while (!done) {
    
      n = receive_request(c_fd, request);
    
      printf("\nrequest: ", request);
    
      send_response(c_fd, "ARTY FARTY");
      
     
      done = 1; 
    }
  }

  unlink(SOCK_PATH);
  return 0;
}
