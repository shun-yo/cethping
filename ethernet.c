#include<stdio.h>
#include<string.h>
//#include"ethernet.h"

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<net/if.h>
#include<netpacket/packet.h>
#include<sys/ioctl.h>

#include"ethernet.h"


void print_mac_address(char *raw){
    int i;

    for(i=0; i<5; i++){
        printf("%02x:", (unsigned char)raw[i]);
    }
    printf("%02x", (unsigned char)raw[5]);

}


void mac_raw(char *str, char *raw){
    sscanf(str, "%02x:%02x:%02x:%02x:%02x:%02x", (int*)&raw[0], (int*)&raw[1], (int*)&raw[2], (int*)&raw[3], (int*)&raw[4], (int*)&raw[5]);

}


void get_hw_addr(char *interface, char *raw){
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    close(fd);

    *(raw) = (unsigned char)ifr.ifr_hwaddr.sa_data[0];
    *(raw+1) = (unsigned char)ifr.ifr_hwaddr.sa_data[1];
    *(raw+2) = (unsigned char)ifr.ifr_hwaddr.sa_data[2];
    *(raw+3) = (unsigned char)ifr.ifr_hwaddr.sa_data[3];
    *(raw+4) = (unsigned char)ifr.ifr_hwaddr.sa_data[4];
    *(raw+5) = (unsigned char)ifr.ifr_hwaddr.sa_data[5];


}
