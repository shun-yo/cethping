#include<stdio.h>

#define BUFSIZE 8192

struct RawSocket;
struct BaseReqestHandler;


struct RawSocket{
    int socket;
    char buf[BUFSIZE];
    char interface[16];
    void (*server_bind)(struct RawSocket* pthis);
    void (*server_activate)(struct RawSocket* pthis);
    void (*server_close)(struct RawSocket* pthis);
    int (*server_fileno)(struct RawSocket* pthis);
    int (*get_request)(struct RawSocket* pthis);
    void (*shutdown_request)(struct RawSocket* pthis, int rawsock_request);
    void (*close_request)(struct RawSocket* pthis, int rawsock_request);
};


struct RawSocket* new_RawSocket(char *interface);
void server_bind(struct RawSocket* pthis);
void server_activate(struct RawSocket* pthis);
void server_close(struct RawSocket* pthis);
int server_fileno(struct RawSocket* pthis);
//void get_request(struct RawSocket* pthis);
int get_request(struct RawSocket* pthis);
void shutdown_request(struct RawSocket* pthis, int rawsock_request);
void close_request(struct RawSocket* pthis, int rawsock_request);



//struct BaseReqestHandler{
//    
//    void (*finish)(struct *BaseRequestHandler);
//};

