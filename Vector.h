//
// Created by dani9 on 09/02/2021.
//

#ifndef INC_236379_LEVENSHTEINBALLS_VECTOR_H
#define INC_236379_LEVENSHTEINBALLS_VECTOR_H

#include <vector>
#include <ostream>
#include "Constants.h"

class Vector {
public:
    explicit Vector(const vector_t&);
    explicit Vector(const std::string&);
    Vector(const Vector& other) = default;
    Vector(Vector&& o) = default;
    const std::string& get_serialized_vector() const;
    unsigned int get_number_of_runs() const;
    unsigned int get_l_ball_size() const;
    unsigned int get_levenshtein_ball_size() const;

    bool operator==(const Vector &rhs) const;

    bool operator!=(const Vector &rhs) const;

    bool operator<(const Vector &rhs) const;

    bool operator>(const Vector &rhs) const;

    bool operator<=(const Vector &rhs) const;

    bool operator>=(const Vector &rhs) const;

    Vector& operator=(const Vector& o) = default;

    Vector& operator=(Vector&& o) = default;

    virtual ~Vector() = default;

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

private:
    // This function calculates the number of runs in the vector and stores it in numberOfRuns
    // For example, the function will store the value 5 for the 5-length binary vector '10101'
    void calculate_number_of_runs();

    // This function calculates the number of maximal alternating segments and their lengths and stores it in
    // alternatingSegmentsLengths
    void calculate_alternating_segments();

    // This function calculates the l ball size of the vector and stores it in lBallSize
    void calculate_l_ball_size();

    void calculate_levenshtein_ball_size();
    vector_t vector;
    std::vector<unsigned char> alternatingSegmentsLengths;
    unsigned int lBallSize;
    unsigned int levenshteinBallSize;
    std::string serializedVector;
    unsigned int numberOfRuns;
};


#endif //INC_236379_LEVENSHTEINBALLS_VECTOR_H
