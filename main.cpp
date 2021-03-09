#include <iostream>
#include <cmath>
#include <set>
#include <cassert>
#include <chrono>
#include "Vector.h"

// This function generates the vector space according to the vector length and alphabet
/*TODO: Isn't it better to analyze vectors when creating them? Generating the space and then iterating on it will take
 * Twice the time
*/
void find_maximal_balls_size(unsigned int N, int lowBound, int upperBound, unsigned int& l_ball, unsigned int& levenshtein_ball);
void find_vectors_with_max_levenshtein_ball_size(unsigned int N, std::set<Vector>& vector_set,int lowBound, int upperBound);
unsigned max_levenshtein_ball_in_vector_space = 0,max_l_ball_in_vector_space = 0;
int lower_bound = 0, upper_bound = 0;
int main() {
    for (unsigned int n = 1; n <=19; ++n) {
        max_levenshtein_ball_in_vector_space = 0;
        max_l_ball_in_vector_space = 0;
        lower_bound = 0;
        upper_bound = 0;
        std::cout << "******** N = " << n << " *********" << std::endl;

        // Calculating max of group T(n) from papers
        double calc = 0.5 * sqrt(1 + 2 * n);
        auto t1 = static_cast<unsigned int>(round(calc));
        auto lengthOfBalancedSequences = static_cast<unsigned int>(floor(static_cast<double>(n) / t1));
        unsigned int prefix = 0;
        for (int i = 0; i < lengthOfBalancedSequences; ++i) {
            prefix <<= 1;
            if (i % 2 == 0)
                ++prefix;
        }
        lower_bound = prefix << (n - lengthOfBalancedSequences);
        std::cout << lower_bound;
        upper_bound = (prefix << (n - lengthOfBalancedSequences)) +
                      static_cast<unsigned int>(pow(2, n - lengthOfBalancedSequences) - 1);
        std::cout << ", " << upper_bound << std::endl;
        int ranges[] = {lower_bound, upper_bound};
        std::set<Vector> max_vector_set;
        // find maximum of l-ball

        auto start = std::chrono::system_clock::now();
        unsigned int l_ball, levenshtein_ball;
        find_maximal_balls_size(n,lower_bound, upper_bound, l_ball, levenshtein_ball);
        if (levenshtein_ball > max_levenshtein_ball_in_vector_space)
            max_levenshtein_ball_in_vector_space = levenshtein_ball;
        if (l_ball > max_l_ball_in_vector_space)
            max_l_ball_in_vector_space = l_ball;
        auto end = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        std::cout << "Run time of range traversal " << diff << " seconds" << std::endl;

        std::cout << "maximal levenshtein ball size is " << max_levenshtein_ball_in_vector_space << std::endl;
        std::cout << "max l ball size is " << max_l_ball_in_vector_space << std::endl;
        find_vectors_with_max_levenshtein_ball_size(n,max_vector_set, lower_bound, upper_bound);
        std::cout << "number of vectors having max levenshtein ball size is " << max_vector_set.size() << std::endl;
        for (const Vector &vector : max_vector_set) {
            std::cout << vector << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
    return 0;
}

void find_maximal_balls_size(unsigned int N,int lowBound, int upperBound, unsigned int& l_ball, unsigned int& levenshtein_ball) {
    unsigned int max_l_ball = 0, max_levenshtein_ball = 0;
    for (int i = lowBound; i <= upperBound - 1; ++i) {
        vector_t vec;
        int num = i;
        for (int j = N-1; j >=0; --j) {
            vec.insert(vec.begin(),num % q);
            num /= q;
        }
        Vector v(vec);
#if (VERBOSE == 1)
        std::cout << v <<std::endl;
#endif
        if (v.get_levenshtein_ball_size() > max_levenshtein_ball)
            max_levenshtein_ball = v.get_levenshtein_ball_size();
        if (v.get_l_ball_size() > max_l_ball)
            max_l_ball = v.get_l_ball_size();
    }

    l_ball = max_l_ball;
    levenshtein_ball = max_levenshtein_ball;
}

void find_vectors_with_max_levenshtein_ball_size(unsigned int N,std::set<Vector>& vector_set,int lowBound, int upperBound) {
    for (int i = lowBound; i <= upperBound - 1; ++i) {
        vector_t vec;
        int num = i;
        for (int j = N-1; j >=0; --j) {
            vec.insert(vec.begin(),num % q);
            num /= q;
        }
        Vector v(vec);
#if (VERBOSE == 1)
        std::cout << v <<std::endl;
#endif
        if (v.get_levenshtein_ball_size() == max_levenshtein_ball_in_vector_space)
            vector_set.insert(vector_set.end(), v);
    }
}