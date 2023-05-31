
#include <iostream>
#include "zmqbroker.h"
#include "message.h"

using namespace std;
using namespace zmq;

int main() {

    ZmqBroker broker;
    broker.connectSubscriber("tcp://benternet.pxl-ea-ict.be:24042");
    broker.connectPusher("tcp://benternet.pxl-ea-ict.be:24041");

    while (true) {
         std::string receivedMessage; //= broker.receive();

         cin >> receivedMessage;


        // Verwerk het bericht met behulp van de Message-klasse
        Message Message(receivedMessage);

        // Bericht sturen


        // Bericht ontvangen

    }

    return 0;
}







