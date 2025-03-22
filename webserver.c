#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main(void) {
  // create a socket
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    perror("webserver (socket)");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
