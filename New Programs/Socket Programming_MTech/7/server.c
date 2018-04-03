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
    	int n,i,m;
	int seq[1000];
    	    
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

	seq[0]=3;
	for(i=1,m=0;i<1000;i++,m+=4)
		seq[i]=seq[i-1]+m;  
  	
	//initial handshake
	memset(buffer, '\0', 1024);
    	new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
    	valread = read(new_socket , buffer, 1024);
    	printf("%s",buffer);
    	send(new_socket , hello , strlen(hello) , 0 );	
	
	while(1)
    	{  
		//reading no. 
		memset(buffer, '\0', 1024); 
          	valread = read(new_socket , buffer, 1024);
            	sscanf(buffer,"%d",&n);
            	            
		//writing answer to buffer 
		memset(buffer, '\0', 1024); 	
		sprintf(buffer,"%d",seq[n]);	
	    	send(new_socket , buffer , strlen(buffer) , 0 );
	    	printf("%d\n",n);
    	}
    	//goto test;
    	printf("\n");
    	return 0;
}
