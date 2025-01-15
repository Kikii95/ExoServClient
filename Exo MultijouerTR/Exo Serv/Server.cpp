#include "Server.h"

Server::Server(unsigned short port) : port(port), serverSocket(INVALID_SOCKET)
{
}

Server::~Server()
{
    if (serverSocket != INVALID_SOCKET)
    {
        Sockets::CloseSocket(serverSocket);
    }
    Sockets::Release();
}

bool Server::start()
{
    if (!Sockets::Start())
    {
        std::cerr << "Erreur initialisation WinSock : " << Sockets::GetError() << std::endl;
        return false;
    }

    serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Erreur creation socket : " << Sockets::GetError() << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Erreur bind : " << Sockets::GetError() << std::endl;
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Erreur listen : " << Sockets::GetError() << std::endl;
        return false;
    }

    std::cout << "Serveur demarre sur le port " << port << std::endl;
    std::cout << "-------------------------------------------- \n";
    return true;
}

SOCKET Server::acceptClient()
{
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Erreur accept : " << Sockets::GetError() << std::endl;
        return INVALID_SOCKET;
    }

    char clientIP[INET_ADDRSTRLEN] = { 0 };
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    std::cout << "Connexion de " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
    return clientSocket;
}

void Server::sendToClient(SOCKET clientSocket, const std::string& message)
{
    send(clientSocket, message.c_str(), message.size(), 0);
}

std::string Server::receiveFromClient(SOCKET clientSocket)
{
    char buffer[1024] = { 0 };
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';
        return std::string(buffer);
    }
    else if (bytesReceived == 0)
    {
        std::cout << "\nLe client a ferme la connexion." << std::endl;
    }
    else
    {
        std::cerr << "Erreur reception : " << Sockets::GetError() << std::endl;
    }
    return "";
}
