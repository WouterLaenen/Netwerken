
#include <iostream>
#include "zmqbroker.h"
#include "Service.h"
#include "qthread.h"
#include <unordered_set>
//#include "message.h"

using namespace std;
using namespace zmq;

/*int main() {
    std::string message;

    ZmqBroker broker;

    broker.connectSubscriber("tcp://benternet.pxl-ea-ict.be:24042");
    broker.connectPusher("tcp://benternet.pxl-ea-ict.be:24041");

    Service MessageProces ;


        while (true) {

            std::string receivedMessage = broker.receive();

            std::cout << "Ontvangen bericht: " << receivedMessage << std::endl;

            MessageProces.split( QString::fromStdString(receivedMessage));

            broker.send(MessageProces.processMessages());


            //broker.send(receivedMessage.c_str());




        }

    return 0;
}*/


void messageProcessingThread(ZmqBroker& broker, Service& messageProces, string RecvMsg) {

        string msgout = messageProces.processMessages(RecvMsg);


        broker.send(msgout, messageProces.getClientID());

        //messageProces.setClientID(-1);

}

int main() {
    ZmqBroker broker;
    broker.connectSubscriber("tcp://benternet.pxl-ea-ict.be:24042");
    broker.connectPusher("tcp://benternet.pxl-ea-ict.be:24041");

    Service messageProces;

    string recievedmessage;

    while(true){

          recievedmessage = broker.receive();

        if(!recievedmessage.empty())
        {

             std::thread processingThread(messageProcessingThread, std::ref(broker), std::ref(messageProces),recievedmessage);
             processingThread.join();

             recievedmessage = "";
        }
    }

    // Start het verwerkingsdraad


    // Wacht op het eindigen van het verwerkingsdraad


    return 0;
}
