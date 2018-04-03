#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
//#define PORT 2127
int main(int argc, char const *argv[])
{
     struct sockaddr_in address;
     int sock = 0, valread;
     struct sockaddr_in serv_addr;
     char buffer[1024] = "\nRequest_from_Client ";
     char item_id[1024];
     int m=0,n,PORT;
	printf("%s %s %s %s",argv[1],argv[2],argv[3],argv[4]);
     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     {
         printf("\nSocket creation error ");
         return -1;
     }
     memset(&serv_addr, '0', sizeof(serv_addr));
	sscanf(argv[2], "%d", &PORT);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(PORT);
     serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
 connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
     send(sock , buffer , strlen(buffer) , 0 );
     valread = read( sock , buffer, 1024);
     printf("%s",buffer );
    strcpy(item_id,argv[3]);
	sscanf(argv[4], "%d", &n);
/* printf("\nEnter the item_id and quantity: "); 
 scanf("%s %d",item_id,&n);
 send(sock , item_id , strlen(item_id) , 0 );
send(sock , &n , sizeof(n) , 0 );//send to server*/
    
// n=0; 
// do
 //{
	
memset(buffer, '\0', 1024);
  //scanf("%s %d",item_id,&n);
 send(sock , item_id , strlen(item_id) , 0 );
send(sock , &n , sizeof(n) , 0 );//send to server
  printf("\nRequest sent");
  //if(strcmp(item_id,"exit") == 0)
	//		break;    
           
  valread = read(sock , buffer, 1024);
     printf("\nReply from server: \n%s",buffer);
 // printf("\nEnter the item_id and quantity (enter exit to end): ");
  
 //}while(n!=-1);
     printf("\n");
     return 1;
}


