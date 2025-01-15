#include "Server.h"
#include "Thread.h"
#include <vector>
#include <iostream>
#include <atomic>
#include <chrono>
#include <thread>

std::atomic<int> threadCounter(0);

void handleClient(Server& server, SOCKET clientSocket) {
    if (clientSocket != INVALID_SOCKET) {
        std::string clientMessage;
        while (true) {
            clientMessage = server.receiveFromClient(clientSocket);
            if (clientMessage.empty()) {
                std::cout << "Client deconnecte." << std::endl;
                break;
            }
            std::cout << "Message du client : " << clientMessage << std::endl;
            server.sendToClient(clientSocket, "Reponse du serveur : " + clientMessage);
        }
        Sockets::CloseSocket(clientSocket);
    }
}

int main() {
    Server server(9999);
    if (!server.start())
        return -1;

    std::vector<Thread*> clientThreads;

    while (true) {
        SOCKET clientSocket = server.acceptClient();
        if (clientSocket != INVALID_SOCKET) {
            Thread* thread = new Thread(threadCounter.fetch_add(1) + 1);
            thread->Start([&server, clientSocket]() { handleClient(server, clientSocket); });
            clientThreads.push_back(thread);
        }

        for (auto it = clientThreads.begin(); it != clientThreads.end();) {
            if (!(*it)->IsRunning()) {
                delete* it;
                it = clientThreads.erase(it);
            }
            else {
                ++it;
            }
        }

        if (clientThreads.empty()) {
            std::cout << "Tous les clients sont deconnectes. Arret du serveur." << std::endl;
            break;
        }
    }

    std::cout << "Serveur arrete." << std::endl;
    return 0;
}
