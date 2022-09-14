#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#define MAX 1024
struct sockaddr_in servaddr, cliaddr;
int len, n, port = 5566;

// function to repeatedly accept input
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        bzero(buff, MAX);
        n = recvfrom(sockfd, buff, MAX, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        printf("Client : %sEnter message to Client:", buff);
        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (struct sockaddr *)&cliaddr, len);
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}
// main fn
int main()
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    bzero(&cliaddr, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        exit(0);
    }
    len = sizeof(cliaddr); // len is value/result
    func(sockfd);
    return 0;
}