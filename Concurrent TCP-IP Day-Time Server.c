#Server Program:
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
struct sockaddr_in sa;
struct sockaddr_in cli;
int sockfd,conntfd;
int len,ch;
char str[100];
time_t tick;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
printf("\nError in Socket");
exit(0);
}
else printf("\nSocket has opened");
bzero(&sa,sizeof(sa));
sa.sin_port = htons(5600);
sa.sin_addr.s_addr=htonl(0);
if(bind(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0)
{

printf("\nError in binding");
}
else
printf("\nBinded Succesfully");
listen(sockfd,50);
for(;;)
{
len = sizeof(ch);
conntfd=accept(sockfd,(struct sockaddr*)&cli,&len);
printf("\nAccepted");
tick = time(NULL);
snprintf(str, sizeof(str), "%s",ctime(&tick));
printf("%s", str);write(conntfd,str,100);
}
return 0;
}

#Client Program:
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
struct sockaddr_in sa, cli;
int n,sockfd;
int len;
char buff[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
printf("\nError in Socket");
exit(0);
}
else printf("\nSocket is Opened");
bzero(&sa,sizeof(sa));
sa.sin_family=AF_INET;
sa.sin_port=htons(5600);
if(connect(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0)
{
printf("\nError in connection failed");
exit(0);
}
else
printf("\nClient Connected Successfully");
if(n=read(sockfd,buff,sizeof(buff))<0)

{
printf("\nError in Reading");
exit(0);
}
else
{
printf("\nMessage Read %s", buff);
}
return 0;
}