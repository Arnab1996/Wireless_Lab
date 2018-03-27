#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

char fun(char *word, int num)
{
    int arr[26] = {0};
    int i,j,k,ln = strlen(word);
    for(i = 0;i<ln;i++)
    {
        if(word[i]>='A'&&word[i]<='Z')
        {
            word[i] = word[i]-'A'+'a';
        }
        j = word[i]-'a';
        arr[j]++;
    }
    j = 0;
    k = 0;
    for(i = 0;i<26;i++)
    {
        if(j<arr[i])
        {
            k = i;
            j = arr[i];
        }
        if(arr[i] == num)
        {
            return i+'a';
        }
    }
    return k+'a';
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
    int num;
    char word[100];
    char ch;
    valread = read(new_socket, &word, sizeof(word), 0);
    valread = read(new_socket, &num, sizeof(num), 0);
    printf("Data received from client %s, %d\n",word,num);
    while(strcmp(word,"Terminate") != 0)
    {
        ch = fun(word,num);
        printf("%c\n",ch);
        send(new_socket, &ch, sizeof(ch), 0);
        valread = read(new_socket, &word, sizeof(word), 0);
        valread = read(new_socket, &num, sizeof(num), 0);
    }
    return 0;
}
