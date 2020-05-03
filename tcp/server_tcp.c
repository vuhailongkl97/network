#include <stdio.h>
#include <time.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <errno.h>

int main(void)
{
    time_t timer;
    int fd = 0;
    struct sockaddr_in addr;

    time(&timer);
    char *time_msg = ctime(&timer);
    printf("local time is: %s\n", ctime(&timer));

    char  address_buffer[100];
    struct sockaddr_in6 server ;
    server.sin6_family = AF_INET6;
    server.sin6_port =   htons(8080);
    server.sin6_addr = in6addr_any;

    fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (fd < 0)
    {
        fprintf(stderr, "%s:%d error %s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }

    int true = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int)) < 0)
    {
        fprintf(stderr, "%s:%d setsockopt error %s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }

    int option = 0;
    if(setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&option, sizeof(option)) < 0)
    {
        fprintf(stderr, "%s:%d setsockopt error %s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }


    if(bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        fprintf(stderr, "%s:%d error %s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }

    if (listen(fd, 10) < 0)
    {
        fprintf(stderr, "%s:%d listen() error %s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }

    printf("Waiting for connection ...\n");

    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);

    int new_fd = accept(fd, (struct sockaddr*)&client_address, &client_len);

    if ( new_fd < 0)
    {
        fprintf(stderr, "%s:%d accept error %s\n", __func__, __LINE__, strerror(errno));
        return -1;
    }

    puts("someone connected ..");
    getnameinfo((struct sockaddr*)&client_address, client_len , address_buffer, \
            sizeof(address_buffer), 0, 0 , NI_NUMERICHOST);

    printf("%s\n", address_buffer);

    char request[1024];
    int bytes_received = recv(new_fd, request, 1024, 0);
    printf("Recv %d bytes. request %.*s\n", bytes_received, bytes_received, request);
    int bytes_send;
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n\r\n";
        "Local time is : ";
    bytes_send = send(new_fd, response, strlen(response), 0);
    printf("Sent response %d of %ld bytes\n", bytes_send , strlen(time_msg));

    bytes_send = send(new_fd, time_msg, strlen(time_msg), 0);
    printf("Sent %d of %ld bytes\n", bytes_send , strlen(time_msg));

    close(new_fd);
    close(fd);

    return 0;
}
