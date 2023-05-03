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
    /*
     * Receives a vector of "spacings" between the dates
     * initializes the vector of repetition dates based on the spacing
     * values in the "spacing" vector represent the offset in days between the FIRST repetition
     * and the date of the repetition that is being inserted at that index
     */

    repetitionDates = vector<rep_date>();
    const auto current = getCurrentDate();

    //fill list

    using namespace date::literals;

    /*constexpr date::sys_days tp = 1900_y/01/01;  // Compile-time date literal
    // Just add and print out
    using date::operator<<;
    std::cout << tp + days << '\n';  // 1902-09-28*/

   /*std::cout <<  "inserting dates: " << std::endl;*/
    for (const auto &d: spacing) {
        date::days days{d};
        /*std::cout <<  "current: " << date::format("%D", current) << std::endl;
        std::cout <<  "current + spacing: " << date::format("%D", current + days) << std::endl;*/
        repetitionDates.push_back(getCurrentDate() + days);
    }

    nextDateIdx = 0; //init next date index to first date
}

bool Subject::insertRepetitionDate(rep_date newDate) {
    //Ordered insert based on date value

    bool inserted = false;
    auto currentItr = repetitionDates.begin();
    while(!inserted && currentItr != repetitionDates.end()) {
        auto currentDate = *currentItr;
        if (currentDate < newDate) {
            repetitionDates.insert(currentItr, newDate);
            inserted = true;

        } else {
            currentItr++;
        }

    }

    if (!inserted) {
        repetitionDates.push_back(newDate);
    }

    return inserted;
}

rep_date Subject::removeRepetitionDate(int idx) {
    //TODO: throws out_of_range exception
    auto targetItr = repetitionDates.begin() + idx;
    rep_date removed = repetitionDates[idx];
    repetitionDates.erase(repetitionDates.begin() + idx);
    return removed;
}
using namespace date;

string Subject::asString() const {
    stringstream output;
    output << name;

    for (const auto &repDate: repetitionDates) {
        output << " -> ";
        output << date::format("%d/%m/%y", repDate);
    }

    return output.str();
}
