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
#include"rawethernetsocketserver.h"


struct RawSocket* new_RawSocket(char *interface){
	struct RawSocket* rawsocket = (struct RawSocket*)malloc(sizeof(struct RawSocket));

	if((rawsocket->socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0){
		perror("socket");
		exit(0);
	};

    rawsocket->server_bind = server_bind;
    rawsocket->server_activate = server_activate;
    rawsocket->server_close = server_close;
    rawsocket->server_fileno = server_fileno;
    rawsocket->get_request = get_request;
    rawsocket->shutdown_request = shutdown_request;
    rawsocket->close_request = close_request;

    memset(rawsocket->interface,0x0,sizeof(rawsocket->interface));
    strcpy(rawsocket->interface, interface);
	
	return rawsocket;
}


void server_bind(struct RawSocket* pthis){
	struct sockaddr_ll sockaddr;
	memset(&sockaddr, 0x0, sizeof(sockaddr));
	sockaddr.sll_family = AF_PACKET;
	sockaddr.sll_protocol = htons(ETH_P_ALL);
	sockaddr.sll_ifindex = if_nametoindex(pthis->interface);
	if(bind(pthis->socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		perror("bind");
		exit(0);
	}
}

void server_activate(struct RawSocket* pthis){
	return;
};

void server_close(struct RawSocket* pthis){
	close(pthis->socket);
};


int server_fileno(struct RawSocket* pthis){
	return pthis->socket;
};


int get_request(struct RawSocket* pthis){

//	struct sockaddr_ll senderinfo;
//	socklen_t addrlen;
//	addrlen=sizeof(senderinfo);

	int recv_size;

	memset(pthis->buf,0x0,sizeof(pthis->buf));
    
	//recv_size = recvfrom(pthis->socket, pthis->buf, sizeof(pthis->buf), 0,(struct sockaddr *)&senderinfo, &addrlen);
	recv_size = recv(pthis->socket, pthis->buf, sizeof(pthis->buf),0);

    if(recv_size < 0){
        perror("recv error");
    }
	return recv_size;
};



void shutdown_request(struct RawSocket* pthis, int rawsock_request){
	pthis->close_request(pthis, rawsock_request);
};


void close_request(struct RawSocket* pthis, int rawsock_request){
	return;
};


