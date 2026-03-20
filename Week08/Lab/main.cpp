#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct ivec2 {
    int x;
    int y;

};

bool operator==(const ivec2& s, const ivec2& o) {
    return (s.x == o.x) && (s.y == o.y);
}

template<> struct std::hash<ivec2> {
    std::size_t operator() (const ivec2& vec) const noexcept {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};

const char* bool_to_str(bool value) {
    return value ? "True" : "False";
}

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

std::vector<std::vector<int>> pascal_triangle(int rows) {
    std::vector<std::vector<int>> triangle = std::vector<std::vector<int>>(0);
    for (int i = 0; i < rows; i++) {
        triangle.push_back(std::vector<int>(0));
        triangle.back().reserve(i + 1);
    }

    for (int i = 1; i < rows; i++) {
        for (int c = 0; c <= i; c++) {
            if (c == 0 || c == i) {
                triangle[i].push_back(1);
            } else {
                triangle[i].push_back(triangle[i - 1][c - 1] + triangle[i - 1][c]);
            }
        }
    }

    return triangle;
}

struct pascal_test_t {
    std::vector<std::vector<int>> expected;
    int rows;
};

void test_pascal_triangle(void) {
    std::vector<pascal_test_t> tests = {
        pascal_test_t {
            .expected = { 
                {       1,        },
                {      1, 1,      },
                {    1, 2, 1,     },
                {   1, 3, 3, 1,   },
                { 1, 4, 6, 4, 1,  },
            },
            .rows = 5
        },
    };

    for (pascal_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        std::vector<std::vector<int>> output = pascal_triangle(test.rows);
        std::cout << "Input: " << test.rows << "\n";
        bool match = output.size() == test.expected.size();

        for (size_t i = 0; i < test.expected.size() && match; i++) {
            match = output[i] == test.expected[i];
        }

        std::cout << "Output:\n";
        for (size_t i = 0; i < test.rows; i++) {
            for (size_t pad = 0; pad < test.rows - i; pad++) {
                std::cout << " ";
            }

            for (size_t j = 0; j < output[i].size(); j++) {
                std::cout << output[i][j] << " ";
            }
            std::cout << "\n";
        }

        std::cout << "Expected:\n";
        for (size_t i = 0; i < test.rows; i++) {
            for (size_t pad = 0; pad < test.rows - i; pad++) {
                std::cout << " ";
            }

            for (size_t j = 0; j < output[i].size(); j++) {
                std::cout << output[i][j] << " ";
            }
            std::cout << "\n";
        }

        std::cout << "Match: " << bool_to_str(match) << "\n";
        std::cout << "-------------------------------\n";
    }
}

static std::string chars[8] = {
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
};

void letter_driver(std::vector<std::string>& combinations, std::string& digits, size_t index, std::string& current) {
    if (index == digits.size()) {
        combinations.push_back(current);
        return;
    }

    for (char ch : chars[digits[index] - '2']) {
        current.push_back(ch);
        letter_driver(combinations, digits, index + 1, current);
        current.pop_back();
    }
}

std::vector<std::string> letter_combos(std::string& digits) {
    std::vector<std::string> combos;

    std::string current = "";
    letter_driver(combos, digits, 0, current);

    return combos;
}

struct letter_combo_test_t {
    std::string input;
    std::vector<std::string> expected;
};

void test_letter_combo(void) {
    std::vector<letter_combo_test_t> tests = {
        letter_combo_test_t {
            .input = "23",
            .expected = {"ad","ae","af","bd","be","bf","cd","ce","cf"}
        },
        letter_combo_test_t {
            .input = "2",
            .expected = {"a","b","c"}
        },
    };

    for (letter_combo_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        std::vector<std::string> output = letter_combos(test.input);
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   ";
        print_vector(output);
        std::cout << "Expected: ";
        print_vector(test.expected);
        std::cout << "Match: " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

int decode_driver(std::string& s, size_t i, std::vector<int>& memo) {
    if (memo[i] > -1) {
        return memo[i];
    }

    if (s[i] == '0') {
        memo[i] = 0;
        return 0;
    }

    int result = decode_driver(s, i + 1, memo); // No pair value

    if (i < s.size() - 1 && (s[i] == '1' || s[i] == '2' && s[i + 1] < '7')) {
        result += decode_driver(s, i + 2, memo);
    }
    memo[i] = result;
    return result;
}

int num_decodings(std::string& s) {
    int ways = 1;
    std::vector<int> memo = std::vector<int>(s.size() + 1, -1);

    memo[s.size()] = 1;
    return s.size() ? decode_driver(s, 0, memo) : 0;
}

struct num_decodings_test_t {
    std::string input;
    int expected;
};

void test_num_decodings(void) {
    std::vector<num_decodings_test_t> tests = {
        num_decodings_test_t {
            .input = "12",
            .expected = 2
        },
        num_decodings_test_t {
            .input = "226",
            .expected = 3
        },
    };

    for (num_decodings_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        int output = num_decodings(test.input);
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match: " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

int coin_change(int n, std::vector<int>& c) {
    return {};
}

struct coin_change_test_t {
    int amount;
    std::vector<int> denominations;
    int expected;
};

void test_coin_change(void) {
    std::vector<coin_change_test_t> tests = {
        coin_change_test_t {
            .amount = 4,
            .denominations = { 1, 2, 3 },
            .expected = 4,
        },
        coin_change_test_t {
            .amount = 10,
            .denominations = { 2, 5, 3, 6 },
            .expected = 5,
        },
    };

    for (coin_change_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        int output = coin_change(test.amount, test.denominations);
        std::cout << "Input:    " << test.amount << ", ";
        std::cout << "Denominations: ";
        print_vector(test.denominations);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

int main(void) {
    test_num_decodings();
    
}
