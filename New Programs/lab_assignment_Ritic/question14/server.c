#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

#define N strlen(g)

char t[50],cs[50],g[]="10001000000100001";

void xor(){
    int a,e,c;
    for(c = 1;c < N; c++)
    cs[c] = (( cs[c] == g[c])?'0':'1');
}

void crc(){
	int a,e,c;
    for(e=0;e<N;e++)
        cs[e]=t[e];
    do{
	//printf("Here\n");
        if(cs[0]=='1')
            xor();
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1];
        cs[c]=t[e++];
    }while(e<=N);
}

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
	
	printf("Before");
	valread = read(new_socket, t, 28, 0);
	valread = read(new_socket, cs, 28, 0);
	printf("%s", t);
	int a = strlen(t),i;
	for(i = a;i<N;i++)
	{
		t[i] = cs[i-a];
	}
	crc();
	//printf("CRC done\n");
	int iscorrect,e;
	for(e=0;(e<N-1) && (cs[e]!='1');e++);
	if(e<N){
		printf("Correct\n");
		iscorrect = 1;
		send(new_socket, &iscorrect, sizeof(iscorrect), 0);
	}
	else{
		printf("Incorrect\n");
		iscorrect = 0;
		send(new_socket, &iscorrect, sizeof(iscorrect), 0);
	}
	
}
