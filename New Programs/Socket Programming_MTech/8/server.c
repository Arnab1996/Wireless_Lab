#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127
 
typedef struct student
{
	char name[50];
	int reg_no;
	char program[30];
	char discipline[50];
	long phone;
	char hostel[50];
}stud;
 
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

	stud s[10]={	{"Aditya Sudheer",1493,"M.Tech","Computer Science and Engineering",9431172007,"Jasper"},
			{"Prakash Kumar",1524,"M.Tech","Computer Science and Engineering",9430377299,"Jasper"},
			{"Prateek Kumar",1535,"M.Tech","Computer Science and Engineering",9717702784,"Jasper"},
			{"Bharathi Giri PV",1538,"M.Tech","Computer Science and Engineering",9470523102,"New Ruby"},
			{"Mamta Kumari",1574,"M.Tech","Computer Science and Engineering",9955601651,"New Ruby"},
			{"Akash Sinha",1593,"M.Tech","Computer Science and Engineering",9454043920,"Jasper"},
			{"Arkojyoti Mitra",1616,"M.Tech","Computer Science and Engineering",7706845933,"Jasper"},
			{"Parul Verma",1731,"M.Tech","Computer Science and Engineering",7022372770,"New Ruby"},
			{"Khyati Kapoor",1748,"M.Tech","Computer Science and Engineering",9471195335,"New Ruby"},
			{"Havan Somaiya",1832,"M.Tech","Computer Science and Engineering",770685933,"Jasper"}};
  	
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
		int l=0,r=9,mid=(l+r)/2;
		while(s[mid].reg_no!=n && l<=r)
		{
			if(s[mid].reg_no > n)
				r--;
			else 
				l++;
			mid=(l+r)/2;
		}
		
		strcpy(buffer,"\n");
		if(s[mid].reg_no!=n)
			strcpy(buffer,"Record Not found !!");
		else
		{
			strcpy(buffer,strcat(buffer,s[mid].name));
			strcpy(buffer,strcat(buffer,"\n"));
			strcpy(buffer,strcat(buffer,s[mid].program));
			strcpy(buffer,strcat(buffer,"\n"));
			strcpy(buffer,strcat(buffer,s[mid].discipline));
			strcpy(buffer,strcat(buffer,"\n"));
			sprintf(temp,"%ld",s[mid].phone);	
			strcpy(buffer,strcat(buffer,temp));
			strcpy(buffer,strcat(buffer,"\n"));
			strcpy(buffer,strcat(buffer,s[mid].hostel));
		}
	    	send(new_socket , buffer , strlen(buffer) , 0 );
	    	printf("%d\n",n);
    	}
    	printf("\n");
    	return 0;
}
