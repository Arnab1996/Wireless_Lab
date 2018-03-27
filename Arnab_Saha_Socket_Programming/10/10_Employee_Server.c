// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

struct emp
{
	int empId, totalLeave, currLeave, extraLeave;
};

struct emp database[4] = {
				{1, 20, 10, 5},
				{2, 20, 17, 2},
				{3, 20, 18, 5},
				{4, 20, 10, 0}
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
    
    int input[2];
    do{
    	valread = read( new_socket , input, sizeof(input));
    	int ind, found = 0;
    	for (ind = 0; ind < 4; ++ind)
    	{
    		if (input[0] == database[ind].empId)
    		{
    			if (database[ind].extraLeave > input[1])
    			{
    				database[ind].extraLeave -= input[1];
    				send(new_socket, "\nLeave granted\n", 16, 0);
    			}
    			else
    			if (database[ind].currLeave + database[ind].extraLeave >= input[1])
    			{
    				input[1] -= database[ind].extraLeave;
    				database[ind].extraLeave = 0;
    				database[ind].currLeave -= input[1];
    				send(new_socket, "\nLeave granted\n", 16, 0);
    			}
    			else
    				send(new_socket, "\nYou don\'t have enough leave\n", 30, 0);
    			found = 1;
    			break;
    		}
    	}
    	if (!found)
    		send(new_socket , "\nRecord not found\n" , 19 , 0 );
    } while (input[0] > 0);
    return 0;
}
