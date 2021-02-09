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
void generate_vector_space(std::set<vector_t >& vector_set);

int main() {
    std::set<vector_t> vector_set;
    auto start = std::chrono::system_clock::now();
    generate_vector_space(vector_set);
    auto end = std::chrono::system_clock::now();
    assert(vector_set.size() == pow(q,N));
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Run time of vector space generation is " << diff << " seconds" << std::endl;
    return 0;
}

void generate_vector_space(std::set<vector_t>& vector_set) {
    for (int i = 0; i <= pow(q,N) - 1; ++i) {
        vector_t vec;
        int num = i;
        for (int j = N-1; j >=0; --j) {
            vec[j] = num % q;
            num /= q;
        }
        Vector v(vec);
        std::cout << "number of runs for vector " << v.get_serialized_vector() << " is " << v.get_number_of_runs() << std::endl;
        vector_set.insert(vector_set.end(), vec);
    }
}