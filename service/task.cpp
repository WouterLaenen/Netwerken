#include "task.h"

Task::Task(const QString& naam) : naam(naam), voltooid(false) {}

// Task::Task(const QString& naam, const QDate& datum) : naam(naam), datum(datum), voltooid(false) {}

QString Task::getNaam() const {
    return naam;
}

void Task::setNaam(const QString& naam) {
    this->naam = naam;
}

// QDate Task::getDatum() const {
//     return datum;
// }

// void Task::setDatum(const QDate& datum) {
//     this->datum = datum;
// }

bool Task::getVoltooid() const {
    return voltooid;
}

void Task::setVoltooid(bool value) {
    voltooid = value;
}
