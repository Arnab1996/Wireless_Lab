#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 2127

typedef struct dictionary
{
 char word[50];
 char meaning[50];
}dict;
 

int main(int argc, char const *argv[])
{
     struct sockaddr_in address;
     int sock = 0, valread;
     struct sockaddr_in serv_addr;
     char buffer[1024] = "\nRequest_from_Client ";
     char in[1024];
     int m,n,i;
     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
     {
         printf("\nSocket creation error ");
         return -1;
     }
     memset(&serv_addr, '0', sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(PORT);
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
     
     dict s[20]={ {"approach","move towards"},
   {"assume","take to be the case or to be true"},
   {"benefit","something that aids or promotes well-being"},
   {"create","bring into existence"},
   {"established","brought about or set up or accepted"},
   {"estimate","judge tentatively"},
   {"export","sell or transfer abroad"},
   {"financial","involving fiscal matters"},
   {"function","what something is used for"},
   {"identified","having the identity known or established"},
   {"involved","connected by participation or association or use"},
   {"issue","some situation or event that is thought about"},
   {"labour","productive work"},
   {"legislation","the act of making or enacting laws"},
   {"major","greater in scope or effect"},
   {"occur","come to pass"},
   {"period","an amount of time"},
   {"required","necessary by rule"},
   {"research","the act of making or enacting laws"},
   {"significant","rich in implication"}};
    

//initial handshake
send(sock , buffer , strlen(buffer) , 0 );
     valread = read( sock , buffer, 1024);
     printf("%s",buffer );
 printf("\nEnter the word (type exit to exit): ");
 n=0;


 do
 {
  gets(buffer);
  if(strcmp(buffer,"exit")==0)
    break;
  for(i=0;i<20;i++){
    if(strcmp(s[i].word,buffer)==0)
        break;
  }
  strcat(buffer,"|");
  strcat(buffer,s[i].meaning);
  send(sock , buffer , strlen(buffer) , 0 );
  printf("\nRequest sent");
  
 
 // sprintf(buffer,"%d",n);
 
 
 // memset(buffer, '\0', 1024);   */      
  memset(buffer, '\0', 1024);
  valread = read(sock , buffer, 1024);
     printf("\nReply from server: \n%s",buffer);
  printf("\nNext word (type exit to exit): ");
 
 }while(n!=-1);
     printf("\n");
     return 1;
}


