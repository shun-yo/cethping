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
    //rawソケット作成。インターフェース名を指定
    struct RawSocket* rawsocket = new_RawSocket(interface);

    //パケットのデータ用のバッファ
    unsigned char buf[32];
    //パケットを定義。イーサネットフレームのフォーマットに合わせてキャスト
    struct ethhdr_frame* eth_packet = (struct ethhdr_frame*)buf;
    //sender, receiverのMACアドレスを格納。Protocol typeは任意で0x88b5を指定
    //senderのMACアドレスは指定したインターフェース名を基に取得
    memset(buf, 0x0, sizeof(eth_packet));
    set_macaddr_from_string(destination, eth_packet->h_dest);
    set_macaddr_from_ifname(interface, eth_packet->h_source);
    eth_packet->h_proto = 0x88b5;
    //ペイロードには文字列"Hi"を設定
    char* data = "Hi";
    memcpy(eth_packet->payload, data, sizeof(data)); 

    //指定したインターフェースでソケットをbind
    rawsocket->bind_rawsocket(rawsocket);
    int send_size = send(rawsocket->socket, &buf, sizeof(buf), 0);
    printf("%dbyte send.\n", send_size);

    //rawソケットを閉じる
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
