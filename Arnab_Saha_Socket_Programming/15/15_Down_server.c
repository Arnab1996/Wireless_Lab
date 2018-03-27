#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc,char **argv){
	int socket_desc,client_sock,c,read_size;
	struct sockaddr_in server,client;
	
	//create socket
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc==-1){
		printf("Could not create socket");
	}
	puts("Socket created\n");
	
	//prepare the sockaddr_in structure
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8880);
	
	//bind
	if(bind(socket_desc,(struct sockaddr *)&server,sizeof(server))<0){
		perror("Bind failed. Error\n");
		return 1;
	}
	puts("Bind done\n");
	
	//listen
	listen(socket_desc,3);
	
	//accept an incoming connection
	puts("Waiting for incoming connections..");
	c=sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);
	if(client_sock<0){
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted\n");
	FILE *fp=fopen("lol","w");
	//receive a msg from client
	int message;
	while((read_size=recv(client_sock,&message,sizeof(int),0))>0){
		printf("%c",message);
		fputc(message,fp);
	}
	if(read_size==0){
		puts("Client disconnected\n");
	}else if(read_size==-1){
		perror("recv failed\n");
	}
	fclose(fp);
	return 0;
	
}
