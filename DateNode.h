//
// Created by pietr on 19/04/2023.
//

#ifndef SPACED_REPETITION_DATENODE_H
#define SPACED_REPETITION_DATENODE_H
#include <chrono>
#include <memory>

using namespace std;

class DateNode {
    //TODO: idea: each DateNode holds a pointer to the next DateNode

public:
    explicit DateNode(chrono::system_clock::time_point d, DateNode* n = nullptr) {
        date = d;
        next = shared_ptr<DateNode>(n);
    }

    [[nodiscard]] const chrono::system_clock::time_point &getDate() const {
        return date;
    }

    void setDate(const chrono::system_clock::time_point &d) {
        this->date = d;
    }

    [[nodiscard]] const shared_ptr<DateNode> &getNext() const {
        return next;
    }

    shared_ptr<DateNode> resetNext(DateNode* n) {
        //TODO: unsure of this
        auto old = shared_ptr<DateNode>(next);
        next.reset(n);
        return old;
    }

private:
    chrono::system_clock::time_point date;
    shared_ptr<DateNode> next; //TODO: try unique_ptr

};


#endif //SPACED_REPETITION_DATENODE_H
