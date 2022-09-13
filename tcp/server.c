#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define MAX 100

void func(int connfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}
int main()
{
    char *ip = "127.0.0.1";
    int port = 5566;
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cliaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = port;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    printf("binded portn %d\n", port);
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    func(connfd);
    close(sockfd);
}