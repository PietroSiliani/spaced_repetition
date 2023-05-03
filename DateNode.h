//
// Created by pietr on 19/04/2023.
//

#ifndef SPACED_REPETITION_DATENODE_H
#define SPACED_REPETITION_DATENODE_H
#include <chrono>
#include <memory>

using namespace std;

class DateNode {

public:
    explicit DateNode(chrono::system_clock::time_point d, DateNode* n = nullptr) {
        date = d;
    }

    [[nodiscard]] const chrono::system_clock::time_point &getDate() const {
        return date;
    }

    void setDate(const chrono::system_clock::time_point &d) {
        this->date = d;
    }

private:
    chrono::system_clock::time_point date;

};


#endif //SPACED_REPETITION_DATENODE_H
