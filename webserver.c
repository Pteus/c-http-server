#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_endian.h>
#include <sys/socket.h>

#define PORT 8080

int main(void) {
  // 1 - create a socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    perror("webserver (socket)");
    return EXIT_FAILURE;
  }

  // 2 - Create the address to bind the socket to
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);

  if (bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("webserver (bind)");
    return EXIT_FAILURE;
  }

  // 3 - Listen
  if (listen(socketfd, SOMAXCONN) == -1) {
    perror("webserver (listen)");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
