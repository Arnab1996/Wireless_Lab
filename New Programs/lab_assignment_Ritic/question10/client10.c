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
    int eid,l;
    printf("Enter employee id\n");
	scanf("%d",&eid);
    do{
    	printf("Enter number of leaves\n");
		scanf("%d",&l);
		send(sock , &eid , sizeof(eid) , 0 );
		send(sock , &l , sizeof(l) , 0 );
		int pos;
		valread = read(sock, &pos, sizeof(pos), 0);
		if(valread>=0)
		{
		    if(pos == 1)
		    {
		    	struct empl temp;
		    	valread = read(sock, &temp, sizeof(temp), 0);
		    	printf("Total Leaves = %d\n",temp.total);
		    	printf("Current no. of Leaves = %d\n",temp.current);
		    	printf("Extra Leaves = %d\n",temp.extra);
		    }
		    else
		    {
		    	printf("%d no. of leaves not possible\n",l);
		    }
		}
		else
		{
		    printf("Error : Value not received\n");
		}
		printf("Enter employee id\n");
		scanf("%d",&eid);
		
    }while(eid>=0&&eid<10);
    return 0;
}
