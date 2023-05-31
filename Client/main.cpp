#include <iostream>
#include <string>
#include "zmqbroker.h"

int main() {
    // Maak een ZmqBroker-object aan
    ZmqBroker broker;
    std::string message;
    // Verbind met de ZMQ-subscriber op "tcp://benternet.pxl-ea-ict.be:24042"
    broker.connectSubscriber("tcp://benternet.pxl-ea-ict.be:24042");

    // Verbind met de ZMQ-pusher op "tcp://benternet.pxl-ea-ict.be:24041"
    broker.connectPusher("tcp://benternet.pxl-ea-ict.be:24041");

    // Blijf berichten sturen en ontvangen
    while (true) {
        // Bericht sturen
        std::string message;


        // Bericht ontvangen
        std::string receivedMessage = broker.receive();
        std::cout << "Ontvangen bericht: " << receivedMessage << std::endl;


        std::cout << "Voer een bericht in: ";
        std::getline(std::cin, message);

        broker.send(message);
        std::cout << "verzonden bericht: " << message << std::endl;
    }

    return 0;
}
