#pragma once

//struct OpStats {
//    unsigned equals = 0;      // ==
//    unsigned comparisons = 0; // <, >
//    unsigned assignments = 0; // =
//
//    void Reset() {
//        equals = 0;
//        comparisons = 0;
//        assignments = 0;
//    }
//
//    OpStats operator+(const OpStats& other) const {
//        OpStats res;
//        res.equals = this->equals + other.equals;
//        res.comparisons = this->comparisons + other.comparisons;
//        res.assignments = this->assignments + other.assignments;
//        return res;
//    }
//
//    OpStats& operator+=(const OpStats& other) {
//        this->equals += other.equals;
//        this->comparisons += other.comparisons;
//        this->assignments += other.assignments;
//        return *this;
//    }
//};

struct OpStats {
    unsigned total = 0;

    void Reset() {
        total = 0;
    }

    void operator++(int) {
        total++;
    }

    void add(unsigned count) {
        total += count;
    }

    OpStats operator+(const OpStats& other) const {
        return { total + other.total };
    }

    OpStats& operator+=(const OpStats& other) {
        this->total += other.total;
        return *this;
    }
};