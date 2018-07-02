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
#include"RawEthernetSocket.h"

struct RawSocket* new_RawSocket(char *interface){
    struct RawSocket* rawsocket = (struct RawSocket*)malloc(sizeof(struct RawSocket));
    if((rawsocket->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0){
        perror("socket");
        exit(0);
    };
    rawsocket->bind_rawsocket = bind_RawSocket;
    rawsocket->recv_rawsocket = recv_RawSocket;
    rawsocket->close_rawsocket = close_RawSocket;
    memset(rawsocket->interface,0x0,sizeof(rawsocket->interface));
    strcpy(rawsocket->interface, interface);
    return rawsocket;
}

void close_RawSocket(struct RawSocket* pthis){
    close(pthis->socket);
    free(pthis);
    return;
}

void bind_RawSocket(struct RawSocket* pthis){
    struct sockaddr_ll sockaddr;
    memset(&sockaddr, 0x0, sizeof(sockaddr));
    sockaddr.sll_family = AF_PACKET;
    sockaddr.sll_protocol = htons(ETH_P_ALL);
    //if_nametoindexでinterface名から番号を取得。sll_ifindexに指定
    sockaddr.sll_ifindex = if_nametoindex(pthis->interface);
    if(bind(pthis->socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        perror("bind");
        exit(0);
    }
}


int recv_RawSocket(struct RawSocket* pthis){
    int recv_size;
    //バッファをクリアしてからrecvで受信
    memset(pthis->buf,0x0,sizeof(pthis->buf));
    recv_size = recv(pthis->socket, pthis->buf, sizeof(pthis->buf),0);
    if(recv_size < 0){
        perror("recv error");
    }
    return recv_size;
};

