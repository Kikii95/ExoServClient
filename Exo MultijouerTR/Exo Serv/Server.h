#ifndef SERVER_H
#define SERVER_H

#include "Sockets.h"
#include <iostream>
#include <string>

class Server
{
private:
    SOCKET serverSocket;
    sockaddr_in serverAddr;
    unsigned short port;

public:
    Server(unsigned short port);
    ~Server();
    bool start();
    SOCKET acceptClient();
    void sendToClient(SOCKET clientSocket, const std::string& message);
    std::string receiveFromClient(SOCKET clientSocket);
};

#endif // SERVER_H
