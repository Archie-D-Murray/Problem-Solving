#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

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

template<typename T> void print_pair_vector(std::vector<std::pair<T, T>> vector, bool new_line = true) {
    std::cout << "[ ";
    size_t i = 0;
    for (size_t i = 0; i < vector.size(); i++) {
        if (i < vector.size() - 1) {
            std::cout << vector[i].first << vector[i].second << ", ";
        } else {
            std::cout << vector[i].first << vector[i].second;
        }
    }
    if (new_line) {
        std::cout << " ] \n";
    } else {
        std::cout << " ]";
    }
}

std::string snake_to_camel(std::string& S) {
    std::string ret;
    bool skipped = true;
    bool first = true;
    bool encounteredLetter = false;

    for (size_t i = 0; i < S.size(); i++) {
        if (S[i] == '_' && encounteredLetter) {
            skipped = true;
            first = false;
            continue;
        } else {
            if (std::isalpha(S[i])) {
                encounteredLetter = true;
            }
        }
        ret.push_back((skipped && !first) ? std::toupper(S[i]) : S[i]);
        skipped &= 0;
    }

    return ret;
}

void test_snake_to_camel() {
    std::vector<std::string> tests = {
        "ur_mom",
        "this_is_a_complex_test",
        "fine",
        "__cxx_std",
    };

    for (std::string& test : tests) {
        std::string output = snake_to_camel(test);
        std::cout << "Input: " << test << " -> " << output << "\n";
    }
}

void morse_equivalent(std::string& A, std::string& B) {
    static std::string lookup[26] = {
        ".-",    
        "-...",  
        "-.-.",  
        "-..",   
        ".",     
        "..-.", 
        "--.",  
        "....", 
        "..",   
        ".---", 
        "-.-",  
        ".-..", 
        "--",   
        "-.",
        "---", 
        ".--.",
        "--.-",
        ".-.", 
        "...", 
        "-",
        "..-",
        "...-",
        ".--",
        "-..-",
        "-.--",
        "--..",
    };

    std::string mA, mB;
    for (size_t i = 0; i < std::max(A.size(), B.size()); i++) {
        if (i < A.size()) {
            mA += lookup[A[i] - 'a'];
            std::cout << "A Contcat lookup of char " << A[i] << " -> " << lookup[A[i] - 'a'] << "\n";
        }
        if (i < B.size()) {
            std::cout << "B Contcat lookup of char " << B[i] << " -> " << lookup[B[i] - 'a'] << "\n";
            mB += lookup[B[i] - 'a'];
        }
    }

    std::cout << "Morse A: " << mA << "\nMorse B: " << mB << "\n";
 
    if (mA == mB) {
        std::cout << "TRUE\n";
    } else {
        std::cout << "FALSE\n";
    }
}

void test_morse_equivalent() {
    std::vector<std::pair<std::string, std::string>> tests = {
        { "abc", "wske" },
        { "abcdefg", "tesaetdmneaae" },
        { "helloworld", "ihdrwntotenetfe" },
    };

    for (std::pair<std::string, std::string>& test : tests) {
        morse_equivalent(test.first, test.second);
    }
}

int32_t grid_index(int32_t nArray, int32_t nSteps, std::vector<std::string>& grid) {
    size_t index = 0;
    std::unordered_map<size_t, size_t> loops;

    for (size_t i = 0; i < nSteps; i++) {
        if (!loops.count(index)) {
            loops[index] = i;
        } else {
            nSteps = nSteps % (i - loops[index]);
            loops.clear();
            i = 0;
        }
        char ch = grid[index / nArray][index % nArray];
        switch (ch) {
            case '>':
                index++;
            break;

            case '<':
                index--;
            break;

            case '^':
                index -= nArray;
            break;

            case 'v':
                index += nArray;
            break;
        }
    }

    return index;
}

void test_grid_movement() {

    struct Test {
        size_t width;
        size_t steps;
        std::vector<std::string> grid;
    };
    
    std::vector<Test> tests = {
        { 
            16, 
            8217, 
            {
                ">>>v>>>v>>>v>>>v",
                "^v<<^<v<^v<<^<<v",
                "^>>>>^>>^>>>>>^v",
                "^<<<v<<<<<<<<<<v",
                ">>>^>>>v>>>>>>^v",
                "^<<v<v<v^<<v<v<v",
                ">>^v^v^v>>^v^v^v",
                "^<<<^<^<^v<<^<^<",
                ">>>v>>>v^v>>>>>v",
                "^<<v^<v<^v^v<v<v",
                ">>^>>^>>^>^v^v^v",
                "^<<<<<<v<<v<^<^<",
                ">>>v>>^v>^>v>>>v",
                "^<<>^v<<^v<v^v<<",
                ">>^v<>>v^v^>^>>v",
                "^<<<^<<<^<^<<<<<",
            } 
        }
    };

    for (Test& test : tests) {
        std::cout << "Final index: " << grid_index(test.width, test.steps, test.grid);
    }
}

size_t to_index_coords(int32_t x, int32_t y, int32_t width) {
    return y * width + x;
}

