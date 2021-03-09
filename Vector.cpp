//
// Created by dani9 on 09/02/2021.
//

#include "Vector.h"
#include <sstream>
#include <set>
#include <iostream>

Vector::Vector(const vector_t & vector) : vector(vector), alternatingSegmentsLengths(), lBallSize(),levenshteinBallSize(), numberOfRuns() {
    std::stringstream ss;
    for (auto it = this->vector.begin(); it != this->vector.end(); ++it) {
        char symbolAsChar[2] = {0,0};
        itoa(*it, symbolAsChar, 10);
        ss << symbolAsChar;
    }
    ss >> this->serializedVector;

    calculate_l_ball_size();
    calculate_levenshtein_ball_size();
}

Vector::Vector(const std::string & vector) : serializedVector(vector), alternatingSegmentsLengths(), lBallSize(), numberOfRuns() {
    int i = 0;
    for (char digit : vector) {
        this->vector[i] = digit - '0';
        ++i;
    }
    calculate_l_ball_size();
    calculate_levenshtein_ball_size();
}

unsigned int Vector::get_number_of_runs() const {
    return numberOfRuns;
}

const std::string &Vector::get_serialized_vector() const {
    return serializedVector;
}

void Vector::calculate_number_of_runs() {
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
    this->numberOfRuns = runs;
}

void Vector::calculate_alternating_segments() {
    int i = 0,j = 0;
    unsigned int segmentLength = 0;
    char symbol1 = 0, symbol2 = 0;

    while (j < vector.size()) {
        if (segmentLength == 0) {
            symbol1 = this->vector[i];
            ++segmentLength;
            ++j;
        } else
        if (segmentLength == 1) {
            symbol2 = this->vector[j];
            if (symbol2 != symbol1) {
                ++j;
                ++segmentLength;
            }
            else {
                if ( i - 1 < 0 || this->vector[i - 1] == symbol1) {
                    this->alternatingSegmentsLengths.push_back(1);
                }
                i = j;
                segmentLength = 0;
            }
        } else
        if ((j - i) % 2 == 0) {
            if (this->vector[j] == symbol1) {
                ++segmentLength;
                ++j;
            } else {
                this->alternatingSegmentsLengths.push_back(segmentLength);
                segmentLength = 0;
                --j;
                i = j;
            }
        } else {
            if (this->vector[j] == symbol2) {
                ++segmentLength;
                ++j;
            } else {
                this->alternatingSegmentsLengths.push_back(segmentLength);
                segmentLength = 0;
                --j;
                i = j;
            }
        }
    }
    if (segmentLength > 0)
        this->alternatingSegmentsLengths.push_back(segmentLength);

}

void Vector::calculate_l_ball_size() {
    calculate_number_of_runs();
    calculate_alternating_segments();
    unsigned int sum = 0;
    for (auto segmentSize: this->alternatingSegmentsLengths) {
        sum += (segmentSize - 1) * (segmentSize - 2);
    }
    sum /= 2;
    lBallSize = numberOfRuns * (vector.size() * (q - 1) - 1) + 2 - sum;
}

unsigned int Vector::get_l_ball_size() const {
    return lBallSize;
}

bool Vector::operator==(const Vector &rhs) const {
    return serializedVector == rhs.serializedVector;
}

bool Vector::operator!=(const Vector &rhs) const {
    return !(rhs == *this);
}

bool Vector::operator<(const Vector &rhs) const {
    return serializedVector < rhs.serializedVector;
}

bool Vector::operator>(const Vector &rhs) const {
    return rhs < *this;
}

bool Vector::operator<=(const Vector &rhs) const {
    return !(rhs < *this);
}

bool Vector::operator>=(const Vector &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    os << "vector " << vector.get_serialized_vector() << " has "
        << vector.get_number_of_runs() << " runs, l ball size of "
        << vector.get_l_ball_size() << ", levenshtein ball of size " << vector.get_levenshtein_ball_size();
    return os;
}

unsigned int Vector::get_levenshtein_ball_size() const {
    return levenshteinBallSize;
}

void Vector::calculate_levenshtein_ball_size() {
    auto length = vector.size();
    unsigned int l_ball_radius_one = get_l_ball_size();
    unsigned int radius_two_i_ball = 1 + (length+2) * (q-1) + (((length+1)*(length+2))/2) * (q-1)*(q-1);
    unsigned int radius_two_d_ball = 0;
    std::set<vector_t > deletion_ball;
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {
            vector_t arr;
            for (int k = 0; k < length; ++k) {
                if (k == i || k == j)
                    continue;
                arr.push_back(this->vector[k]);
            }
            deletion_ball.insert(arr);
        }
    }
    radius_two_d_ball = deletion_ball.size();
    levenshteinBallSize = l_ball_radius_one + radius_two_d_ball + radius_two_i_ball;
}
