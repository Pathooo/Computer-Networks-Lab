#Server Program:
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024
int main(int argc, char **argv)
{
int sockfd;
int n;
socklen_t len;
char msg[1024];
struct sockaddr_in serveradd , clientadd;
sockfd = socket(AF_INET,SOCK_DGRAM,0);
bzero(&serveradd,sizeof(serveradd));
serveradd.sin_family = AF_INET;
serveradd.sin_addr.s_addr = INADDR_ANY;
serveradd.sin_port = htons(5656);
printf("\nServer has Binded");
bind(sockfd,(struct sockaddr*)&serveradd, sizeof(serveradd));
printf("\nListening to the Client...");
for(;;)
{
printf("\n");
len=sizeof(clientadd);
n=recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr*)&clientadd,&len);

printf("The Client's Message is : %s\n",msg);
if(n<6)
perror("Send Error");
sendto(sockfd,msg,n,0,(struct sockaddr*)&clientadd,len);
}
return 0;
}

#Client Program:
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#define MAXLINE 1024
int main(int argc,char* argv[])
{
int sockfd;
int n;
socklen_t len;
char sendline[1024] , recvline[1024];
struct sockaddr_in serveradd;
strcpy(sendline,"");
printf("\n Enter the message to be sent : ");
scanf("%s",sendline);
sockfd = socket(AF_INET,SOCK_DGRAM,0);
bzero(&serveradd, sizeof(serveradd));
serveradd.sin_family = AF_INET;
serveradd.sin_addr.s_addr = inet_addr("127.0.0.1");
serveradd.sin_port=htons(5656);
connect(sockfd, (struct sockaddr*)&serveradd, sizeof(serveradd));
len = sizeof(serveradd);
sendto(sockfd,sendline,MAXLINE,0,(struct sockaddr*)&serveradd,len);
n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL,NULL);
recvline[n] = 0;
printf("\nServer's Echo Message : %s\n\n", recvline);
return 0;
}