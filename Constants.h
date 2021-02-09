//
// Created by dani9 on 09/02/2021.
//

#ifndef INC_236379_LEVENSHTEINBALLS_CONSTANTS_H
#define INC_236379_LEVENSHTEINBALLS_CONSTANTS_H
// N is vector length, q is size of alphabet
//Note: these are predefined const expressions to enable compile-tine optimizations
constexpr unsigned int N = 5, q = 2;
#include <array>
using vector_t = std::array<unsigned char, N>;
#endif //INC_236379_LEVENSHTEINBALLS_CONSTANTS_H
