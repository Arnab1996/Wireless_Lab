#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127
 
typedef struct products
{
 char item_id[10];
 char item_name[20];
 char price[20];
 char no_of_items_available[30];
}prod;
 
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
 prod s[2]={ {"I-01","Paneer","Rs. 25/100gms","50 pieces/100 gms"},
   {"I-02","Washing powder","Rs. 20/packet","20 packets"}};
   
   
 //initial handshake
 memset(buffer, '\0', 1024);
     new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
     valread = read(new_socket , buffer, 1024);
     printf("%s",buffer);
     send(new_socket , hello , strlen(hello) , 0 ); 
 
 //while(1)
   //  { 
	//n++;
	
  //reading no.
  memset(buffer, 0, 1024);
           valread = read(new_socket , buffer, 1024);
	recv(new_socket, &n,sizeof(n),0);
            // sscanf(buffer,"%d",&n);
            //   if(strcmp(buffer,"exit") == 0)
		//	break;         
  //writing answer to buffer  
  for(i=0;i<2;i++){
	//printf("\n\t i: %d and compare : %d",i,strcmp((s[i].question), buffer));
	if(strcmp((s[i].item_id), buffer) == 0)
		break;
  }
  if(i==2){
	strcpy(buffer,"Try again");	
	strcat(buffer,"\n");
  }
  else{
	int dig1 = s[i].no_of_items_available[0] - '0';
	int dig2 = s[i].no_of_items_available[1] - '0';
	if(dig1 == 0 && dig2 == 0){
		
		printf("\n\t Answer >> %s ",s[i].no_of_items_available);
	  strcpy(buffer,"Item not available");
	  strcat(buffer,"\n");
	}
	else if(dig1 < (n/10)){
	printf("\n\t Answer >> %s ",s[i].no_of_items_available);
	  strcpy(buffer,"Item is not available in required quantities");
	  strcat(buffer,"\n");
	}
	else if(dig1 == (n/10) && dig2 < (n%10)){
	strcpy(buffer,"Item is not available in required quantities");
  	strcat(buffer,"\n");
	}
	else{
		if(dig1 > 0)
		{
			dig1 = dig1 - n/10;
			dig2 = dig2 - n%10;
			s[i].no_of_items_available[0] = dig1 + '0';
			s[i].no_of_items_available[1] = dig2 + '0';
		}
		else
		{
			dig2 = dig2 - n%10;
			s[i].no_of_items_available[1] = dig2 + '0';
		}

		printf("\n\t Answer >> %s ",s[i].no_of_items_available);
	  strcpy(buffer,"Purchase Successful");
	  strcat(buffer,"\n");
	}
  }
      send(new_socket , buffer , strlen(buffer) , 0 );
      printf("%s\n",buffer);

   //  }
     printf("\n");

     return 0;
}
