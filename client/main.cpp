#include <iostream>
#include "../libTLV/Socket.h"
#include "../libTLV/TVLEncoder.h"
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    std::string s, msg;
    const int bufSize = 2048;
    char buf[bufSize];
    uint32_t ip;
    ip = 1;
    ip |= 56 << 8;
    ip |= 168 << 16;
    ip |= 192 << 24;
    while (true)
    {
        std::cout << "enter a message" << std::endl;
        std::cin >> msg;
        std::vector<uint8_t> l = TVLEncoder::encode(msg.length(), TVLEncoder::shortForm);
        for (auto i : l)
        {
            s += static_cast<char>(i);
        }
        s += msg;
        MySocket::Socket soc;
#ifndef _WIN32
        //INADDR_LOOPBACK
        soc.connectToHost(INADDR_LOOPBACK, 27015);
#else
        soc.connectToHost(ip, 27015);
#endif
        soc.sendData(const_cast<char *>(s.c_str()), bufSize);
        soc.recvData(buf, bufSize);
        l.clear();
        l.push_back(buf[0]);
        int msgLen = TVLEncoder::decode(l);
        buf[0] = ' ';
        buf[msgLen + 1] = '\0';
        std::cout << "server response:" << buf << std::endl;
        soc.closeSocket();
        msg.clear();
        s.clear();
        l.clear();
    }
    return 0;
}
