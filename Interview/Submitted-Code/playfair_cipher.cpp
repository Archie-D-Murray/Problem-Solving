#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

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

string PlayfairCode(string plainText, string codePhrase) {
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
