/*FTP Client*/
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
  struct sockaddr_in server;
  struct stat obj;
  int sock;
  int choice;
  char buf[100], command[5], filename[20], *f;
  int k, size, status, PORT;
  int filehandle;
  sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock == -1)
    {
        printf("cannot create socket!\n");
        return 0;
    }

    struct sockaddr_in client;  
    memset(&client, 0, sizeof(client));
	sscanf(argv[2], "%d", &PORT);  
    client.sin_family = AF_INET;  
    client.sin_addr.s_addr = inet_addr(argv[1]);  
    client.sin_port = htons(PORT);   //7777

    if (connect(sock, (struct sockaddr*)&client, sizeof(client)) != 0)
    {
        printf("cannot connect to server!\n");
        close(sock);
    }
	int i = 1;
   strcpy(filename,argv[4]);
	  strcpy(buf, argv[3]);
	strcat(buf, " ");
	  
	  filehandle = open(filename, O_RDONLY);
          if(filehandle == -1)
            {
              printf("No such file on the local directory\n\n");
              //break;
            }
	else{
          strcpy(buf, argv[3]);
	strcat(buf, " ");
	  strcat(buf, filename);
	  send(sock, buf, 100, 0);
	  stat(filename, &obj);
	  size = obj.st_size;
	  send(sock, &size, sizeof(int), 0);
	  sendfile(sock, filehandle, NULL, size);
	  recv(sock, &status, sizeof(int), 0);
	  if(status)
	    printf("File stored successfully\n");
	  else
	    printf("File failed to be stored to remote machine\n");
	  }
	
    
}
