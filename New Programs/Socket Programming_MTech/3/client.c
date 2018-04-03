#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127

int main(int argc, char const *argv[])
{
    	struct sockaddr_in address;
    	int sock = 0, valread;
    	struct sockaddr_in serv_addr;
    	char buffer[1024] = "\nRequest_from_Client ";
    	char in[1024];
    	int n;
    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    	{
        	printf("\n Socket creation error ");
        	return -1;
    	}

    	memset(&serv_addr, '0', sizeof(serv_addr));

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(PORT);
    	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    	send(sock , buffer , strlen(buffer) , 0 );
    	valread = read( sock , buffer, 1024);
    	printf("%s\n",buffer );

    	printf("\nEnter the number: ");
    	gets(buffer) ;
    	send(sock , buffer , strlen(buffer) , 0 );
    	printf("\nRequest sent");
        
	memset(buffer, '\0', 1024);    
    	valread = read(sock , buffer, 1024);
    	printf("%s\n",buffer );
    
    	printf("\n");
    	return 1;
}


