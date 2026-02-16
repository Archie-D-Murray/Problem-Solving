#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

template<typename T> void print_vector(std::vector<T> vector, bool new_line = true) {
    std::cout << "[ ";
    size_t i = 0;
    for (size_t i = 0; i < vector.size(); i++) {
        if (i < vector.size() - 1) {
            std::cout << vector[i] << ", ";
        } else {
            std::cout << vector[i];
        }
    }
    if (new_line) {
        std::cout << " ] \n";
    } else {
        std::cout << " ]";
    }
}

class Solution {
    std::unordered_set<char> keyboard[3];

public:

    Solution() {
        for (char ch : "qwertyuiop") {
            Solution::keyboard[0].insert(ch);
        }
        for (char ch : "asdfghjkl") {
            Solution::keyboard[1].insert(ch);
        }
        for (char ch : "zxcvbnm") {
            Solution::keyboard[2].insert(ch);
        }
    }

    std::vector<std::string> findWords(std::vector<std::string>& words) {
        std::vector<std::string> found;
        for (std::string& str : words) {
            size_t index = 0;
            for (size_t i = 0; i < 3; i++) {
                char lower = std::tolower(str[0]);
                if (Solution::keyboard[i].count(lower)) {
                    index = i;
                }
            }
            bool ok = true;
            for (char ch : str) {
                if (!Solution::keyboard[index].count(std::tolower(ch))) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                found.push_back(str);
            }
        }
        return found;
    }

    std::vector<int> majorityElement(std::vector<int>& nums) {
        std::vector<int> majority;
        std::unordered_map<int, size_t> counts;
        for (size_t i = 0; i < nums.size(); i++) {
            counts[nums[i]]++;
        }

        size_t size = nums.size() / 3;
        for (auto it = counts.begin(); it != counts.end(); it++) {
            if (it->second > size) {
                majority.push_back(it->first);
            }
        }

        return majority;
    }

    int salesMerchant(std::vector<int>& nums) {
        std::unordered_map<int, size_t> counts;
        for (int num : nums) {
            counts[num]++;
        }

        int count = 0;
        for (std::pair<int, size_t> pair : counts) {
            count += pair.second / 2;
        }

        return count;
    }

    int fact(int n) {
        int fact = 1;
        while (n > 1) {
            fact *= n;
            n--;
        }
        return fact;
    }

    int sherlockAnagrams(std::string& s) {
        std::map<std::vector<uint8_t>, size_t> counts;
        for (size_t i = 0; i < s.size(); i++) {
            for (size_t j = 1; j <= s.size() - i; j++) {
                std::vector<uint8_t> substrCharCounts = std::vector<uint8_t>(26);
                for (size_t subsstrIdx = i; subsstrIdx < i + j; subsstrIdx++) {
                    substrCharCounts[s[subsstrIdx] - 'a']++;
                }
                counts[substrCharCounts]++;
            }
        }
        // std::map<std::string, size_t> counts;
        // for (size_t i = 0; i < s.size(); i++) {
        //     for (size_t j = 1; j <= s.size() - i; j++) {
        //         std::string substrCharCounts;
        //         substrCharCounts.reserve(26);
        //         for (size_t subsstrIdx = i; subsstrIdx < i + j; subsstrIdx++) {
        //             substrCharCounts[s[subsstrIdx] - 'a']++;
        //         }
        //         counts[substrCharCounts]++;
        //     }
        // }

        int anagrams = 0;
        for (auto pair : counts) {
            anagrams += (pair.second * (pair.second - 1)) / 2;
        }

        return anagrams;
    }
};

void find_words(Solution& solution) {
    std::vector<std::vector<std::string>> tests = {
        { "hello","Alaska","Dad","peace" },
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
    sherlock_anagrams(solution);
}
