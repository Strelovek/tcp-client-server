#ifndef SOCKET_H
#define SOCKET_H
#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#else
#include <winsock2.h>
#include "winsock2.h"
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // _WIN32
#include <iostream>
#include <cstring>
namespace MySocket
{
    class Socket
    {
#ifndef _WIN32
        int sock=0, listener = 0;
        struct sockaddr_in addr;
#else
        WSADATA wsaData;
        SOCKET sock, listener;
        struct sockaddr_in addr;
#endif // _WIN32
    public:
        Socket();
#ifndef _WIN32
        Socket(int desc);
#else
        Socket(SOCKET desc);
#endif
        void connectToHost(int ip, int port);
        void listenSocket(int port);
        void acceptSocket();
        void closeSocket();
        void sendData(char *buf, int bufSize);
        int recvData(char *buf, int bufSize);
        int getDescriptor();
        ~Socket();
    };
} // namespace MySocket

#endif