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
    	char *hello = "\nConnection_Established";
    	int n,i;
    	double fac[1000];
    
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
    
    	fac[0]=1;fac[1]=1;
    	for(i=2;i<1000;i++)
    	{
        	fac[i]=fac[i-1]*i;
    	}

    	while(1)
    	{   
		//initial handshake		
		memset(buffer, '\0', 1024);
   	    	new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
            	valread = read(new_socket , buffer, 1024);
	    	printf("\n%s",buffer);
            	send(new_socket , hello , strlen(hello) , 0 );
            	memset(buffer, '\0', 1024);
   
		//reading no.  
          	valread = read(new_socket , buffer, 1024);
            	sscanf(buffer,"%d", &n);
		strcpy(buffer,"\n");	
            	            
		//writing answer to buffer                 	
		for(i=1;i<=1;i++)
	    	{
            		sprintf(temp,"%d!: %g ",n,fac[n]);
            		strcpy(buffer,strcat(buffer,temp));
	    	}
	    	send(new_socket , buffer , strlen(buffer) , 0 );
	    	printf("%d\n",n);
    	}
    
    	printf("\n");
    	return 0;
}
