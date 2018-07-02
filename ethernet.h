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

//パケットのフォーマット
struct ethhdr_frame {
    unsigned char	h_dest[6];	/* destination eth addr	*/
    unsigned char	h_source[6];	/* source ether addr	*/
    __be16		h_proto;		/* packet type ID field	*/
    char payload[];
};

//MACアドレスの文字列から生データに変換
void set_macaddr_from_string(char *str, char *raw);

//インターフェース名からMACアドレス取得
void set_macaddr_from_ifname(char *interface, char *raw);

//MACアドレスの生データを文字列でprintf
void print_macaddr(char *raw);
