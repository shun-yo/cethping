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

#include"rawethernetsocketserver.h"
#include"ethernet.h"

void ethping(char *destination, char* interface){
    struct RawSocket* rawsocket = new_RawSocket(interface);
    unsigned char buf[32];
    struct ethhdr_frame* eth_packet = (struct ethhdr_frame*)buf;
    memset(buf, 0x0, sizeof(eth_packet));
    set_macaddr_from_string(destination, eth_packet->h_dest);
    set_macaddr_from_ifname(interface, eth_packet->h_source);
    eth_packet->h_proto = 0x88b5;
    char* data = "Hi";
    memcpy(eth_packet->payload, data, sizeof(data)); 

    rawsocket->bind_rawsocket(rawsocket);
    int send_size = send(rawsocket->socket, &buf, sizeof(buf), 0);
    printf("%dbyte send.\n", send_size);


    rawsocket->close_rawsocket(rawsocket);
}


int main(int argc, char *argv[]){
    if(argc != 3){
        printf("usage: %s <destination> <interface>", argv[0]);
        exit(0);
    }

    char *destination = argv[1];
    char *if_name = argv[2];
    ethping(destination, if_name);

    return 0;
}
