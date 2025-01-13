#include "Server.h"

int main()
{
    Server server(9999);
    if (!server.start())
        return -1;

    SOCKET clientSocket1 = server.acceptClient();
    SOCKET clientSocket2 = server.acceptClient();

    if (clientSocket1 != INVALID_SOCKET)
    {
        std::string clientMessage1 = server.receiveFromClient(clientSocket1);
        std::cout << "-------------------------------------------- \n";
        std::cout << "Message du client : " << clientMessage1 << std::endl;
        server.sendToClient(clientSocket1, "Hi, Client 1 !");
    }


	if (clientSocket2 != INVALID_SOCKET)
	{
		std::string clientMessage2 = server.receiveFromClient(clientSocket2);
        std::cout << "-------------------------------------------- \n";
		std::cout << "Message du client : " << clientMessage2 << std::endl;
		server.sendToClient(clientSocket2, "Hi, Client 2 !");
	}

    return 0;
}
