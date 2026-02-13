#include <string>
#include <vector>
#include <iostream>

template<typename T> void print_vector(std::vector<T> vector, bool new_line = true) {
    std::cout << "[ ";
    size_t i = 0;
    for (size_t i = 0; i < vector.size(); i++) {
        if (i < vector.size() - 1) {
            std::cout << vector[i] << ", ";
        } else {
            std::cout << vector[i] << " ]";
        }
    }
    if (new_line) {
        std::cout << "\n";
    }
}

class Solution {
public:
    std::vector<std::string> findWords(std::vector<std::string>& words) {
        
    }

    std::vector<int> majorityElement(std::vector<int>& nums) {
        
    }

    int salesMerchant(std::vector<int>& nums) {

    }

    int sherlockAnagrams(std::string& s) {

    }
};

void find_words(Solution& solution) {
    std::vector<std::vector<std::string>> tests = {
        { "hello","alaska","dad","peace" },
        { "omk" },
        { "adsdf","sfd" }
    };

    for (std::vector<std::string>& test : tests) {
        std::cout << "Inputs: ";
        print_vector(test);
        std::vector<std::string> output = solution.findWords(test);
        std::cout << "Output: ";
        print_vector(output);
    }
}

void majority_element(Solution& solution) {
    std::vector<std::vector<int>> tests = {
        { 3,2,3 },
        { 1 },
        { 1,2 }
    };

    for (std::vector<int>& test : tests) {
        std::cout << "Inputs: ";
        print_vector(test);
        std::vector<int> output = solution.majorityElement(test);
        std::cout << "Output: ";
        print_vector(output);
    }
}

void sales_merchant(Solution& solution) {
    std::vector<std::vector<int>> tests = {
        { 1, 2, 1, 2, 1, 3, 2 }, // 2
        { 10, 20, 20, 10, 10, 30, 50, 10, 20 }, // 3
    };

    for (std::vector<int>& test : tests) {
        std::cout << "Inputs: ";
        print_vector(test);
        int output = solution.salesMerchant(test);
        std::cout << "Output: " << output << "\n";
    }
}

void sherlock_anagrams(Solution& solution) {
    std::vector<std::vector<std::string>> tests = { 
        { "abba", "abcd" },
        { "ifailuhkqq", "kkkk" },
        { "cdcd" },
    };

    for (std::vector<std::string>& test : tests) {
        std::cout << "Inputs: ";
        print_vector(test);

        for (std::string& str : test) {
            std::cout << "Input: " << str << "\n";
            int output = solution.sherlockAnagrams(str);
            std::cout << "Output: " << output << "\n";
        }
    }
}

int main(void) {
    Solution solution;

    // find_words(solution);
    // majority_element(solution);
    // sales_merchant(solution);
    // sherlock_anagrams(solution);
}
