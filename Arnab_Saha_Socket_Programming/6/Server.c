// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int starPattern(int size, char *pattern)
{
	int i, j, p = 0;
	for (i = size; i > 0; --i)
	{
		// space loop
		for (j = 1; j <= size - i; ++j)
			pattern[p++] = ' ';
			
		// star loop
		for (j = 1; j < i; ++j)
		{
			pattern[p++] = '*';
			pattern[p++] = ' ';
		}
		pattern[p++] = '*';
			
		pattern[p++] = '\n';
	}
	pattern[p++] = '\0';
	return p;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
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
    int input;
    valread = read( new_socket , &input, sizeof(input));
    printf("\nReceived number = %d\n", input );
    
    char *pattern = malloc(2*input*input);	// an estimated loose upper bound of size
    int pSize = starPattern(input, pattern);
    //printf("\nResult = %d", pattern);
    puts(pattern);
    send(new_socket, pattern, pSize+1, 0 );
    printf("\nOutput sent\n");
    return 0;
}
