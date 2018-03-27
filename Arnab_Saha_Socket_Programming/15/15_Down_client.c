#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int toInt(char *s){
	int i=0,ans=0;
	while(s[i]){
		int x=s[i]-'0';
		ans=ans*10+x;
		i++;
	}
	return ans;
}
int main(int argc,char **argv){
	int port=toInt(argv[2]);
	int sock;
	struct sockaddr_in server;
	//create socket
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1){
		printf("Could not create socket\n");
	}
	puts("Socket created\n");
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	
	//connect to remote server
	if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0){
		perror("Connect failed. Error\n");
		return 1;
	}
	puts("Connected\n");
	if(strcmp(argv[3],"get")==0){
		FILE *fp=fopen(argv[4],"r+");
		while(1){
			int a=fgetc(fp);
			if(a==EOF)break;
			if(send(sock,&a,sizeof(int),0)<0){
				puts("Send failed\n");
				fclose(fp);
				return 1;
			}
		}
		fclose(fp);
	}else{
		FILE *fp=fopen(argv[4],"w+");
		int a;
		while(recv(sock,&a,sizeof(int),0)>=0){
			fputc(a,fp);
		}
		fclose(fp);
	}
	/**
	int n;
	printf("Enter n:");
	scanf("%d",&n);
	if(send(sock,&n,sizeof(int),0)<0){
		puts("Send failed\n");
		return 1;
	}
	int N=n+1;
	int F[N];
	if(recv(sock,&F,N*sizeof(int),0)<0){
		puts("Recv failed\n");
		return 1;
	}
	for(int i=0;i<N;i++){
		printf("F%d = %d\n",i,F[i]);
	}
	**/
	//close(sock);
	return 0;
}
