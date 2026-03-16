#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

const char* bool_to_str(bool value) {
    return value ? "True" : "False";
}

bool ransom_note(std::string& ransomNote, std::string& magazine) {
    int used[26] = {0};
    for (size_t i = 0; i < 26; i++) {
        used[i] = -1;
    }

    for (char ch : magazine) {
        if (used[ch - 'a'] < 0) {
            used[ch - 'a'] = 1;
        } else {
            used[ch - 'a']++;
        }
    }

    for (char ch : ransomNote) {
        if (used[ch - 'a'] < 0) {
            return false;
        }

        used[ch - 'a']--;
        if (used[ch - 'a'] < 0) {
            return false;
        }
    }
    return true;
}

struct ransom_note_test_t {
    std::string ransom_note;
    std::string magazine;
    bool expected;
};

void test_ransom_note() {
    std::vector<ransom_note_test_t> tests = {
        ransom_note_test_t {
            .ransom_note = "a",
            .magazine = "b",
            .expected = false,
        },
        ransom_note_test_t {
            .ransom_note = "aa",
            .magazine = "ab",
            .expected = false,
        },
        ransom_note_test_t {
            .ransom_note = "aa",
            .magazine = "aab",
            .expected = true,
        },
    };
    for (ransom_note_test_t& test : tests) {
        std::cout << "\n-----------------------------------------\n";
        bool output = ransom_note(test.ransom_note, test.magazine);
        std::cout << "Ransom:   " << test.ransom_note << "\n";
        std::cout << "Magazine: " << test.magazine << "\n";
        std::cout << "Output:   " << bool_to_str(output) << "\n";
        std::cout << "Expected: " << bool_to_str(test.expected) << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-----------------------------------------\n";
    }
}

int64_t num_digits(int64_t num) {
    return floor(log10(num)) + 1;
}

bool is_crap_number(int64_t num) {
    if (num == 1) { return true; }
    int64_t squared = num * num;
    int64_t size = num_digits(squared);

    // std::cout << "\nInput: " << num << " Squared: " << squared << " Length: " << size << "\n";
    int64_t leftHalf = squared / pow(10, ceil(size / 2.0f)); 
    int64_t rightHalf = squared - leftHalf * pow(10, size - floor((float) size / 2));
    // std::cout << "Left: " << leftHalf << " Right: " << rightHalf << "\n";

    int64_t left = 0;
    int64_t right = 0;
    // int power = 1;
    // while (leftHalf > 0) {
    //     left += leftHalf % 10;
    //     leftHalf /= 10;
    // }
    //
    // while (rightHalf > 0) {
    //     right += rightHalf % 10;
    //     rightHalf /= 10;
    // }
    return leftHalf + rightHalf == num;
}

struct crap_number_test_t {
    int64_t start;
    int64_t end;
    std::string expected;
};

void test_crap_number() {
    std::vector<crap_number_test_t> tests = {
        crap_number_test_t {
            .start = 1,
            .end = 100,
            .expected = "1 9 45 55 99 ",
        },
        crap_number_test_t {
            .start = 1,
            .end = 99999,
            .expected = "297",
        }
    };


    for (crap_number_test_t& test : tests) {
        std::cout << "\n-----------------------------------------\n";
        std::cout << "Numbers:  " << test.start << " <- " << test.end << "\n";
        std::cout << "Found:    ";
        for (int64_t i = test.start; i <= test.end; i++) {
            if (is_crap_number(i)) {
                std::cout << i << " ";
            }
        }
        std::cout << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "-----------------------------------------\n";
    }
}

int maxProduct(std::vector<std::string>& words) {
    int product = 0;
    std::vector<uint32_t> masks = std::vector<uint32_t>(words.size());
    for (size_t i = 0; i < words.size(); i++) {
        uint32_t wordMask = 0;
        for (char ch : words[i]) {
            wordMask |= 1 << (ch - 'a');
        }
        masks[i] = wordMask;
        for (size_t j = 0; j < i; j++) {
            if (masks[i] & masks[j]) { continue; }
            int tmp_product = words[i].size() * words[j].size();
            if (tmp_product > product) {
                product = tmp_product;
            }
        }
    }

    return product;
}

int main(void) {
    test_crap_number();
}
