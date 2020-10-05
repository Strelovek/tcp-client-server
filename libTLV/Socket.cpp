#include "Socket.h"

using namespace MySocket;

#pragma warning(disable : 4996)

#ifndef _WIN32
Socket::Socket(int desc)
{
	sock = desc;
}
#else
Socket::Socket(SOCKET desc)
{
	sock = desc;
}
#endif

Socket::Socket()
{
#ifndef _WIN32
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0)
	{
		throw std::runtime_error("socket init failed");
	}
#else
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != NO_ERROR)
	{
		std::cout << "Error at WSAStartup" << std::endl;
	}
	listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listener == INVALID_SOCKET)
	{
		WSACleanup();
		throw std::runtime_error("socket init failed");
	}
#endif
}

void Socket::connectToHost(int ip, int port)
{
	sock = listener;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(ip);
#ifndef _WIN32
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		throw std::runtime_error("socket connection failed");
	}
#else
	if (connect(sock, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		WSACleanup();
		throw std::runtime_error("socket connection failed");
	}
#endif
}

void Socket::sendData(char *buf, int bufSize)
{
	send(sock, buf, bufSize, 0);
}

void Socket::closeSocket()
{
#ifndef _WIN32
	close(sock);
#else
	closesocket(sock);
#endif
}

void Socket::acceptSocket()
{
	sock = accept(listener, 0, 0);
	if (sock < 0)
	{
		throw std::runtime_error("socket accept failed");
	}
}

void Socket::listenSocket(int port)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
#ifndef _WIN32
	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		throw std::runtime_error("bind failed");
	}
	listen(listener, 1);
#else
	if (bind(listener, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		closesocket(listener);
		throw std::runtime_error("bind failed");
	}
	listen(listener, 1);
#endif
}

int Socket::getDescriptor()
{
#ifndef _WIN32
	int t = sock;
	sock = 0;
	return t;
#else
	SOCKET t = sock;
	sock = 0;
	return t;
#endif
}

int Socket::recvData(char *buf, int bufSize)
{
	return recv(sock, buf, bufSize, 0);
}

Socket::~Socket()
{
}