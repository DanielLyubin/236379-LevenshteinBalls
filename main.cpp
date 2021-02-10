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
unsigned int find_maximal_l_ball_size(int lowBound, int upperBound);
void find_vectors_with_max_l_ball_size(std::set<Vector>& vector_set,int lowBound, int upperBound);
unsigned max_l_ball_in_vector_space = 0;

int main() {
    int power_of_N = static_cast<int>(pow(q,N));
    int ranges[] = {0, power_of_N / 4,power_of_N / 2, (3 *power_of_N) / 4, power_of_N };
    std::set<Vector> max_vector_set;
    // find maximum of l-ball
    for (int i = 1; i < 5; ++i) {
        auto start = std::chrono::system_clock::now();
        auto res = find_maximal_l_ball_size(ranges[i-1],ranges[i]);
        if (res > max_l_ball_in_vector_space)
            max_l_ball_in_vector_space = res;
        auto end = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        std::cout << "Run time of range traversal " << diff << " seconds" << std::endl;
    }
    std::cout << "maximal l ball size is " << max_l_ball_in_vector_space << std::endl;
    for (int i = 1; i < 5; ++i) {
        find_vectors_with_max_l_ball_size(max_vector_set, ranges[i-1],ranges[i]);
    }
    std::cout << "number of vectors having max l ball size is " << max_vector_set.size() << std::endl;
    for (const Vector& vector : max_vector_set) {
        std::cout << vector << std::endl;
    }
    return 0;
}

unsigned int find_maximal_l_ball_size(int lowBound, int upperBound) {
    int max = 0;
    for (int i = lowBound; i <= upperBound - 1; ++i) {
        vector_t vec;
        int num = i;
        for (int j = N-1; j >=0; --j) {
            vec[j] = num % q;
            num /= q;
        }
        Vector v(vec);
#if (VERBOSE == 1)
        std::cout << v <<std::endl;
#endif
        if (v.get_l_ball_size() > max)
            max = v.get_l_ball_size();
    }
    return max;
}

void find_vectors_with_max_l_ball_size(std::set<Vector>& vector_set,int lowBound, int upperBound) {
    for (int i = lowBound; i <= upperBound - 1; ++i) {
        vector_t vec;
        int num = i;
        for (int j = N-1; j >=0; --j) {
            vec[j] = num % q;
            num /= q;
        }
        Vector v(vec);
#if (VERBOSE == 1)
        std::cout << v <<std::endl;
#endif
        if (v.get_l_ball_size() == max_l_ball_in_vector_space)
            vector_set.insert(vector_set.end(), v);
    }
}