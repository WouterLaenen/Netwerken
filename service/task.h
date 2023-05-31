#ifndef TASK_H
#define TASK_H

#include <QString>

class Task {
private:
    QString naam;
    // QDate datum;
    bool voltooid;

public:
    Task(const QString& naam);
    // Task(const QString& naam, const QDate& datum);
    QString getNaam() const;
    void setNaam(const QString& naam);
    // QDate getDatum() const;
    // void setDatum(const QDate& datum);
    bool getVoltooid() const;
    void setVoltooid(bool value);
};

#endif // TASK_H
