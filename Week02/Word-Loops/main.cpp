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

void string_loop(std::vector<std::string>& strings) {
    for (size_t i = 0; i < strings.size(); i++) {
        if (hamming_distance(strings[i], strings[(i + 1) % strings.size()]) != 1) {
            std::cout << "False\n";
            return;
        }
    }

    std::cout << "True\n";
}

int main(void) {
    std::vector<std::vector<std::string>> tests = {
        { "MATE", "MALE", "PALE", "PATE" },
        { "ABCD", "ABCE", "ABCF", "AAAA" },
    };

    for (std::vector<std::string>& test : tests) {
        string_loop(test);
    }
}
