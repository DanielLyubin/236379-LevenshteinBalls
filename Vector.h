//
// Created by dani9 on 09/02/2021.
//

#ifndef INC_236379_LEVENSHTEINBALLS_VECTOR_H
#define INC_236379_LEVENSHTEINBALLS_VECTOR_H

#include "Constants.h"

class Vector {
public:
    Vector(const vector_t&);
    Vector(const std::string&);
    const std::string& get_serialized_vector(void);
    unsigned int get_number_of_runs(void);
private:
    // This function returns the number of runs in the vector
    // For example, the function will return 5 for the 5-length binary vector '10101'
    static unsigned int runs(const vector_t& vector);

    vector_t vector;
    std::string serializedVector;
    unsigned int numberOfRuns;
};


#endif //INC_236379_LEVENSHTEINBALLS_VECTOR_H
