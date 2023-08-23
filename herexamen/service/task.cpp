#include "task.h"

void Task::setDate(const std::string &newDate)
{
    date = newDate;
}

Task::Task(const std::string& name, const std::string& date)
    : name(name), date(date), completed(false) {}



std::string Task::getName() const {
    return name;
}

std::string Task::getDate() const {
    return date;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool status) {
    completed = status;
}
