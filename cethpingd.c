#include<stdio.h>
#include<stdlib.h>
#include<linux/if_ether.h>
#include"RawEthernetSocket.h"
#include"ethernet.h"

void start_daemon(char *interface){
    //rawソケット作成(receiverのインターフェース名を指定)
    struct RawSocket* rawsocket = new_RawSocket(interface);
    int len;
    //bindでインターフェースと紐付け
    rawsocket->bind_rawsocket(rawsocket);
    while(1){
        int len = rawsocket->recv_rawsocket(rawsocket);
        struct ethhdr_frame *data = (struct ethhdr_frame*)(rawsocket->buf);
        fflush(stdout);
        //受信したパケットの内容を表示
        if(len > 0){
            printf("src: ");
            print_macaddr(data->h_source);
            printf(", ");
            printf("dst: ");
            print_macaddr(data->h_dest);
            printf(", ");
            printf("type: ");
            printf("%02x", (uint16_t)data->h_proto);
            printf(", ");
            printf("payload: ");
            printf("%s", data->payload);
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
