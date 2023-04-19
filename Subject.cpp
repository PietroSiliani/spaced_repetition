//
// Created by pietr on 19/04/2023.
//

#include "Subject.h"

Subject::Subject(string &n, const vector<int> &spacing) {
    this->name = n;
    initRepetitionDates(spacing);
}

system_clock::time_point Subject::getCurrentDate() {
    return std::chrono::system_clock::now();
}

system_clock::time_point Subject::getNextDate(system_clock::time_point current, int nDays) {
    return current + hours(nDays*24);
}

const string &Subject::getName() const {
    return name;
}

void Subject::setName(const string &name) {
    Subject::name = name;
}

void Subject::initRepetitionDates(const vector<int> &spacing) {
    //TODO: idea: fill a list with DateNodes, each DateNode points to next date
    //Motivation: list allows for easy iteration over each node through iterators
    //DateNode allows for easy access to nextDate without having to save pointers to iterators
    //(and thus without the need to modify nextDate in case of insertion/removal of a node)

    repetitionDates = list<DateNode>();
    const auto current = getCurrentDate();

    //fill list
    for (const auto &days: spacing) {
        repetitionDates.emplace_back((current + hours(days*24)));
    }

    //set next pointers
    for (auto currentItr = repetitionDates.begin(); currentItr != repetitionDates.end(); currentItr++) {
        auto nextItr = next(currentItr, 1);
        if (nextItr != repetitionDates.end()) {
            currentItr->resetNext(&(*nextItr)); //pass address of DateNote "pointed" by nextItr
        }
    }
}

bool Subject::insertRepetitionDate(system_clock::time_point newDate) {
    //Ordered insert based on date value
    //TODO: should it return result or not? Could insertion fail in some way? (check on validity of the date should be made somewhere else)

    bool inserted = false;
    auto currentItr = repetitionDates.begin();
    while(!inserted && currentItr != repetitionDates.end()) {
        auto currentDate = currentItr->getDate();
        if (currentDate < newDate) {
            auto newNext = currentItr->getNext(); //read next of current DateNode
            DateNode newNode = DateNode(newDate, newNext.get()); //create new DateNode and set its next ptr to newNext
            currentItr->resetNext(&newNode); //change next ptr of currently pointed DateNode
            repetitionDates.insert(currentItr, newNode);

            inserted = true;
        } else {
            currentItr++;
        }
    }
    return inserted;
}

