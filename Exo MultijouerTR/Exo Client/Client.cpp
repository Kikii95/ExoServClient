#include "Client.h"

Client::Client() : clientSocket(INVALID_SOCKET)
{
}

Client::~Client()
{
    if (clientSocket != INVALID_SOCKET)
    {
        Sockets::CloseSocket(clientSocket);
    }
    Sockets::Release();
}

bool Client::connectToServer(const std::string& ip, unsigned short port)
{
    if (!Sockets::Start())
    {
        std::cerr << "Erreur initialisation WinSock : " << Sockets::GetError() << std::endl;
        return false;
    }

    clientSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Erreur creation socket : " << Sockets::GetError() << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Erreur conversion adresse IP" << std::endl;
        return false;
    }

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Erreur connexion : " << Sockets::GetError() << std::endl;
        return false;
    }

    std::cout << "Connexion reussie au serveur !" << std::endl;
    return true;
}

void Client::sendToServer(const std::string& message)
{
    send(clientSocket, message.c_str(), message.size(), 0);
}

std::string Client::receiveFromServer()
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
        std::cout << "Le serveur a ferme la connexion." << std::endl;
    }
    else
    {
        std::cerr << "Erreur reception : " << Sockets::GetError() << std::endl;
    }
    return "";
}
