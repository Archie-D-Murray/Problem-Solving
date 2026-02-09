

#include <iostream>
#include <vector>

int operations(int A, int B) {
    int count = 0;

    int current = A;

    while (current < B) {
        if (current * A <= B) {
            current *= A;
            count++;
            continue;
        }

        if (current + A <= B) {
            current += A;
            count++;
            continue;
        }

        current++;
        count++;
    }

    return count;
}

int main(void) {
    std::vector<std::pair<int, int>> tests = {
        { 7, 85 }, // 7
        { 74, 3531 } // 99
    };

    for (std::pair<int, int>& test : tests) {
        std::cout << "Input: " << test.first << " Target: " << test.second << " Count: " << operations(test.first, test.second) << "\n";
    }

    return 0;
}
