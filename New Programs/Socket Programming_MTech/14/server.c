#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127
#define N strlen(g)
 
char t[28],s[28],cs[28],g[]="11000000000000101";
int a=4,e,c;

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
 int server_fd, new_socket, valread;
     struct sockaddr_in address;
     int opt = 1;
     int addrlen = sizeof(address);
     char buffer[1024] = {0};
     char temp[1024]={0};
     char *hello = "\nConnection_Established";
     int n;
       char *p; 
     // Creating socket file descriptor
     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
         printf("\nsocket failed");
         exit(EXIT_FAILURE);
     }
     // Forcefully attaching socket to the port 8080
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons( PORT );
     bind(server_fd, (struct sockaddr *)&address,sizeof(address));
     listen(server_fd, 10);
 
   
 //initial handshake
 memset(buffer, '\0', 1024);
     new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
     valread = read(new_socket , buffer, 1024);
     printf("%s",buffer);
     send(new_socket , hello , strlen(hello) , 0 ); 
 
    valread = read(new_socket , buffer, 1024);
  //sscanf(buffer,"%d",&n);
  
    p = strtok(buffer, "|");
 	sscanf(p,"%d",&a);
    p = strtok(NULL, "|");
	strcpy(t,p);
	/*for(n=0;n<strlen(buffer)-1;n++)
		t[n] = buffer[n];
	printf("\n buffer length %d\n",strlen(buffer));*/
memset(buffer, '\0', 1024);
printf("%d\n%s\n",a,t);
	crc();
for(n=0;n<10000;n++);
  printf("\nNew Checksum is : %s\n t length : %d \n",cs,strlen(t));
    for(e=0;(e<N-1) && (cs[e]!='1');e++);
        if(e<N-1)
            strcpy(buffer,"\nbad data\n\n");
        else
            strcpy(buffer,"\ngood data\n\n");
     send(new_socket , buffer , strlen(buffer) , 0 );
     return 0;
}
