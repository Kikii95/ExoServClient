#include "Client.h"

int main()
{
    Client client1;
    if (!client1.connectToServer("127.0.0.1", 9999))
        return -1;
	Client client2;
	if (!client2.connectToServer("127.0.0.2", 9999))
		return -1;

    client1.sendToServer("Hello 1, Server!");
	client2.sendToServer("Hello 2, Server!");
    std::string response1 = client1.receiveFromServer();
	std::string response2 = client2.receiveFromServer();
    std::cout << "-------------------------------------------- \n" << "Reponse du serveur : " << response1 << std::endl;
	std::cout << "-------------------------------------------- \n" << "Reponse du serveur : " << response2 << std::endl;

    return 0;
}
