#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

static const char* SERVER_IP_ADDRESS = "127.0.0.1";
static const unsigned short portno = 5000;
static const unsigned int BUFFER_SIZE = 1024;


int main(int argc, char* argv[])
{
    char message[BUFFER_SIZE];
    if (argc > 1)
    {
        strncpy(message, argv[1], BUFFER_SIZE);
    }
    else
    {
        strcpy(message, "Hello everyone!");
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("[ERROR] open socket failed");
        return errno;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = portno;
    if (inet_pton(AF_INET, SERVER_IP_ADDRESS, &(server_addr.sin_addr)) <= 0)
    {
        perror("[ERROR] converting server IP address");
        return errno;
    }

    
    if (sendto(sockfd, message, strlen(message), 0, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("[ERROR] sending message to server");
        return errno;
    }

    printf("Message sent to the server: %s\n", message);

    close(sockfd);

    return EXIT_SUCCESS;
}
