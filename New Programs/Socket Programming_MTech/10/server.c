#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127
 
typedef struct employee
{
	char name[50];
	int emp_id;
	int total;
	int balance;
	int extra;
}emp;
 
int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
    	struct sockaddr_in address;
    	int opt = 1;
    	int addrlen = sizeof(address);
    	char buffer[1024] = {0};
    	char temp[1024]={0};
    	char *hello = "\nConnection_Established";
    	int m,n;
    	    
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

	emp e[10]={	{"Aditya Sudheer",1493,30,9,5},
			{"Prakash Kumar",1524,30,14,4},
			{"Prateek Kumar",1535,30,10,3},
			{"Bharathi Giri PV",1538,30,14,4},
			{"Mamta Kumari",1574,30,13,5},
			{"Akash Sinha",1593,30,10,4},
			{"Arkojyoti Mitra",1616,30,11,4},
			{"Parul Verma",1731,30,9,3},
			{"Khyati Kapoor",1748,30,6,2},
			{"Havan Somaiya",1832,30,20,8}};
  	
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
            	sscanf(buffer,"%d %d",&n,&m);
            	            
		//writing answer to buffer 	
		int l=0,r=9,mid=(l+r)/2;
		while(e[mid].emp_id!=n && l<=r)
		{
			if(e[mid].emp_id > n)
				r--;
			else 
				l++;
			mid=(l+r)/2;
		}
		
		strcpy(buffer,"\n");
		if(e[mid].emp_id!=n)
			strcpy(buffer,"Record Not found !!");
		else
		{
			strcpy(buffer,strcat(buffer,e[mid].name));
			strcpy(buffer,strcat(buffer,"\nTotal Leaves: "));
			sprintf(temp,"%d",e[mid].total);	
			strcpy(buffer,strcat(buffer,temp));
			strcpy(buffer,strcat(buffer,"\nLeaves Left: "));
			sprintf(temp,"%d",e[mid].balance);	
			strcpy(buffer,strcat(buffer,temp));
			strcpy(buffer,strcat(buffer,"\nExtra Leaves Available: "));
			sprintf(temp,"%d",e[mid].extra);	
			strcpy(buffer,strcat(buffer,temp));
			if(e[mid].extra+e[mid].balance>=m)
				strcpy(buffer,strcat(buffer,"\nLeaves CAN be availed"));
			else
				strcpy(buffer,strcat(buffer,"\nLeaves CANNOT be availed"));
		}
	    	send(new_socket , buffer , strlen(buffer) , 0 );
	    	printf("%d %d\n",n,m);
    	}
    	printf("\n");
    	return 0;
}
