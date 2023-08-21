#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <QString>
#include "string.h"
#include "task.h"
#include "zmqbroker.h"
#include "qstringlist.h"
#include "qlist.h"
using namespace std;

class Service {
private:
    vector<QString> berichtInList;
    string berichtOut;

    ZmqBroker broker;

    vector<Task> CompletedTasks;

    std::unordered_set<int> InUseIds;

    vector<QList<Task>> Tasks;

    void split(const QString& bericht);

    string AddTask();
    string removeTask(const string &Taskname);
    string completeTask();
    string printTasks();
    string getIncompleteTasks();

    string Recieve();
    bool InfoCheck(int infoCount);


public:


    Service();
    string processMessages(string &recvMsg);
    int MakeClientID(vector<QString> &List);

    int ClientID = -1;






    void setClientID(int newClientID);

    int getClientID() const;

private:
    enum class CommandType {
        Delete,
        Add,
        Give,
        Incompleted,
        Complete,
        Done,
        LisTTasks,
        Unknown
    };

    CommandType getCommandType(const QString& token);
};

#endif // SERVICE_H
