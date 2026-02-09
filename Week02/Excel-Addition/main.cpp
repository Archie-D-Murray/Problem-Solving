#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

static std::unordered_map<char, int> characterValues;

std::string excel_addition(std::string& A, std::string& B) {
    std::string* longer = &A;
    std::string* shorter = &B;

    if (A.size() < B.size()) {
        longer = &B;
        shorter = &A;
    }

    std::string output;
    output.reserve(longer->size() + 1);

    const int base = 26;

    int carry = 0;
    for (size_t i = 1; i <= longer->size(); i++) {
        char longerChar = (*longer)[longer->size() - i]; 
        int shorterChar = shorter->size() - i < shorter->size() ? characterValues[(*shorter)[shorter->size() - i]] : 0;
        int value = characterValues[longerChar] + shorterChar + carry;


        output.insert(0, 1, 'A' + (value % base));
        if (value >= base) {
            carry = value / base;
        } else {
            carry = 0;
        }
    }

    if (carry > 0) {
        output.insert(0, 1, 'A' + carry);
    }

    return output;
}

int main(void) {

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        characterValues[ch] = ch - 'A';
    }

    std::vector<std::pair<std::string, std::string>> tests = {
        { "KJLIKW", "CEPRGF"},
        { "A", "A", },
        { "B", "Z" }
    };

    for (std::pair<std::string, std::string> test : tests) {
        std::string output = excel_addition(test.first, test.second);
        std::cout << "First: " << test.first << " Second: " << test.second << " Output: " << output << "\n";
    }
}
