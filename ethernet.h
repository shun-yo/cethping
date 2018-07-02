#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<net/if.h>
#include<netpacket/packet.h>
#include<sys/ioctl.h>

struct ethhdr_frame {
    unsigned char	h_dest[6];	/* destination eth addr	*/
    unsigned char	h_source[6];	/* source ether addr	*/
    __be16		h_proto;		/* packet type ID field	*/
    char payload[];
};

void set_macaddr_from_string(char *str, char *raw);

void set_macaddr_from_ifname(char *interface, char *raw);

void print_macaddr(char *raw);
