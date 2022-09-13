#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAXLINE 1024
int sockfd;
int n, len;
struct sockaddr_in servaddr;
char buffer[MAXLINE];
// function to repeatedly accept input
void func(int fd)
{
    char buff[MAXLINE];
    for (;;)
    {
        bzero(buff, MAXLINE);
        n = recvfrom(fd, buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buff[n] = '\0';
        printf("Server : %s\n To Server:", buff);
        bzero(buff, MAXLINE);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        sendto(fd, buff, sizeof(buff), MSG_CONFIRM, (struct sockaddr *)&servaddr, sizeof(servaddr));
    }
}

// main function
int main()
{
    char *hello = "Hello from client";
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    sendto(sockfd, (char *)hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Hello message sent.\n");

    func(sockfd);

    close(sockfd);
    return 0;
}