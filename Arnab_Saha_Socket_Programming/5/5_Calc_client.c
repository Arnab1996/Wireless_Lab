#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
  
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
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
    printf("Enter the value of n and m\n");
    float a[2];
    scanf("%f%f",&a[0],&a[1]);
    send(sock , &a , sizeof(a) , 0 );
    float ans[4],i;
    valread = read(sock, &ans, sizeof(ans), 0);
    if(valread>=0)
    {
        printf("%f + %f = %f\n",a[0],a[1],ans[0]);
        printf("%f - %f = %f\n",a[0],a[1],ans[1]);
        printf("%f * %f = %f\n",a[0],a[1],ans[2]);
        printf("%f / %f = %f\n",a[0],a[1],ans[3]);
    }
    else
    {
        printf("Error : Value not received\n");
    }
    
    return 0;
}
