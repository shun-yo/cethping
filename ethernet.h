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

struct cethhdr {
    unsigned char	h_dest[6];	/* destination eth addr	*/
    unsigned char	h_source[6];	/* source ether addr	*/
    uint16_t h_proto;
    //__be16		h_proto;		/* packet type ID field	*/
    char rest[];
};

void mac_raw(char *str, char *raw);

void get_hw_addr(char *interface, char *raw);

void print_mac_address(char *raw);
