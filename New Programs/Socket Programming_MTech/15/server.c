/*FTP server*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*for getting file size using stat()*/
#include<sys/stat.h>
/*for sendfile()*/
#include<sys/sendfile.h>
/*for O_RDONLY*/
#include<fcntl.h>

int main(int argc,char *argv[])
{
  struct sockaddr_in server, client;
  struct stat obj;
  int sock1, sock2;
  char buf[100], command[5], filename[20];
  int k, i, size, c;
  int filehandle;
  int sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
    {
        printf("cannot create socket!\n");
        return 0;
    }

    
    memset(&server, 0, sizeof(server));  
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  
    server.sin_port = htons(7777);  
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0)
    {
        printf("cannot bind socket!\n");
        close(sock_desc);  
        return 0;
    }

    if (listen(sock_desc, 20) != 0)
    {
        printf("cannot listen on socket!\n");
        close(sock_desc);  
        return 0;
    }

     
    memset(&client, 0, sizeof(client));  
    socklen_t len = sizeof(client); 
    sock2 = accept(sock_desc, (struct sockaddr*)&client, &len);  
    if (sock2 == -1)
    {
        printf("cannot accept client!\n");
        close(sock_desc);  
        return 0;
    }
  i = 1;
  
      recv(sock2, buf, 100, 0);
      sscanf(buf, "%s", command);
     if(!strcmp(command,"get"))
	{
	  sscanf(buf, "%s%s", filename, filename);
	  stat(filename, &obj);
	  filehandle = open(filename, O_RDONLY);
	  size = obj.st_size;
	  if(filehandle == -1)
	      size = 0;
	  send(sock2, &size, sizeof(int), 0);
	  if(size)
	  sendfile(sock2, filehandle, NULL, size);
      
	}
     
     
  return 0;
}
