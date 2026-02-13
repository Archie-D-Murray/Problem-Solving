#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
class Solution {
public:
    int titleToNumber(std::string& columnTitle) {
        int number = 0;

        for (size_t i = 0; i < columnTitle.size(); i++) {
            number *= 26;
            number += (columnTitle[i] - ('A') + 1);
        }

        return number;
    }

    std::string binaryAddition(std::string& A, std::string& B) {
        std::string* longer = &A;
        std::string* shorter = &B;

        if (A.size() < B.size()) {
            longer = &B;
            shorter = &A;
        }

        std::string output;
        output.resize(longer->size() + 1);

        const int base = 2;
        const char ref = '0';

        int carry = 0;
        size_t index = output.size() - 1;
        for (size_t i = 1; i <= longer->size(); i++) {
            char longerChar = (*longer)[longer->size() - i]; 
            int shorterChar = shorter->size() - i < shorter->size() ? (*shorter)[shorter->size() - i] - ref : 0;
            int value = longerChar - ref + shorterChar + carry;


            output[index] = ref + (value % base);
            if (value >= base) {
                carry = value / base;
            } else {
                carry = 0;
            }
            index--;
        }
        if (carry > 0) {
            output[index] = ref + carry;
        } else {
            output.erase(output.begin(), std::find_if(output.begin(), output.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
        }

        return output;
    }

    void sortColours(std::vector<int>& nums) {
        std::unordered_map<int, size_t> mapped;

        for (int num : nums) {
            mapped[num]++;
        }

        int offset = 0;
        for (int i = 0; i <= 2; i++) {
            memset(nums.data() + offset * sizeof(int), i, mapped[i]);
            offset += nums[i];
        }
    }
};

int main(void) {
    std::vector<std::vector<int>> tests = {
        { 2, 1, 2, 0, 0, 0, 1 },
        { 1, 0, 1, 2, 1, 0, 2 },
    };

    Solution solution;

    for (std::vector<int> test : tests) {
        std::cout << "Inputs: [ ";
        size_t i = 0;
        for (int num : test) {
            std::cout << num << (i < (test.size() - 1) ? ", " : " ");
            i++;
        }
        std::cout << "]";
        solution.sortColours(test);
        std::cout << "Outputs: [ ";
        i = 0;
        for (int num : test) {
            std::cout << num << (i < (test.size() - 1) ? ", " : " ");
            i++;
        }
        std::cout << "]\n";
    }
}
