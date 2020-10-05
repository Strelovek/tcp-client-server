#ifndef SERVER_H
#define SERVER_H
#include "../libTLV/Socket.h"

class Server
{
    static const int BUFER_SIZE = 2048;
    int bytes_read=0;
    char buf[BUFER_SIZE];
    friend void createResponse(char *buf, int bytes_read, int desc);

public:
    Server();
    void  run();
    ~Server();
};
#endif