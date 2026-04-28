#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

const char* bool_to_str(bool value) {
    return value ? "True" : "False";
}

std::string valid_sudoku_bits(std::string& s) {
    int16_t valid = 0;

    const size_t offset = '1';

    for (size_t i = 0; i < 9; i++) {

        for (size_t x = 0; x < 9; x++) {
            if (valid & (1 << (s[i * 9 + x] - offset))) {
                return "INVALID";
            } else {
                valid |= 1 << (s[i * 9 + x] - offset);
            }
        }

        valid = 0;

        for (size_t y = 0; y < 9; y++) {
            if (valid & (1 << (s[y * 9 + i] - offset))) {
                return "INVALID";
            } else {
                valid |= 1 << (s[y * 9 + i] - offset);
            }
        }

        valid = 0;


        for (size_t y = 0; y < 3; y++) {
            size_t start_y = (i / 3) * 27;
            for (size_t x = 0; x < 3; x++) {
                size_t index = start_y + (y * 9) + (i % 3) * 3 + x;
                if (valid & (1 << (s[index] - offset))) {
                    return "INVALID";
                } else {
                    valid |= 1 << (s[index] - offset);
                }
            }
        }

        valid = 0;
    }

    return "VALID";
}

std::string valid_sudoku(std::string& s) {
    bool valid[9] = {0};

    size_t offset = '1';

    for (size_t i = 0; i < 9; i++) {

        for (size_t x = 0; x < 9; x++) {
            if (valid[s[i * 9 + x] - offset]) {
                return "INVALID";
            } else {
                valid[s[i * 9 + x] - offset] = true;
            }
        }

        memset(valid, 0, sizeof(bool) * 9);

        for (size_t y = 0; y < 9; y++) {
            if (valid[s[y * 9 + i] - offset]) {
                return "INVALID";
            } else {
                valid[s[y * 9 + i] - offset] = true;
            }
        }

        memset(valid, 0, sizeof(bool) * 9);


        for (size_t y = 0; y < 3; y++) {
            size_t start_y = (i / 3) * 27;
            for (size_t x = 0; x < 3; x++) {
                size_t index = start_y + (y * 9) + (i % 3) * 3 + x;
                if (valid[s[index] - offset]) {
                    return "INVALID";
                } else {
                    valid[s[index] - offset] = true;
                }
            }
        }

        memset(valid, 0, sizeof(bool) * 9);
    }

    return "VALID";
}

struct sudoku_test_t {
    std::string grid;
    std::string expected;
};

void test_sudoku() {
    std::vector<sudoku_test_t> tests = {
        sudoku_test_t {
            .grid = "524361897631798254789542316143827965952416738876935142418679523265183479397254681",
            .expected = "VALID"
        },
        sudoku_test_t {
            .grid = "185436927976582143342719685263174598451928376897653412524861739639247851718395264",
            .expected = "VALID"
        },
        sudoku_test_t {
            .grid = "853194628674532891192876345437621589961358472285947163748215936316789254529463717",
            .expected = "INVALID"
        },
    };

    for (sudoku_test_t& test : tests) {
        std::cout << "\n-----------------------------------------\n";
        std::string output = valid_sudoku_bits(test.grid);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-----------------------------------------\n";
    }
}
