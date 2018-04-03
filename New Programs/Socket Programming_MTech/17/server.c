#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
    	struct sockaddr_in address;
    	int opt = 1;
    	int addrlen = sizeof(address);
    	char buffer[1024] = {0};
    	char temp[1024]={0};
    	char *hello = "\nHello";
	char *passward= "qwerty123";
    	    	    
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
        	
    	while(1)
    	{   
		//initial handshake		
		memset(buffer, '\0', 1024);
   	    	new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
            	valread = read(new_socket , buffer, 1024);
		
		//processing passward		
		if(strcmp(buffer,passward)==0)
		{  	
			memset(buffer, '\0', 1024);			
			strcpy(temp,"Access Granted");
			strcpy(buffer,"\n");	
			strcpy(buffer,strcat(buffer,temp));
			send(new_socket , buffer , strlen(buffer) , 0 );

			memset(buffer, '\0', 1024);
          		valread = read(new_socket , buffer, 1024);
            		printf("%s\n",buffer );

			memset(buffer, '\0', 1024);			
			strcpy(temp,hello);	
			strcpy(buffer,strcat(buffer,temp));
			send(new_socket , buffer , strlen(buffer) , 0 );
			
		}
		else 
		{
			memset(buffer, '\0', 1024);
			strcpy(temp,"Access Denied");
			strcpy(buffer,"\n");	
			strcpy(buffer,strcat(buffer,temp));
			send(new_socket , buffer , strlen(buffer) , 0 );
		}
    	}
    
    	printf("\n");
    	return 0;
}
