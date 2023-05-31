#include "zmqbroker.h"

using namespace std;
using namespace zmq;

ZmqBroker::ZmqBroker() : context(1), subscriber(context, ZMQ_SUB), pusher(context, ZMQ_PUSH) {}

string Subtag = "!TaskMa ";

void ZmqBroker::connectSubscriber(const string& address) {
    subscriber.connect(address);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, Subtag.c_str()  ,Subtag.length());
}

void ZmqBroker::connectPusher(const string& address) {
    pusher.connect(address);
}

void ZmqBroker::send(const string& message) {
    string taggedMessage = "#TaskMa " + message;
    message_t zmqMessage(taggedMessage.size());
    memcpy(zmqMessage.data(), taggedMessage.data(), taggedMessage.size());
    pusher.send(zmqMessage);

}

string ZmqBroker::receive() {
    message_t zmqMessage;
    subscriber.recv(&zmqMessage);
    string message(static_cast<char*>(zmqMessage.data()), zmqMessage.size());
    return message;
}


