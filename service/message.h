#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <vector>
#include <QString>
#include "string.h"
#include "task.h"
#include "zmqbroker.h"
#include "qstringlist.h"

class Message {
private:
    std::vector<QString> berichtInList;
    ZmqBroker broker;
    std::vector<Task> tasks;

public:
    Message(const std::string& bericht);
    void split(const QString& bericht);
    void processMessages();
    void AddTask();
    void removeTask();
    void completeTask();
    void printTasks();
    void send(const QString& message);

private:
    enum class CommandType {
        Delete,
        Add,
        Give,
        Complete,
        Done,
        Unknown
    };

    CommandType getCommandType(const QString& token);
};

#endif // MESSAGE_H
