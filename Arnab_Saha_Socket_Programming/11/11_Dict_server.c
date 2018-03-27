#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

char word[20][15], meaning[100][15];
int dictSize = 0;

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int con;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
	int count = 5;	//20;
    char w[20], m[100];
    valread = read(new_socket, w, sizeof(w), 0);
    int i, found = 0;
	char empty[] = "";
	for (i = 0; i < dictSize; ++i)
	{
		if (!strcmpi(w, word[i]))
		{
			send(new_socket, meaning[i], strlen(meaning[i]), 0);
			found = 1;
			break;
		}
	}
	
	if (!found)
	{
		send(new_socket, empty, strlen(empty), 0);
		read(new_socket, m, 100);
		strcpy(word[dictSize], w);
		strcpy(meaning[dictSize], m);
		++dictSize;
	}

    return 0;
}
