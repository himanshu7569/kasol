#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main()
{
int network_socket;
//creating a socket
int nSocket;
nSocket = socket(AF_INET,SOCK_STREAM,0);
if(nSocket < 0)
{
printf("Socket is not opened: %d",nSocket);
}
else
{
printf("Socket is opened:%d",nSocket);
}
//Specify an address for the socket
//initialize the environment for sockaddr(in this case IPV4) structure

struct sockaddr_in svr;
svr.sin_family=AF_INET;
svr.sin_port = htons(9002);
svr.sin_addr.s_addr= INADDR_ANY;
//memset(&(svr.sin_zero),0,8);
int connection_status=connect(network_socket,(struct sockaddr *) &svr, sizeof(svr));
if(connection_status == -1)
{
printf("An error came in between connection to the remote socket");
}
else

return 0;
}
