#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

static const unsigned short portno = 5000;
static const unsigned int BUFFER_SIZE = 1024;


int main(int regc, char* argv[])
{
    printf("Starting server pid=%d\n", getpid());

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("[ERROR] open socket failed");
        return errno;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // use IP
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = portno; // listen port

    // bind address to socket
    if (0 != bind(sockfd, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)))
    {
        perror("[ERROR] binding socket to address failed");
        return errno;
    }

    // if (0 != listen(sockfd, 0))
    // {
    //     perror("[ERROR] listen failed");
    //     return errno;
    // }

    printf("Waiting for UDP messages on %s:%d...\n", inet_ntoa(serv_addr.sin_addr), portno);

    unsigned int bytes_read = 0;
    char buffer[BUFFER_SIZE];
    do 
    {
        bytes_read = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);

        printf("Read %d bytes\n", bytes_read);
        if (0 < bytes_read)
        {
            buffer[bytes_read] = '\0';
            printf("[MESSAGE] \"%s\"\n", buffer);
        }

    } while (bytes_read >= 0);

    return errno;
}