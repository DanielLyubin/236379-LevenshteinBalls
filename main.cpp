#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include <chrono>

// N is vector length, q is size of alphabet
//Note: these are predefined const expressions to enable compile-tine optimizations
constexpr unsigned int N = 15, q = 3;

// This function generates the vector space according to the vector length and alphabet
/*TODO: Isn't it better to analyze vectors when creating them? Generating the space and then iterating on it will take
 * Twice the time
*/
void generate_vector_space(std::set<std::vector<unsigned char>>& vector_set);

int main() {
    std::set<std::vector<unsigned char>> vector_set;
    auto start = std::chrono::system_clock::now();
    generate_vector_space(vector_set);
    auto end = std::chrono::system_clock::now();
    assert(vector_set.size() == pow(q,N));
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    std::cout << "Run time of vector space generation is " << diff << " seconds" << std::endl;
    return 0;
}

void generate_vector_space(std::set<std::vector<unsigned char>>& vector_set) {
    for (int i = 0; i <= pow(q,N) - 1; ++i) {
        std::vector<unsigned char> vec;
        int num = i;
        for (int j = 0; j < N; j++) {
            vec.insert(vec.begin(),num % q);
            num /= q;
        }
        vector_set.insert(vector_set.end(), vec);
    }
}
