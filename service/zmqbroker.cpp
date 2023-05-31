#include "zmqbroker.h"

using namespace std;
using namespace zmq;

ZmqBroker::ZmqBroker() : context(1), subscriber(context, ZMQ_SUB), pusher(context, ZMQ_PUSH) {}

string subtag = "#TaskMa ";

void ZmqBroker::connectSubscriber(const string& address) {
    subscriber.connect(address);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, subtag.c_str(), subtag.length());
}

void ZmqBroker::connectPusher(const string& address) {
    pusher.connect(address);
}

void ZmqBroker::send(const string& message) {
    string taggedMessage = "!TaskMa " + message;
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



