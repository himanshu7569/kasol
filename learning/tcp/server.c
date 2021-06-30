#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_endian.h>
#include <sys/_types/_in_port_t.h>
#include <sys/_types/_socklen_t.h>
#include <sys/socket.h>
#include <sys/types.h>

// Max request this server can handle
static const int MAXPENDING = 5;

// TODO
void HandleTCPClient(int clntSocket) {}

int main() {

  printf("Server Side Application\n");

  // First argument according to book
  char *port = "80";

  in_port_t servPort = atoi(port);

  int servSock;
  servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (servSock < 0) {
    printf("Error at 1\n");
    return 0;
  }

  // Address Structure
  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(servPort);

  // Binding socket to port
  if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    printf("Error at 2\n");
    return 0;
  }

  // Listen for incomming request
  if (listen(servSock, MAXPENDING) < 0) {
    printf("Error at 3\n");
    return 0;
  }

  // Run forever
  for (;;) {
    // Client Address
    struct sockaddr_in clntAddr;

    socklen_t clntAddrLen = sizeof(clntAddr);

    int clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen);
    if (clntSock < 0) {
      printf("Error at 4\n");
      return 0;
    }

    // Connected to a client
    char clntName[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName,
                  sizeof(clntName)) != NULL) {
      printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
    } else {
      puts("Unable to get client address");
    }
    HandleTCPClient(clntSock);
  }
  return 0;
}