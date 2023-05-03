//
// Created by pietr on 19/04/2023.
//

#ifndef SPACED_REPETITION_SUBJECT_H
#define SPACED_REPETITION_SUBJECT_H

#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>
#include "include/date/date.h"
//#include "DateNode.h"
#include "const.h"

using namespace std;
using namespace std::chrono;

typedef chrono::system_clock::time_point rep_date;


class Subject {
public:
    explicit Subject(string &n, const vector<int> &spacing = DEFAULT_DAY_SPACING);

    [[nodiscard]] const string &getName() const; //TODO: what does [[nodiscard]] do?

    void setName(const string &name);

    void initRepetitionDates(const vector<int> &spacing = DEFAULT_DAY_SPACING);
    bool insertRepetitionDate(system_clock::time_point newDate);
    rep_date removeRepetitionDate(int idx);
    static system_clock::time_point getCurrentDate();
    static system_clock::time_point getNextDate(system_clock::time_point current, int nDays);
    [[nodiscard]] string asString() const;

private:
    string name;
    int nextDateIdx;
    vector<rep_date> repetitionDates;
};


#endif //SPACED_REPETITION_SUBJECT_H
