#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int hamming_distance(std::string& A, std::string& B) {

    int count = 0;
    for (size_t i  = 0; i < std::min(A.size(), B.size()); i++) {
        if (A[i] != B[i]) {
            count++;
        }
    }

    count += abs((int) (A.size() - B.size()));

    return count;
}

int main(void) {
    std::vector<std::pair<std::string, std::string>> tests = {
        {"a", "aaaa"},
        { "abcde", "abcdf" }
    };

    for (std::pair<std::string, std::string>& test : tests) {
        std::cout << "First: " << test.first << " Second: " << test.second << " Distance: " << hamming_distance(test.first, test.second) << "\n";
    }
}
