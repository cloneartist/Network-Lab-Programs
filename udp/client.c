#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define MAX 1024
int sockfd, port = 5566;
int n, len;
struct sockaddr_in servaddr;
// function to repeatedly accept input
void func(int sockfd)
{
    char buff[MAX];
    for (;;)
    {
        bzero(buff, MAX);
        n = 0;
        printf("Enter message to server:");
        while ((buff[n++] = getchar()) != '\n')
            ;
        sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (struct sockaddr *)&servaddr, sizeof(servaddr));
        bzero(buff, MAX);
        n = recvfrom(sockfd, buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        printf("From Server : %s", buff);
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Client Exit...\n");
            break;
        }
    }
}

// main function
int main()
{
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    func(sockfd);
    close(sockfd);
    return 0;
}