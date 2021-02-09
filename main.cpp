#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include <chrono>
#include <sstream>
#include <array>
// N is vector length, q is size of alphabet
//Note: these are predefined const expressions to enable compile-tine optimizations
constexpr unsigned int N = 5, q = 2;

using vector_t = std::array<unsigned char, N>;


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

unsigned int Vector::get_number_of_runs(void) {
    return numberOfRuns;
}

const std::string &Vector::get_serialized_vector(void) {
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

Vector::Vector(const std::string & vector) : serializedVector(vector) {
    int i = 0;
    for (char digit : vector) {
        this->vector[i] = digit - '0';
        ++i;
    }
    this->numberOfRuns = runs(this->vector);
}



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