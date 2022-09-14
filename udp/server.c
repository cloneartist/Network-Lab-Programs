#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAXLINE 1024
struct sockaddr_in servaddr, cliaddr;
int len, n;

// function to repeatedly accept input
void func(int fd)
{
    char buff[MAXLINE];
    int n;
    for (;;)
    {
        bzero(buff, MAXLINE);
        n = recvfrom(fd, buff, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        // buff[n] = '\0';
        printf("Client : %s\nTo Client:", buff);
        bzero(buff, MAXLINE);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        sendto(fd, buff, sizeof(buff), MSG_CONFIRM, (struct sockaddr *)&cliaddr, len);
    }
}
// main fn
int main()
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    char *hello = "Hello from server";
    len = sizeof(cliaddr); // len is value/result
    sendto(sockfd, (char *)hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *)&cliaddr, len);
    func(sockfd);
    printf("Hello message sent.\n");
    return 0;
}