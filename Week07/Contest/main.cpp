#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::string cat_or_dog(std::string& input) {
    char counts[26] = {0};

    for (char ch : input) {
        counts[std::toupper(ch) - 'A']++;
    }

    int cat = counts['C' - 'A'] + counts['A' - 'A'] + counts['T' - 'A'];
    int dog = counts['D' - 'A'] + counts['O' - 'A'] + counts['G' - 'A'];

    if (cat + dog == 0 || cat == dog) {
        return "NEITHER";
    } else if (cat > dog) {
        return "CAT";
    } else {
        return "DOG";
    }
}

struct cat_dog_test_t {
    std::string input;
    std::string expected;
};

void test_cat_dog() {
    std::vector<cat_dog_test_t> tests = {
        { "Dogcat", "NEITHER" },
        { "RAPIDAPPLIEDPROBLEMSOLVING", "DOG" },
        { "Antidisestablishmentarian", "CAT" },
    };

    for (cat_dog_test_t& test : tests) {
        std::cout << "\n-----------------------------------------\n";
        std::string output = cat_or_dog(test.input);
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "-----------------------------------------\n";
    }
}

int speed_camera(std::vector<std::string>& data) {
    std::unordered_map<std::string, float> times;

    const float max_time = 0.5f / 55.0f;

    std::cout << "Max diff: " << max_time << "\n";

    int tickets = 0;

    int hour, min, sec;
    for (std::string& entry : data) {
        sscanf_s(entry.data() + 8, "%d %d %d", &hour, &min, &sec);
        float time = hour + (min / 60.0f) + (sec / 3600.0f);
        std::string reg = entry.substr(0, 7);

        if (!times.count(reg)) {
            times[reg] = time;
        } else {
            if (time - times[reg] < max_time) {
                tickets++;
            }
        }
    }

    return tickets;
}

struct camera_test_t {
    std::vector<std::string> input;
    int expected;
};

void test_speed_camera() {
    std::vector<camera_test_t> tests = {
        camera_test_t {
            .input = {
                "SL69DSW 11 2 48",
                "GF73AXG 11 3 0",
                "EV11CMB 11 3 9",
                "YN21UXF 11 3 10",
                "FH64BTT 11 3 16",
                "SL69DSW 11 3 22",
                "GF73AXG 11 3 36",
                "YN21UXF 11 3 41",
                "EV11CMB 11 3 42",
                "FH64BTT 11 3 53",
            },
            .expected = 1
        }
    };

    for (camera_test_t& test : tests) {
        std::cout << "\n-----------------------------------------\n";
        int output = speed_camera(test.input);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "-----------------------------------------\n";
    }
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
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "-----------------------------------------\n";
    }
}

struct bracket_t {
    char closing = '\0';
    char opening = '\0';
    bool is_opening = false;
};

bracket_t brackets[128] = { 0 };

std::string valid_brackets(std::string& s) {
    std::vector<char> stack;
    for (char ch : s) {
        if (std::isspace(ch)) { continue; }
        if (brackets[ch].is_opening) {
            stack.push_back(ch);
        } else if (!stack.empty()) {
            char popped = stack.back();
            if (popped != brackets[ch].opening) {
                return "INVALID";
            } else {
                stack.pop_back();
            }
        } else {
            return "INVALID";
        }
    }

    return stack.empty() ? "VALID" : "INVALID";
}

struct brackets_test_t {
    std::string input;
    std::string expected;
};

void test_brackets() {
    char chs[] = { '[', ']', '{', '}', '(', ')' };

    for (size_t i = 0; i < 6; i += 2) {
        brackets[chs[i]].closing = chs[i + 1];
        brackets[chs[i]].is_opening = true;
        brackets[chs[i + 1]].opening = chs[i];
    }

    std::vector<brackets_test_t> tests = {
        brackets_test_t {
            .input = "{()}",
            .expected = "VALID",
        },
        brackets_test_t {
            .input = "]]()",
            .expected = "INVALID",
        },
        brackets_test_t {
            .input = "{{}{}[]}",
            .expected = "VALID",
        },
        brackets_test_t {
            .input = "(([{}]))",
            .expected = "VALID",
        }
    };


    for (brackets_test_t& test : tests) {
        std::cout << "\n-----------------------------------------\n";
        std::string output = valid_brackets(test.input);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "-----------------------------------------\n";
    }
}


int main(void) {
    test_brackets();
}
