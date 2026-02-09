#include <iostream>
#include <unordered_map>
#include <vector>

int mode(std::vector<int> values) {
    int mode = 0;

    std::unordered_map<int, int> count;

    int maxCount = 0;

    for (int value : values) {
        count[value]++;
        if (count[value] > maxCount) {
            maxCount = count[value];
            mode = value;
        }
    }

    for (std::pair<int, int> pair : count) {
        if (pair.first != mode && pair.second == maxCount) {
            return -1;
        }
    }

    return mode;
}

int main(void) {
    std::vector<std::vector<int>> tests = {
        { 100, 3, 3, 44, 39, 32, 15, 27, 9, 5, 20, 49, 7, 22, 49, 27, 4, 26, 39, 29, 1, 35, 38, 4, 4, 35, 20, 43, 17, 17, 5, 1, 35, 37, 2, 50, 38, 27, 39, 22, 29, 33, 37, 43, 23, 18, 24, 33, 21, 32, 26, 40, 1, 6, 2, 19, 39, 9, 11, 0, 36, 2, 47, 0, 35, 35, 7, 43, 29, 32, 19, 36, 21, 18, 18, 24, 45, 36, 21, 31, 4, 35, 38, 42, 42, 44, 3, 3, 30, 23, 5, 23, 15, 47, 14, 48, 19, 49, 22, 9, 16 },
        { 100, 42, 50, 29, 35, 18, 5, 41, 46, 38, 35, 16, 31, 6, 46, 3, 26, 3, 32, 32, 24, 36, 38, 31, 36, 15, 34, 39, 14, 10, 29, 6, 5, 25, 28, 11, 1, 32, 47, 42, 19, 29, 31, 23, 43, 42, 48, 19, 50, 14, 44, 7, 32, 23, 10, 7, 24, 13, 15, 12, 15, 1, 40, 7, 35, 41, 20, 22, 7, 4, 6, 2, 29, 19, 45, 6, 8, 49, 17, 31, 16, 4, 39, 22, 45, 1, 11, 5, 11, 45, 6, 22, 34, 45, 17, 47, 42, 48, 0, 43, 32 }
    };

    size_t i = 1;
    for (std::vector<int> test : tests) {
        std::cout << "Test: " << i << " Mode: " << mode(test) << "\n";
        i++;
    }
}
