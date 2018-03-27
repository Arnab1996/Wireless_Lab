/*Server Side*/
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
main()
{
intsd,i,len,bi,nsd,port;
char content[30];
structsockaddr_inser,cli;
if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
{
printf("\nSocket problem");
return 0;
}
printf("\nSocket created\n");
bzero((char*)&cli,sizeof(ser));
printf("ENTER PORT NO:\n");
scanf("%d",&port);
printf("\nPort Address is %d\n:",port);
ser.sin_family=AF_INET;
ser.sin_port=htons(port);
ser.sin_addr.s_addr=htonl(INADDR_ANY);
bi=bind(sd,(structsockaddr *)&ser,sizeof(ser));
if(bi==-1)
{
printf("\nBind error, Port busy, Plz change port in client and server");
return 0;
}
i=sizeof(cli);
listen(sd,5);
nsd = accept(sd,((structsockaddr *)&cli),&i);
if(nsd==-1)
{
printf("\nCheck the description parameter\n");
return 0;
}
printf("\nConnection accepted!");
if(fork())
{
printf("\nEnter the data to be send type exit for stop:\n");
scanf("%s",content);
while(strcmp(content,"exit")!=0)
{
send(nsd,content,30,0);
scanf("%s",content);
}
send(nsd,"exit",5,0);
}
else
i = recv(nsd,content,30,0);
while(strcmp(content,"exit")!=0)
{
printf("\nClient: %s\n",content);
i=recv(nsd,content,30,0);
}
printf("\nBye");
send(nsd,"Offline",10,0);
close(sd);
close(nsd);
return 0;
}