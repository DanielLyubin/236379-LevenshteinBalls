//
// Created by dani9 on 09/02/2021.
//

#ifndef INC_236379_LEVENSHTEINBALLS_CONSTANTS_H
#define INC_236379_LEVENSHTEINBALLS_CONSTANTS_H
// N is vector length, q is size of alphabet
//Note: these are predefined const expressions to enable compile-tine optimizations
constexpr unsigned int q = 2;
/*constexpr unsigned int maximal_l_ball_size_non_binary = N * N * (q - 1) - N + 2; // relevant for q >= 3
constexpr unsigned int l_ball_size_binary_alternating = N * N  - N + 2 - ((N - 1) * (N - 2)) / 2; // relevant for q >= 3*/
#include <array>
using vector_t = std::vector<unsigned char>;
#endif //INC_236379_LEVENSHTEINBALLS_CONSTANTS_H
