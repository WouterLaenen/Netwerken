#include "zmqbroker.h"
#include <iostream>

using namespace std;
using namespace zmq;

ZmqBroker::ZmqBroker() : context(1), subscriber(context, ZMQ_SUB), pusher(context, ZMQ_PUSH) {}

string subtag = "#TaskMa";

void ZmqBroker::connectSubscriber(const string& address) {
    subscriber.connect(address);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subtag.c_str(), subtag.length());
}

void ZmqBroker::connectPusher(const string& address) {
    pusher.connect(address);
}

void ZmqBroker::send(const string& message, int ID) {

    cout<< ID<<endl;

    string taggedMessage = "!TaskMa," + std::to_string(ID) + "," + message;
    message_t zmqMessage(taggedMessage.size());
    memcpy(zmqMessage.data(), taggedMessage.data(), taggedMessage.size());
    pusher.send(zmqMessage);
    std::cout << taggedMessage << std::endl;
}

string ZmqBroker::receive() {
    message_t zmqMessage;
    subscriber.recv(&zmqMessage);
    string message(static_cast<char*>(zmqMessage.data()), zmqMessage.size());


    return message;
}


/*using namespace zmq;
using namespace std;

ZmqBroker::ZmqBroker() : context(1), pusher(context, socket_type::push) {}

void ZmqBroker::connectPusher(const string& address) {
    pusher.connect(address);
}

void ZmqBroker::connectSubscriber(const string& subscriberAddress) {
    thread listeningThread(&ZmqBroker::listenLoop, this, subscriberAddress);
    listeningThread.detach();
}

void ZmqBroker::listenLoop(const string& subscriberAddress) {


    context_t subscriberContext(1);
    socket_t subscriber(subscriberContext, socket_type::sub);

    subscriber.connect(subscriberAddress);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subTag.c_str(), subTag.size()); // Listening for messages with the tag "#TaskMa"

    while (true) {
        message_t zmqMessage;
        subscriber.recv(&zmqMessage);
        QString message = QString::fromStdString(static_cast<char*>(zmqMessage.data()));

        // Extract service ID and message from the received message
        QStringList parts = message.split(',');
        parts.removeFirst(); // Remove the first element (service ID)

        if (!parts[0].toInt()) {
            // If parts[0] is not a valid int, assign a new client ID

            parts.prepend(QString::number(usedId.size()+1));
            usedId.push_back(usedId.size()+1);
            clientThreads.push_back(make_pair(parts[0))

        } else {

            for(auto& tok: clientThreads){
                if(tok.first == parts[0].toInt()){

                    tok.second.join();
                    break;
                }

            }
        }

        std::string clientMessage = parts.join(",").toStdString(); // Join the remaining parts to get the client message

        handleMessage(QString::number(clientId), clientMessage);
    }
}


void ZmqBroker::send(const string& serviceId, int clientId, const string& message) {
    {
        lock_guard<mutex> lock(mtx);
        if (usedClientIds[serviceId].find(clientId) == usedClientIds[serviceId].end()) {
            usedClientIds[serviceId].insert(clientId);
            newClientIdQueue.emplace(serviceId, clientId);
        }
    }

    {
        lock_guard<mutex> lock(mtx);
        messageQueue.emplace(make_pair(serviceId, clientId), message);
    }
}

void ZmqBroker::sendLoop(const string& serviceId, int clientId) {
    while (true) {
        pair<pair<string, int>, string> queuedMessage;
        {
            lock_guard<mutex> lock(mtx);
            if (!messageQueue.empty() && messageQueue.front().first == make_pair(serviceId, clientId)) {
                queuedMessage = messageQueue.front();
                messageQueue.pop();
            }
        }

        if (!queuedMessage.first.first.empty()) {
            string taggedMessage = PushTag + to_string(clientId);
            message_t zmqMessage(taggedMessage.size());

            memcpy(zmqMessage.data(), taggedMessage.data(), taggedMessage.size());
            pusher.send(zmqMessage, send_flags::none);
        }
    }
}

void ZmqBroker::handleMessage(const string& serviceId, const string& message) {

    int clientId = stoi(message);
    if (usedClientIds[serviceId].find(clientId) == usedClientIds[serviceId].end()) {
        usedClientIds[serviceId].insert(clientId);
        newClientIdQueue.emplace(serviceId, clientId);
    }
}
string ZmqBroker::receive() {
    string receivedMessage;
    {
        lock_guard<mutex> lock(mtx);
        if (!messageQueue.empty()) {
            receivedMessage = messageQueue.front().second;
            messageQueue.pop();
        }
    }
    return receivedMessage;
}*/





