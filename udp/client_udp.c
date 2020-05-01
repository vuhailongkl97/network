#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(int argc , char *argv[])
{
    int SRV_PORT = 0;
    char SERVER_IP[16];
    char *buf = "abc";
    char buf2[100] ={0};
    int fd , i , len , ret;
    struct sockaddr_in addr;
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

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if ( -1 == fd)
    {
        perror("create socket error");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port =htons(SRV_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    ret = sendto(fd, (const void*)buf, strlen(buf), 0, (const struct sockaddr*)&addr, sizeof(addr));

    if( -1 == ret)
    {
        perror("sento error :");
        return -1 ;
    }
    else if ( ret == strlen(buf))
    {
        printf("send successfully\n"); 
    }
    len = sizeof(addr);
    recvfrom(fd, (char *)buf2, 100, 0, (struct sockaddr *)&addr,
            &len);
    printf("SERVER : %s\n", buf2);
    strncpy(buf2, "reply from cli", sizeof(buf2));
    ret = sendto(fd, (const void*)buf2, strlen(buf2), 0, (const struct sockaddr*)&addr, sizeof(addr));

    if( -1 == ret)
    {
        perror("sento error :");
        return -1 ;
    }
    else if ( ret == strlen(buf))
    {
        printf("send successfully\n"); 
    }
    close(fd);

    return 0;

}
