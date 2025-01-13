#ifndef SOCKETS_H
#define SOCKETS_H

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#define SOCKET_ERROR (-1)
#endif

namespace Sockets
{
    bool Start();
    void Release();
    int GetError();
    void CloseSocket(SOCKET socket);
}

#endif 



