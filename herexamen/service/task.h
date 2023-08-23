#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
private:
    std::string name;
    std::string date;
    bool completed;



public:

    Task(const std::string& name, const std::string& date);
    std::string getName() const;
    std::string getDate() const;
    bool isCompleted() const;
    void setCompleted(bool status);
    void setDate(const std::string &newDate);
};

#endif  // TASK_H
