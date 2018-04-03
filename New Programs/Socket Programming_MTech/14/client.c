#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127
#define N strlen(g)

char t[28],s[28],cs[28],g[]="11000000000000101";
int a,e,c;

void xor(){
    for(c = 1;c < N; c++)
    cs[c] = (( cs[c] == g[c])?'0':'1');
}
 
void crc(){
    for(e=0;e<N;e++)
        cs[e]=t[e];
    do{
        if(cs[0]=='1')
            xor();
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1];
        cs[c]=t[e++];
    }while(e<=a+N-1);
}

int main(int argc, char const *argv[])
{
     struct sockaddr_in address;
     int sock = 0, valread;
     struct sockaddr_in serv_addr;
     char buffer[1024] = "\nRequest_from_Client ";
     char in[1024];
     int m,n;
     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     {
         printf("\nSocket creation error ");
         return -1;
     }
     memset(&serv_addr, '0', sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(PORT);
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
     send(sock , buffer , strlen(buffer) , 0 );
     valread = read( sock , buffer, 1024);
     printf("%s",buffer );
     printf("\nEnter data : ");
     scanf("%s",t);
     a=strlen(t);
     snprintf(s, sizeof(s), "%d", a);
     for(e=a;e<a+N-1;e++)
	t[e]='0';
     crc();
     for(e=a;e<a+N-1;e++)
        t[e]=cs[e-a];
	printf("%s\n",t);
	//strcpy(s,t);
     printf("\nTest error detection 0(yes) 1(no)? : ");
    scanf("%d",&e);
    if(e==0)
    {
        do{
            printf("\nEnter the position where error is to be inserted : ");
            scanf("%d",&e);
        }while(e==0 || e>a+N-1);
        t[e-1]=(t[e-1]=='0')?'1':'0';
        strcpy(buffer,s);
	strcat(buffer,"|");
	strcat(buffer,t);
	printf("%s\n",buffer);
        send(sock , buffer , strlen(buffer) , 0 );
	for(n=0;n<10000;n++);
	valread = read(sock , buffer, 1024);
	printf("%s\n",buffer);
    }
    else
   {
 	strcpy(buffer,s);
	strcat(buffer,"|");
	strcat(buffer,t);
	printf("%s\n",buffer);
	send(sock , buffer , strlen(buffer) , 0 );
	for(n=0;n<10000;n++);
	valread = read(sock , buffer, 1024);
	printf("%s\n",buffer);
   }	
     return 1;
}


