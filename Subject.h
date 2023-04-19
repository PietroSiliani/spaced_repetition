//
// Created by pietr on 19/04/2023.
//

#ifndef SPACED_REPETITION_SUBJECT_H
#define SPACED_REPETITION_SUBJECT_H

#include <string>
#include <list>
#include <chrono>
#include <memory>
#include "DateNode.h"
#include "const.h"

using namespace std;
using namespace std::chrono;


class Subject {
public:
    explicit Subject(string &n, const vector<int> &spacing = DEFAULT_DAY_SPACING);

    [[nodiscard]] const string &getName() const; //TODO: what does [[nodiscard]] do?

    void setName(const string &name);

    void initRepetitionDates(const vector<int> &spacing = DEFAULT_DAY_SPACING);
    bool insertRepetitionDate(system_clock::time_point newDate);
    static system_clock::time_point getCurrentDate();
    static system_clock::time_point getNextDate(system_clock::time_point current, int nDays);

private:
    string name;
    std::shared_ptr<DateNode> nextDate;
    list<DateNode> repetitionDates;
};


#endif //SPACED_REPETITION_SUBJECT_H
