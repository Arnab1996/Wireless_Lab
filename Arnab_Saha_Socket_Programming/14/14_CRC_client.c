#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

#define N strlen(g)
char t[28],cs[28],g[]="10001000000100001";

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	int n;
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}


	printf("Enter the message and checksum\n");
	scanf("%s",t);
	scanf("%s",cs);
	send(sock, t, sizeof(t), 0);
	send(sock, cs, sizeof(cs), 0);
	int iscorrect;
	valread = read(sock, &iscorrect, sizeof(iscorrect), 0);
	if(iscorrect)
	{
		printf("No Error detected\n");
	}
	else
	{
		printf("Error Detected\n");
	}


}
