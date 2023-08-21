#include "Service.h"

Service::Service() {}



string Service::processMessages(string &recvMsg) {

        split(QString::fromStdString(recvMsg));


        switch (getCommandType(berichtInList[1])) {
            case CommandType::Delete:



            if (InfoCheck(2)){


                    std::cout << "Verwijderen: " << berichtInList[2].toStdString() << std::endl;

                    removeTask( berichtInList[2].toStdString());

                    return "Taak verwijderd ";

                }else{return "Onvoldoende info voor dit commando";}

            return "fout";

                break;
            case CommandType::Add:


                if (InfoCheck(3)){

                    std::cout << "Toevoegen: " << berichtInList[1].toStdString() << std::endl;



                    AddTask();

                    return " Taak Toegevoegd ";

                }else{return " Onvoldoende info voor dit commando";}



                break;
            case CommandType::Give:

                std::cout << "Geven: " <<berichtInList[2].toStdString() << std::endl;
                return printTasks();

                break;
            case CommandType::Complete:

                if (InfoCheck(3)){

                    std::cout << "Compleet: " << berichtInList[2].toStdString() << std::endl;

                    return completeTask();

                }else{return " Onvoldoende info voor dit commando";}

                break;
            case CommandType::Done:


                std::cout << "Done: " <<berichtInList[2].toStdString() << std::endl;

                break;
            case CommandType::LisTTasks:

            break;
            default:
                std::cout << "Onbekend commando: " << berichtInList[1].toStdString() << std::endl;
                return "Onbekend commando: " ;
                break;

    }
}

void Service::split(const QString& bericht) {
    berichtInList.clear();

    QStringList tokens = bericht.split(",");
    tokens.removeFirst();

    for (const QString& token : tokens) {
        berichtInList.push_back(token);
    }

   ClientID =  MakeClientID(berichtInList);

}
int Service::MakeClientID(vector<QString> &list){

    int Index =0;

    if(list.size()<2){

        if(InUseIds.find(Index)== InUseIds.end() || InUseIds.empty())
        {
              InUseIds.insert(Index);

            return Index;

        }else{Index++;}
    }
            else{ return  list[0].toInt();}

}

int Service::getClientID() const
{
    return ClientID;
}



string Service::AddTask() {
    Task NewTask(berichtInList[2].toStdString(), berichtInList[3].toStdString());

    if (Tasks.size() <= ClientID) {
        Tasks.resize(ClientID + 1);
    }

    Tasks[ClientID].append(NewTask);

    return "Task Added";
}

string Service::removeTask(const string &Taskname) {
    for (int i = 0; i < Tasks[ClientID].size(); ++i) {
        if (Tasks[ClientID][i].getName() == Taskname) {
            Tasks[ClientID].removeAt(i);
            return "Task Removed";
        }
    }
    return "Task was not found in the list. Try again.";
}

string Service::completeTask() {
    for (auto &task : Tasks[ClientID]) {
        if (task.getName() == berichtInList[2].toStdString()) {
            task.setCompleted(true);
            CompletedTasks.push_back(task);
            return "Task completed";
        }
    }
    return "Task not found in the list. Try again.";
}

string Service::printTasks() {
    std::string output;
    for (const auto &task : Tasks[ClientID]) {
        output += task.getName() + " - " + task.getDate() + " - " + (task.isCompleted() ? "Completed" : "Not completed") + "\n";
    }
    return output;
}



Service::CommandType Service::getCommandType(const QString& token) {

    if (token == "delete") {
        return CommandType::Delete;
    } else if (token == "add") {
        return CommandType::Add;
    } else if (token == "give") {
        return CommandType::Give;
    } else if (token == "complete") {
        return CommandType::Complete;
    } else if (token == "done") {
        return CommandType::Done;
    } else if (token == "complete") {
        return CommandType::LisTTasks;}
        else {
        return CommandType::Unknown;
    }
}




bool Service::InfoCheck(int infoCount){

    if(static_cast<int>( berichtInList.size()) < infoCount){ return false;cout<< "done"<<endl;
    }
        else{ return true; cout<< "done"<<endl;}
}




std::string Service::getIncompleteTasks() {

    std::string output;
    for (const auto& task : Tasks[ClientID]) {
        if(!task.isCompleted()){output += task.getName() + "." + task.getDate() + "." + (task.isCompleted() ? "voltooid" : "niet voltooid") + " ; ";
            }else{ output = "fout ";}
    }return output;
}
void Service::setClientID(int newClientID)
{
    ClientID = newClientID;
}

