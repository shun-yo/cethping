#include<stdio.h>
#include<stdlib.h>
#include<linux/if_ether.h>
#include"rawethernetsocketserver.h"
#include"ethernet.h"

void start_daemon(char *interface){
    struct RawSocket* rawsocket = new_RawSocket(interface);
    int len;
    rawsocket->server_bind(rawsocket);
    while(1){
        int len = rawsocket->get_request(rawsocket);
        struct cethhdr *data = (struct cethhdr*)(rawsocket->buf);
        fflush(stdout);
        if(len > 0){
            printf("src: ");
            print_mac_address(data->h_source);
            printf(", ");
            printf("dst: ");
            print_mac_address(data->h_dest);
            printf(", ");
            printf("type: ");
            printf("%02x", (uint16_t)data->h_proto);
            printf("\n");
        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("usage: %s <interface>", argv[0]);
        exit(0);
    }
    char *if_name = argv[1];
    start_daemon(if_name);
    return 0;
}
