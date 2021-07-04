#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
//create a buffer to store the incoming messages
char buffer[50]={0};

//create a struct top store address information
struct sockaddr_in servaddr={0};

//create a socket
int sockfd=socket(AF_INET,SOCK_DGRAM, 0);
if(sockfd==-1)
{
perror("Failed to create socket");
exit(EXIT_FAILURE);
}
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(12345);
servaddr.sin_addr.s_addr= INADDR_ANY;

//now bind socket to this address
int rc=bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr));
if(rc==-1)
{
perror("failed to bind");
close(sockfd);
exit(EXIT_FAILURE);
}
socklen_t len=0;

//now recieve data
int n=recvfrom(sockfd,(char *)buffer,50,MSG_WAITALL,0,&len);
buffer[n] = '\n';
printf("%s",buffer);
close(sockfd);
return 0;
}
