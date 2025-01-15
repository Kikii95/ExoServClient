#include "Client.h"
#include "Thread.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <atomic>

std::atomic<int> threadCounter(0);

void clientTask(const std::string& ip, unsigned short port, int clientID) {
    Client client;
    if (!client.connectToServer(ip, port)) {
        std::cerr << "Client " << clientID << " : Impossible de se connecter au serveur." << std::endl;
        return;
    }

    for (int i = 1; i <= 50; ++i) {
        std::string message = "Client " + std::to_string(clientID) + " : Message " + std::to_string(i);
        client.sendToServer(message);
        std::string response = client.receiveFromServer();
        std::cout << "Reponse pour Client " << clientID << " : " << response << std::endl;
    }

    std::cout << "Client " << clientID << " termine." << std::endl;
}

void threadCreatorTask(const std::string& ip, unsigned short port, std::vector<Thread*>& clientThreads) {
    for (int i = 1; i <= 500; ++i) {
        Thread* thread = new Thread(threadCounter.fetch_add(1) + 1);
        thread->Start([=]() { clientTask(ip, port, i); });
        clientThreads.push_back(thread);
    }
}

int main() {
    const std::string serverIP = "127.0.0.1";
    const unsigned short serverPort = 9999;

    std::vector<Thread*> clientThreads;

	for (int i = 0; i < 50; ++i) {
		threadCreatorTask(serverIP, serverPort, clientThreads);
	}



    while (!clientThreads.empty()) {
        for (auto it = clientThreads.begin(); it != clientThreads.end();) {
            if (!(*it)->IsRunning()) {
                delete* it;
                it = clientThreads.erase(it);
            }
            else {
                ++it;
            }
        }
    }

	Sleep(1000);

    std::cout << "\n\nTous les clients ont termine." << std::endl;
    return 0;
}

