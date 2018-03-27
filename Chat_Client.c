/*Client Side*/
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
intsd,con,port,i,Res;
char content[30];
structsockaddr_in cli;
if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
{
printf("\nSocket problem");
return 0;
}
bzero((char*)&cli,sizeof(cli));
cli.sin_family = AF_INET;
printf("ENTER PORT NO:\n");
scanf("%d",&port);
cli.sin_port=htons(port);
cli.sin_addr.s_addr=htonl(INADDR_ANY);
con=connect(sd,(structsockaddr*)&cli,sizeof(cli));
if(con==-1)
{
printf("\nConnection error");
return 0;
}
if(fork())
{
printf("\nEnter the data to be send type exit for stop:\n");
scanf("%s",content);
while(strcmp(content,"exit")!=0)
{
send(sd,content,30,0);
scanf("%s",content);
}
send(sd,"exit",5,0);
}
else
{
i=recv(sd,content,30,0);
while(strcmp(content,"exit")!=0)
{
printf("\nServer: %s\n",content);
i=recv(sd,content,30,0);
}
send(sd,"exit",5,0);
}
close(sd);
return 0;
}