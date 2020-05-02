#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno;
int
main(void)
{
    struct ifaddrs *addr_list;
    struct ifaddrs *addr_head;

    if (getifaddrs(&addr_list) == -1)
    {
        fprintf(stderr, "%s:%d err %s\n", __func__, __LINE__, strerror(errno)); 
        return -1;
    }
    addr_head = addr_list;

    while (addr_head)
    {
        int family = addr_head->ifa_addr->sa_family;
        
        if (family == AF_INET  || family == AF_INET6)
        {
            printf("interface name %s\t", addr_head->ifa_name);
            printf("family %s\t", family == AF_INET ? "IPv4" : "IPv6");
            char ap[100];
            const int family_size = ( family == AF_INET ? sizeof(struct sockaddr_in) \
                    : sizeof(struct sockaddr_in6));

            getnameinfo(addr_head->ifa_addr, family_size, ap , sizeof(ap), \
                    0, 0, NI_NUMERICHOST);

            printf("\t%s\n", ap);
        }
        addr_head = addr_head->ifa_next;
    }
    freeifaddrs(addr_list);
    return 0;
}

