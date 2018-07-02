#include<stdio.h>

#define BUFSIZE 8192

struct RawSocket;
struct BaseReqestHandler;


struct RawSocket{
    int socket;
    char buf[BUFSIZE];
    char interface[16];
    void (*bind_rawsocket)(struct RawSocket* pthis);
    int (*recv_rawsocket)(struct RawSocket* pthis);
    void (*close_rawsocket)(struct RawSocket* pthis);
};


struct RawSocket* new_RawSocket(char *interface);
void close_RawSocket(struct RawSocket* pthis);
void bind_RawSocket(struct RawSocket* pthis);
int recv_RawSocket(struct RawSocket* pthis);


