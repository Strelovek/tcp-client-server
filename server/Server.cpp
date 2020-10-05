#include "Server.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include "../libTLV/TVLEncoder.h"
#include "../libTLV/TVLEncoder.h"
#ifdef _WIN32
#include <Windows.h>
#endif

Server::Server()
{
}

void createResponse(char *buf, int bytes_read, int desc)
{
    static std::mutex m;
    m.lock();
    MySocket::Socket soc(desc);
    m.unlock();
#ifndef _WIN32
    sleep(5);
#else
    Sleep(5000);
#endif
    std::vector<uint8_t> t;
    std::string s;
    t.push_back(buf[0]);
    int l = TVLEncoder::decode(t);
    for (int i = 1; i <= l; i++)
    {
        s += buf[i];
    }
    m.lock();
    soc.sendData(buf, bytes_read);
    m.unlock();
    soc.closeSocket();
    delete buf;
    std::cout << "client requests: " << s << std::endl;
}

void Server::run()
{
    char *t;
    MySocket::Socket *soc = new MySocket::Socket;
    soc->listenSocket(27015);
    std::thread *th;
    std::cout << "server run" << std::endl;
    while (true)
    {
        soc->acceptSocket();
        while (true)
        {
            bytes_read = soc->recvData(buf, BUFER_SIZE);
            if (bytes_read <= 0)
                break;
            t = new char[BUFER_SIZE];
#ifdef _WIN32
#pragma warning(disable : 4996)
#endif
            strcpy(t, buf);
            th = new std::thread(createResponse, t, bytes_read, soc->getDescriptor());
            th->detach();
        }
    }
    soc->closeSocket();
    delete soc;
}

Server::~Server()
{
}
