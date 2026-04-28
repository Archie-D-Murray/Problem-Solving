#include <iostream>
#include <string>
#include <vector>

const char* bool_to_str(bool value) {
    return value ? "True" : "False";
}

int split_count(std::string& str, size_t start, size_t length) {
    // Base case: length 1 -> must be valid partition, cannot split further
    if (length == 1) { return 1; }
    char min = 10;
    char max = 0;
    // Iterate through a partition using start point + length - no copy
    for (size_t i = start; i < start + length; i++) {
        if (str[i] - '0' < min) {
            min = str[i] - '0';
        }
        if (str[i] - '0' > max) {
            max = str[i] - '0';
        }
        // If max and min differ by more than 1, then the partition contains characters with more than 1 value difference
        if (max - min > 1) {
            return split_count(str, start, length / 2) + split_count(str, start + length / 2, length / 2); // Add two partitions
        }
    }
    // Base case: Paritioning complete
    return 1;
}

int split_count_no_subtraction(std::string& str, size_t start, size_t length) {
    if (length == 1) { return 1; }
    char min = '0' + 10; // No need for `- '0'` everywhere
    char max = '0';
    for (size_t i = start; i < start + length; i++) {
        if (str[i] < min) {
            min = str[i];
        }
        if (str[i] > max) {
            max = str[i];
        }
        if (max - min > 1) {
            return split_count(str, start, length / 2) + split_count(str, start + length / 2, length / 2);
        }
    }
    return 1;
}

struct split_test_t {
    std::string input;
    int expected;
};

void test_split_count() {
    std::vector<split_test_t> tests = {
        split_test_t {
            .input = "11112222",
            .expected = 1,
        },
        split_test_t {
            .input = "12123434",
            .expected = 2,
        },
        split_test_t {
            .input = "64444444",
            .expected = 4,
        },
    };

    for (split_test_t& test : tests) {
        std::cout << "\n---------------------------\n";
        int output = split_count(test.input, 0, test.input.size());
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   " << (output) << "\n";
        std::cout << "Expected: " << (test.expected) << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "---------------------------\n";
    }
}

int main(void) {
    test_split_count();
}
