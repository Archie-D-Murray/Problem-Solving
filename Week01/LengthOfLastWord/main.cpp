#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int length = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (isspace(s[i])) {
                if (length == 0) {
                    continue;
                } else {
                    return length;
                }
            }
            length++;
        }

        return length;
    }

    bool isPalindrome(int x) {
        if (x < 0) { return false; }
        if (x < 10) { return true; }
        static char num[16] = {0};
        sprintf(num, "%d", x);
        size_t length = strlen(num);
        for (size_t i = 0; i < length / 2; i++) {
            if (num[i] != num[length - (i + 1)]) {
                return false;
            }
        }

        return true;
    }

    bool isPalindromeFast(int x) {
        if (x < 0) { return false; }
        if (x < 10) { return true; }

        int left = x;
        long right = 0;
        while (x > 0) {
            right = right * 10 + x % 10;
            x /= 10;
        }

        return left == right;
    }

    int maxProfit(vector<int>& prices) {
        int profit = 0;

        constexpr size_t null = size_t(-1);
        size_t current = null;
        for (size_t i = 0; i < prices.size(); i++) {
            int candidate = prices[i];

            if (current != null && i == current) {
                profit += prices[current];
                current = null;
                continue;
            }


            size_t bestSell = null;
            int candidateProfit = 0;
            for (size_t j = i + 1; j < prices.size() && j < i + 4; j++) {
                if (prices[j] > candidate && prices[j] - candidate > candidateProfit) {
                    bestSell = j;
                    candidateProfit = prices[j] - candidate;
                }

            }

            if (bestSell != null) {
                profit -= candidate;
                current = bestSell;
            }
        }

        return profit;
    }
};

void lengthTest(Solution& solution) {
    std::vector<string> tests = {
        "Hello World",
        "   fly me   to   the moon  ",
        "luffy is still joyboy"
    };

    for (const string& test : tests) {
        std::cout << "Test input: " << test << " length: " << solution.lengthOfLastWord(test) << "\n";
    }
}

void palindrome(Solution& solution) {
    std::vector<int> tests = {
        -121,
        121,
        10
    };

    for (int test : tests) {
        std::cout << "Test input: " << test << " palindrome: " << solution.isPalindromeFast(test) << "\n";
    }
} 

void profit(Solution& solution) {
    std::vector<int> tests[3] = {
        { 7,1,5,3,6,4 },
        {1,2,3,4,5},
        { 7,6,4,3,1}
    };

    for (size_t i = 0; i < 3; i++) {
        std::cout << "Input: [ ";
        for (size_t j = 0; j < tests[i].size(); j++) {
            std::cout << tests[i][j];
            if (j < tests[i].size() - 1) {
                std::cout << ", ";
            }
        }

        std::cout << " ] - Profit: " << solution.maxProfit(tests[i]) << "\n";
    }
}

int main(void) {
    Solution solution;

    profit(solution);
}

