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

    memset(buf, 0x0, sizeof(buf));

    mac_raw(destination, ((struct cethhdr*)buf)->h_dest);

    get_hw_addr(interface, ((struct cethhdr*)buf)->h_source);

    ((struct cethhdr*)buf)->h_proto = 0xb588;

    rawsocket->server_bind(rawsocket);

    int send_size = send(rawsocket->socket, &buf, sizeof(buf), 0);

    printf("%d send\n", send_size);
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
