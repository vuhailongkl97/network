#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


int main(int argc , char *argv[])
{
    int SRV_PORT = 0;
    char SERVER_IP[16];
    char buf[100] = {0};
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = 0, i;
    struct sockaddr_in addr, cli_addr;
    socklen_t addrlen;
    
    if ( argc < 3 )
    {
        fprintf(stderr, "<program> <ip> <port>");
        return -1; 
    }
    for (i = 0 ; i < argc ; i++)
        printf("argv[%d] : %s\t", i, argv[i]);

    printf("\n");
    SRV_PORT = atoi(argv[1]);
    strcpy(SERVER_IP, argv[2]);
    if ( -1 == fd)
    {
        fprintf(stderr, "create socket error\n");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port =htons(SRV_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    ret = bind(fd, (const  struct sockaddr *)&addr, sizeof(addr));

    if( -1 == ret)
    {
        perror("error bind\n");
        return -1 ;
    }

    int len = sizeof(cli_addr);
    int n  = recvfrom(fd, (char *)buf, 100, 0, (struct sockaddr *)&cli_addr, &len);

    printf("client : %s, len  %d\n", buf, len);
    bzero(buf, 100);
    strcpy(buf, "reply from server");
    n = sendto(fd, (const char *)buf, strlen(buf),0 , (struct sockaddr *)&cli_addr, sizeof(addr));

    if( n < 0)
    {
        fprintf(stderr,"%s:%d error : %s", __func__, __LINE__, strerror(errno));
    }
    printf("server send done %d\n", n);

    bzero(buf, sizeof(buf));
    recvfrom(fd, (char *)buf, 100, 0, (struct sockaddr *)&cli_addr, &len);
    printf("client : %s, len  %d\n", buf, len);

    close(fd);
    return 0;

}
