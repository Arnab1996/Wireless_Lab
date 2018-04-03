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
 int server_fd, new_socket, valread;
     struct sockaddr_in address;
     int opt = 1;
     int addrlen = sizeof(address);
     char buffer[1024] = {0};
     char buffer_2[1024] = {0};
     char temp[1024]={0};
     char *hello = "\nConnection_Established";
     int n=15,i=0;
     char *p = (char*) malloc(sizeof(char)*50);
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
 dict s[25]={ {"approach","move towards"},
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
   {"major","greater in scope or effect"}};
   
 //initial handshake
 
     new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen);
     valread = read(new_socket , buffer, 1024);
     printf("%s",buffer);
     send(new_socket , hello , strlen(hello) , 0 );
 
 while(1)
     {
  //reading no.
  memset(buffer, '\0', 1024);
  memset(buffer_2, '\0', 1024);
  valread = read(new_socket , buffer_2, 1024);
  //sscanf(buffer,"%d",&n);
  
    p = strtok(buffer_2, "|");
  strcpy(buffer,p);
  //printf("\nstrcmp : %d with buffer : %s", strcmp(buffer,"exit"),buffer);
  if(strcmp(buffer,"exit")==0)
    break;                      
  for(i=0;i<n;i++){
    if(strcmp(s[i].word,buffer)==0)
        break;
  }
 
  //strcpy(buffer,"\n");
  if(i==n){
   p = strtok(NULL, "|");
   strcpy(s[n].word,buffer);
   strcpy(s[n++].meaning,p);
   strcpy(buffer,"Record not found !! New Record added successfully !!");
   
  }else
  {
   strcpy(buffer,s[i].meaning);
   strcat(buffer,"\n");
   printf("\n\t Received word >> %s and meaning >> %s", s[i].word, s[i].meaning);
  }
      send(new_socket , buffer , strlen(buffer) , 0 );
      //printf("%d\n",n);
     }
     printf("\n");
     return 0;
}
