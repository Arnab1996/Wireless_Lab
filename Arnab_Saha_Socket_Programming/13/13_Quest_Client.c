#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc,char **argv){
	int sock,i;
	struct sockaddr_in server;
	//create socket
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1){
		printf("Could not create socket\n");
	}
	puts("Socket created\n");
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8880);
	
	//connect to remote server
	if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0){
		perror("Connect failed. Error\n");
		return 1;
	}
	puts("Connected\n");
	int count = 0;
	while(1){
		if(count == 3)
		{
			printf("3 questions completed\nTerminating...\n");
			return 0;
		}
		int disconnect=0;
		printf("Disconnect 0/1?");
		scanf("%d",&disconnect);
		if(disconnect)
		{
			return 0;
		}
		int n;
		printf("Enter n to get its prime factors:");
		scanf("%d",&n);
		count++;
		if(send(sock,&n,sizeof(int),0)<0){
			puts("Send failed\n");
			continue;
		}
		int F[1000];
		int N=0;
		if(recv(sock,&N,sizeof(int),0)<0){
			puts("Recv failed\n");
			continue;
		}
		if(recv(sock,F,N*sizeof(int),0)<0){
			puts("Recv failed\n");
			continue;
		}
		printf("There are %d prime factors of %d:\n",N,n);
		for(i=0;i<N;i++){
			printf("%d ",F[i]);
		}
		printf("\n");
	}
	//close(sock);
	return 0;
}
