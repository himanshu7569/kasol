#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("Client Side Application\n");
  char *servIP = "127.0.0.1"; // First arg: server IP address (dotted quad)
  char *echoString = "This is String from client";

  in_port_t servPort = 80;

  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0) {
    printf("Error at 1\n");
    return 0;
  }

  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;

  int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);

  if (rtnVal == 0 || rtnVal < 0) {
    printf("Error at 2\n");
    return 0;
  }

  servAddr.sin_port = htons(servPort);

  if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    printf("Error at 3\n");
    return 0;
  }

  size_t echoStringLen = strlen(echoString);

  ssize_t numBytes = send(sock, echoString, echoStringLen, 0);

  if (numBytes < 0 || numBytes != echoStringLen) {
    printf("Error at 4\n");
    return 0;
  }

  unsigned int totalBytesRcvd = 0;
  fputs("Received: ", stdout);

  while (totalBytesRcvd < echoStringLen) {
    char buffer[BUFSIZ];
    numBytes = recv(sock, buffer, BUFSIZ - 1, 0);
    if (numBytes <= 0) {
      printf("Error at 5\n");
      return 0;
    }

    totalBytesRcvd += numBytes;
    buffer[numBytes] = '\0';
    fputs(buffer, stdout);
  }
  fputc('\n', stdout);
  close(sock);
  exit(0);
}