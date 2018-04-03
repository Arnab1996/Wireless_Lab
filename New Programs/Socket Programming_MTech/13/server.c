#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127
 
typedef struct database
{
 char question[50];
 char answer[30];
}db;
 
int main(int argc, char const *argv[])
{
 int server_fd, new_socket, valread;
     struct sockaddr_in address;
     int opt = 1;
     int addrlen = sizeof(address);
     char buffer[1024] = {0};
     char temp[1024]={0};
     char *hello = "\nConnection_Established";
     int n=0,i;
        
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

 db s[10]={ {"What is the time?","10:10 AM"},
   {"What is the date?","01-01-18"},
   {"What is the temperature right now?","20 degree celsius"},
   {"Which month is going on?","January"},
   {"Which year is going on?","2018"},
   {"Who is the prime minister of India?","Narendra Modi"},
   {"What is the capital of India?","Delhi"},
   {"Who is the president of India?","Ram Nath Kovind"},
   {"Who is the captain of Indian cricket team?","Virat Kohli"},
   {"Who is the CEO of Flipkart?","Kalyan Krishnamurthy"}};
   
 //initial handshake
 memset(buffer, '\0', 1024);
     new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
     valread = read(new_socket , buffer, 1024);
     printf("%s",buffer);
     send(new_socket , hello , strlen(hello) , 0 ); 
 
 while(1)
     { 
	n++;
	
  //reading no.
	  memset(buffer, 0, 1024);
           valread = read(new_socket , buffer, 1024);
            // sscanf(buffer,"%d",&n);
               if(strcmp(buffer,"exit") == 0)
			break;         
	  //writing answer to buffer  
	  for(i=0;i<10;i++){
		//printf("\n\t i: %d and compare : %d",i,strcmp((s[i].question), buffer));
		if(strcmp((s[i].question), buffer) == 0)
			break;
	  }
	  if(i==10){
		strcpy(buffer,"Try again");	
		strcat(buffer,"\n");
	  }
	  else{
		printf("\n\t Answer >> %s ",s[i].answer);
		  strcpy(buffer,s[i].answer);
		  strcat(buffer,"\n");
	  }
	      send(new_socket , buffer , strlen(buffer) , 0 );
	      printf("%s\n",buffer);
	if(n==3)
		break;
     }
     printf("\n");

     return 0;
}
