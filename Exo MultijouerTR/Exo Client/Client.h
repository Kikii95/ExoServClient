#ifndef CLIENT_H
#define CLIENT_H

#include "Sockets.h"
#include <iostream>
#include <string>

class Client
{
private:
    SOCKET clientSocket;
    sockaddr_in serverAddr;

public:
    Client();
    ~Client();
    bool connectToServer(const std::string& ip, unsigned short port);
    void sendToServer(const std::string& message);
    std::string receiveFromServer();
};

#endif // CLIENT_H
