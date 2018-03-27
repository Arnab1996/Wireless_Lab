// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

struct record
{
	int rollNo;
	char name[50];
	int age;
	float cgpa;
	int currYear;
}; 
struct record _blank = {0, "", 0, 0.0, 0};

struct record database[10] = {
						{1, "abc", 20, 7.0, 4},
						{2, "def", 20, 9.1, 4},
						{3, "t", 19, 8.4, 4},
						{4, "aiugh", 21, 6.9, 4},
						{5, "qwert", 20, 7.8, 4},
						{6, "akf", 22, 8.8, 4},
						{7, "aghr", 21, 9.6, 4},
						{8, "oyitoe", 20, 8.1, 4},
						{9, "ruoa", 19, 7.8, 4},
						{10, "ipyi", 21, 6.7, 4}
					};

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
    do{
    valread = read( new_socket , &input, sizeof(input),0);
    printf("\nInput recvd\n");
    int ind = 0, found = 0;
    for (ind = 0; ind < 10; ++ind)
    {
		if (input == database[ind].rollNo)
		{
			send(new_socket, &database[ind], sizeof(struct record), 0);
			found = 1;
			break;
		}
	}
    if (!found)
		send(new_socket , &_blank , sizeof(struct record) , 0 );
	} while (input > 0);
    return 0;
}
