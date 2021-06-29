#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Start of tcp-socket.c learning program
int main() {

  char *servIP = "169.1.1.1";

  // TCP stream socket
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0) {
    printf("Error creating socket stream");
  } else {
    printf("Working 1 %d \n", sock);
  }

  struct sockaddr_in servAddr; // Server Address
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;

  int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
  if (rtnVal < 0) {
    printf("Error creating socket stream");
  } else {
    printf("Working 2 %d \n", rtnVal);
  }

  //   servAddr.sin

  return 0;
}