#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_endian.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
  char buffer[BUFFER_SIZE];
  char resp[] = "HTTP/1.0 200 OK\r\n"
                "Server: webserver-c\r\n"
                "Content-type: text/html\r\n\r\n"
                "<html>hello, world</html>\r\n";

  // 1 - create a socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    perror("webserver (socket)");
    return EXIT_FAILURE;
  }
  printf("socket created successfully\n");

  // 2 - Create the address to bind the socket to
  struct sockaddr_in server_addr;
  int server_addrlen = sizeof(server_addr);

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);

  if (bind(socketfd, (struct sockaddr *)&server_addr, server_addrlen) == -1) {
    perror("webserver (bind)");
    return EXIT_FAILURE;
  }
  printf("socket successfully bound to address\n");

  // 3 - Listen
  if (listen(socketfd, SOMAXCONN) == -1) {
    perror("webserver (listen)");
    return EXIT_FAILURE;
  }
  printf("server listening for connections\n");

  // 4 - Accept incoming connections
  for (;;) {
    int connection = accept(socketfd, (struct sockaddr *restrict)&server_addr,
                            (socklen_t *restrict)&server_addrlen);
    if (connection == -1) {
      perror("webserver (accept)");
      continue;
    }
    printf("connection accepted\n");

    // 5
    // 5.1 - Read from the socket
    int val = recv(connection, buffer, BUFFER_SIZE, 0);
    if (val < 0) {
      perror("webserver (recv)");
      continue;
    }

    // 5.2 - Write to the socket
    int sent = send(connection, resp, sizeof(resp), 0);
    if (sent < 0) {
      perror("webserver (send)");
      continue;
    }

    // 6 - close the connection
    close(connection);
    printf("connection closed\n");
  }

  return EXIT_SUCCESS;
}
