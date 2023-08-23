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
    std::string mesageIn;

public:
    ZmqBroker();
    void connectSubscriber(const std::string& address);
    void connectPusher(const std::string& address);
    void send(const std::string& message , int ID );
    std::string receive();
};

#endif // ZMQBROKER_H

/*#ifndef ZMQBROKER_H
#define ZMQBROKER_H

#include <zmq.hpp>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <queue>
#include <vector>
#include <string> // Include the <string> header
#include <QString>
#include "qstringlist.h"

using namespace zmq;
using namespace std;

class ZmqBroker {
public:

    ZmqBroker();
    void connectPusher(const string& address);
    void connectSubscriber(const string& subscriberAddress);
    void send(const string& serviceId, int clientId, const string& message);
    string receive();
    vector<int> usedId;
private:

    string subTag = "#TaskMa";
    string PushTag = "!TaskMa,";

    void listenLoop(const string& subscriberAddress);
    void sendLoop(const string& serviceId, int clientId);
    void handleMessage(const string& serviceId, const string& message);

    context_t context;
    socket_t pusher;

    vector<pair<int, thread>>clientThreads;

    mutex mtx;
    queue<pair<string, int>> newClientIdQueue;
    queue<pair<pair<string, int>, string>> messageQueue;
};

#endif // ZMQBROKER_H
*/
