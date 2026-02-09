#include <iostream>
#include <unordered_set>
#include <vector>
int pairs(std::vector<int> values) {
    std::unordered_set<int> unique;

    for (int value : values) {
        unique.insert(value);
    }

    if (unique.size() <= 1) {
        return 0;
    }

    if (unique.size() == 2) {
        return 1;
    }

    return (unique.size() * (unique.size() - 1)) / 2;
}

int main(void) {
    std::vector<std::vector<int>> tests = {
        { 39, 34, 5, 39, 34, 15, 29, 17, 17, 39, 15, 29, 9, 22, 29, 43, 14, 33, 43, 5, 9, 43, 43, 29, 43, 17, 17, 5, 5, 39, 29, 9, 34, 15, 17, 27,         }, //66
        { 3 }
    };

    for (std::vector<int> test : tests) {
        std::cout << pairs(test) << "\n";
    }
}
