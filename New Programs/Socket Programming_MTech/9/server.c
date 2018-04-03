#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
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
    	int n,count[256],pos,max,i;
    	    
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
	
	while(1)
    	{  
		//reading no. 
		memset(buffer, '\0', 1024); 
		memset(temp, '\0', 1024); 
          	valread = read(new_socket , buffer, 1024);
            	sscanf(buffer,"%s %d",temp,&n);
            	            
		//writing answer to buffer 	
		for(i=0;i<256;i++)
			count[i]=0;
		max=count[0]; pos=0;
		
		for(i=0;temp[i]!='\0';i++)
		{
			if(isalpha(temp[i]))			
				temp[i]=tolower(temp[i]);
			count[(int)temp[i]]++;
		}
	
		for(i=1;i<256;i++)
		{
			if(count[i]==n)
			{
				pos=i;
				break;
			}
			else if(max < count[i])
			{
				max=count[i];
				pos=i;	
			}
		}
		
		printf("%s ",temp);		
		strcpy(buffer,"\n");
		if(count[pos]==n)
			sprintf(temp,"The charcter with count %d is: %c",n,(char)pos);
		else
		{
			sprintf(temp,"The charcter with maximum count %d is: %c",max,(char)pos);
		}
		strcpy(buffer,strcat(buffer,temp));
	    	send(new_socket , buffer , strlen(buffer) , 0 );
		printf("%d\n",n);
    	}
    	printf("\n");
    	return 0;
}
