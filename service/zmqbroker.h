#ifndef ZMQBROKER_H
#define ZMQBROKER_H

#include <string>
#include <zmq.hpp>
#include <iostream>


class ZmqBroker {
private:
    zmq::context_t context;
    zmq::socket_t subscriber;
    zmq::socket_t pusher;

public:
    ZmqBroker();
    void connectSubscriber(const std::string& address);
    void connectPusher(const std::string& address);
    void send(const std::string& message);
    std::string receive();
};

#endif // ZMQBROKER_H
