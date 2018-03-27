// Client side C/C++ program to demonstrate Socket programming
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
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
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
    int input;
    do{
    scanf("%d", &input);
    send(sock , &input , sizeof(input) , 0 );
    struct record r;
    valread = read( sock , &r, sizeof(struct record));
	if (r.rollNo != 0)
	{
		printf("\nRoll No = %d\nName = ", r.rollNo);
		puts(r.name);
		printf("Age = %d\nCGPA = %f\nCurrent year = %d\n\n", r.age, r.cgpa, r.currYear);
	}
	else
		printf("\nNo record found with given roll number\n");
	}while (input > 0);
    return 0;
}