bool correct_rect(std::pair<char, char>& pair, std::unordered_map<char, int32_t>& cols, std::unordered_map<char, int32_t>& rows, const char* grid) { 
    if (abs(cols[pair.first] - cols[pair.second]) > 0 && abs(rows[pair.first] - rows[pair.second]) > 0) {
        char first = pair.first;
        pair.first  = grid[to_index_coords(cols[pair.second], rows[pair.first], 5)];
        pair.second = grid[to_index_coords(cols[first],  rows[pair.second], 5)];
        return true;
    }

    return false;
}
bool correct_rows(std::pair<char, char>& pair, std::unordered_map<char, int32_t>& cols, std::unordered_map<char, int32_t>& rows, const char* grid) { 
    if (rows[pair.first] == rows[pair.second]) {
        pair.first  = grid[to_index_coords((1 + cols[pair.first])  % 5, rows[pair.first],  5)];
        pair.second = grid[to_index_coords((1 + cols[pair.second]) % 5, rows[pair.second], 5)];
        return true;
    }

    return false;
}
bool correct_cols(std::pair<char, char>& pair, std::unordered_map<char, int32_t>& cols, std::unordered_map<char, int32_t>& rows, const char* grid) { 
    if (cols[pair.first] == cols[pair.second]) {
        pair.first  = grid[to_index_coords(cols[pair.first],  (1 + rows[pair.first])  % 5, 5)];
        pair.second = grid[to_index_coords(cols[pair.second], (1 + rows[pair.second]) % 5, 5)];
        return true;
    }

    return false;
}

std::string playfair_code(std::string plainText, std::string codePhrase) {
    char grid[25] = {0};
    char used[26] = {0};

    std::string encoded;

    size_t offset = 0;

    for (size_t i = 0; i < codePhrase.size() && offset < 25; i++) {
        if (codePhrase[i] == 'J') {
            codePhrase[i] = 'I';
        }
        if (used[codePhrase[i] - 'A']) {
            continue;
        } else {
            used[codePhrase[i] - 'A'] = true;
            grid[offset] = codePhrase[i];
            offset++;
        }
    }

    for (size_t i = 0; i < 26; i++) {
        if (used[i]) { continue; }
        if ('A' + i == 'J' && (!used['I' - 'A'] && !used['J' - 'A'])) { 
            grid[offset] = 'I';
            used['I' - 'A'] = true;
            used['J' - 'A'] = true;
            offset++;
        } else if ('A' + i == 'J') {
            used['I' - 'A'] = true;
            used['J' - 'A'] = true;
        } else {
            grid[offset] = 'A' + i;
            used[i] = true;
            offset++;
        }
    }

    for (size_t y = 0; y < 5; y++) {
        for (size_t x = 0; x < 5; x++) {
            std::cout << grid[to_index_coords(x, y, 5)];
        }
        std::cout << "\n";
    }

    std::unordered_map<char, int32_t> cols;
    std::unordered_map<char, int32_t> rows;

    for (size_t i = 0; i < 25; i++) {
        cols[grid[i]] = i % 5;
        rows[grid[i]] = i / 5;
    }

    std::vector<std::pair<char, char>> pairs;
    for (size_t i = 0; i < plainText.size(); ) {
        if (plainText[i] == 'J') { 
            plainText[i] = 'I'; 
        }
        if (i < plainText.size() - 1 && plainText[i + 1] == 'J') {
            plainText[i + 1] = 'I';
        }
        if (i < plainText.size() - 1 && plainText[i] == plainText[i + 1]) {
            pairs.push_back(std::make_pair(plainText[i], 'X'));
            i++;
        } else {
            if (i == plainText.size() - 1) {
                pairs.push_back(std::make_pair(plainText[i], 'X'));
                i++;
            } else {
                pairs.push_back(std::make_pair(plainText[i], plainText[i + 1]));
                i += 2;
            }
        }
    }

    for (std::pair<char, char>& pair : pairs) {
        std::cout << "Got pair: " << pair.first << pair.second << " -> ";

        if (correct_rect(pair, cols, rows, grid)) {
            std::cout << pair.first << pair.second << "\n";
            std::cout << "Corrected rect\n";
        } else if (correct_rows(pair, cols, rows, grid)) {
            std::cout << pair.first << pair.second << "\n";
            std::cout << "Corrected row\n";
        } else if (correct_cols(pair, cols, rows, grid)) {
            std::cout << pair.first << pair.second << "\n";
            std::cout << "Corrected cols\n";
        } else {
            std::cout << pair.first << pair.second << "\n";
        }


        encoded.push_back(pair.first);
        encoded.push_back(pair.second);
    }

    // std::cout << "Pairs from input: " << plainText << " ";
    // print_pair_vector(pairs);

    return encoded;
}

void test_playfair_code() {
    std::cout << playfair_code("WECANNOTTALKABOUTMOTLEYCRUEINTOOMUCHDETAIL", "NIKKYSIX") << "\n";
}

int main(void) {
    test_playfair_code();
}
