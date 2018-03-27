#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
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
    char details[10][50];
    char ch = 'y';
    int n,i;
    char word[100],c;
    int num;
    while(ch == 'y'||ch == 'Y')
    {
        printf("Enter the word and a number\n");
        scanf("%s%d",word,&num);
        send(sock, &word, sizeof(word), 0);
        send(sock, &num, sizeof(num), 0);
        printf("Data sent ot server\n");
        valread = read(sock, &c, sizeof(c), 0);
        if(valread<0)
        {
            printf("Error\n");
        }
        else
        {
            printf("Character : %c satisfies the given conditions\n",c);
        }
        while ((getchar()) != '\n');
        printf("Enter y/Y to continue\n");
        scanf("%c",&ch);
    }
    strcpy(word, "Terminate");
    send(sock, &word, sizeof(word), 0);
    return 0;
}
