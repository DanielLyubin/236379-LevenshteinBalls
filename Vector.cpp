//
// Created by dani9 on 09/02/2021.
//

#include "Vector.h"
#include <sstream>
Vector::Vector(const vector_t & vector) : vector(vector) {
    numberOfRuns = runs(vector);
    std::stringstream ss;
    for (auto it = this->vector.begin(); it != this->vector.end(); ++it) {
        char symbolAsChar[2] = {0,0};
        itoa(*it, symbolAsChar, 10);
        ss << symbolAsChar;
    }
    ss >> this->serializedVector;
}

Vector::Vector(const std::string & vector) : serializedVector(vector) {
    int i = 0;
    for (char digit : vector) {
        this->vector[i] = digit - '0';
        ++i;
    }
    this->numberOfRuns = runs(this->vector);
}

unsigned int Vector::get_number_of_runs() {
    return numberOfRuns;
}

const std::string &Vector::get_serialized_vector() {
    return serializedVector;
}

unsigned int Vector::runs(const vector_t& vector) {
    unsigned int runs = 0;
    auto it = vector.begin();
    auto last_symbol = *it;
    ++runs;
    for (; it != vector.end(); ++it) {
        if (*it != last_symbol) {
            last_symbol = *it;
            ++runs;
        }
    }
    return runs;
}
