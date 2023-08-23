#include "zmqbroker.h"

using namespace std;
using namespace zmq;

ZmqBroker::ZmqBroker() : context(1), subscriber(context, ZMQ_SUB), pusher(context, ZMQ_PUSH) {}

string Subtag = "!TaskMa,";

void ZmqBroker::connectSubscriber(const string& address) {
    subscriber.connect(address);
    subscriber.setsockopt(ZMQ_SUBSCRIBE, Subtag.c_str()  ,Subtag.length());
}

void ZmqBroker::connectPusher(const string& address) {
    pusher.connect(address);
}

void ZmqBroker::send(const string& message) {

    string taggedMessage ;

    if(ClientID != -1){
        taggedMessage = "#TaskMa," + to_string(ClientID) + ","+ message;
    }else{taggedMessage = "#TaskMa," + message;}


    message_t zmqMessage(taggedMessage.size());
    memcpy(zmqMessage.data(), taggedMessage.data(), taggedMessage.size());
    pusher.send(zmqMessage);
    std::cout << "verzonden bericht: " << taggedMessage << std::endl;
}

string ZmqBroker::receive() {
    message_t zmqMessage;
    subscriber.recv(&zmqMessage);
    QString message( QString::fromStdString( static_cast<char*>(zmqMessage.data())));

    MessageIn = message.split(",");
    MessageIn.removeFirst();

    ClientID = MessageIn[0].toInt();

    return message.toStdString();
}


