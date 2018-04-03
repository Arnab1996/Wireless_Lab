#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

struct empl{
	int total,current,extra;
};

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int con;
    char *hello = "Hello from server";
      
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
    
    struct empl arr[10] = {{20,10,0},{20,1,0},{20,0,0},{20,20,3},{20,17,0},{20,20,2},{20,3,0},{20,9,0},{20,20,5},{20,19,0}};
    int eid,l,pos;
    valread = read( new_socket , &eid, sizeof(con));
	valread = read( new_socket , &l, sizeof(con));
    do{
		
		if(eid>=0&&eid<10)
		{
			if(arr[eid].total+arr[eid].extra-arr[eid].current>=l)
			{
				arr[eid].current += l;
				if(arr[eid].total<arr[eid].current)
				{
					arr[eid].extra -= arr[eid].current-arr[eid].total;
				}
				pos = 1;
				send(new_socket , &pos , sizeof(pos) , 0 );
				send(new_socket , &arr[eid] , sizeof(arr[eid]) , 0 );
			}
			else
			{
				pos = 0;
				send(new_socket , &pos , sizeof(pos) , 0 );
			}
		}
		valread = read( new_socket , &eid, sizeof(con));
		valread = read( new_socket , &l, sizeof(con));
    }while(eid>=0&&eid<10);
    return 0;
}
