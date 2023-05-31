#include "message.h"

Message::Message(const std::string& bericht) {
    split(QString::fromStdString(bericht));
}

void Message::split(const QString& bericht) {
    berichtInList.clear();

    QStringList tokens = bericht.split(",");
    for (const QString& token : tokens) {
        berichtInList.push_back(token);
    }

    processMessages();
}

void Message::processMessages() {

        switch (getCommandType(berichtInList[2])) {
            case CommandType::Delete:
                std::cout << "Verwijderen: " << berichtInList[2].toStdString() << std::endl;
                removeTask();
                break;
            case CommandType::Add:

                AddTask();
                break;
            case CommandType::Give:
                std::cout << "Geven: " <<berichtInList[2].toStdString() << std::endl;
                printTasks();
                break;
            case CommandType::Complete:
                std::cout << "Compleet: " << berichtInList[2].toStdString() << std::endl;
                completeTask();
                break;
            case CommandType::Done:
                std::cout << "Done: " <<berichtInList[2].toStdString() << std::endl;
                break;
            default:
                std::cout << "Onbekend commando: " << berichtInList[2].toStdString() << std::endl;
                break;

    }
}

void Message::AddTask() {
    if (berichtInList.size() > 3) {
        QString name = berichtInList[3];
        // QDate date = QDate::fromString(berichtInList[4], "dd/MM/yyyy");
        Task task(name);

        tasks.push_back(task);
        //send("Taak toegevoegd" );
        std::cout << "Taak toegevoegd" << task.getNaam().toStdString() << std::endl;
    }
}

void Message::removeTask() {
    if (berichtInList.size() > 3) {
        int index = berichtInList[3].toInt();
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            send("Taak verwijderd" );
            std::cout << "Taak voltooid" << std::endl;
        }
    }
}

void Message::completeTask() {
    if (berichtInList.size() > 3) {
        int index = berichtInList[3].toInt();
        if (index >= 0 && index < tasks.size()) {
            tasks[index].setVoltooid(true);
            send("Taak voltooid" );
            std::cout << "Taak voltooid" << std::endl;
        }
    }
}

Message::CommandType Message::getCommandType(const QString& token) {
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
    } else {
        return CommandType::Unknown;
    }
}

void Message::printTasks() {
    for (const auto& task : tasks) {

        send(task.getNaam() + "," + (task.getVoltooid() ? "Ja" : "Nee") );

        std::cout << "Naam: " << task.getNaam().toStdString() << ", Voltooid: " << (task.getVoltooid() ? "Ja" : "Nee") << std::endl;
    }
}

void Message::send(const QString& message) {
    broker.send( message.toStdString());
}
