#include <iostream>
#include <string>
#include <unordered_map>

struct Adjacents {
    char left = '\0';
    char right = '\0';
};

bool contains(Adjacents& adj, char c) {
    return c == adj.left || c == adj.right;
}
    
static std::unordered_map<char, Adjacents> chars;

std::string is_random_walk(std::string S) {
    for (size_t i = 0; i < S.size() - 1; i++) {
        if (!contains(chars[S[i]], S[i + 1])) {
            return "INVALID";
        }
    }

    return "VALID";
}

int main(void) {
    if (chars.empty()) {
        for (char c = 'A'; c <= 'Z'; c++) {
            Adjacents adj;
            if (c - 1 >= 'A') {
                adj.left = c - 1;
            }
            if (c + 1 <= 'Z') {
                adj.right = c + 1;
            }
            chars[c] = adj;
        }
    }

    std::cout << is_random_walk("WVUTUTSRQPONON") << "\n";
    std::cout << is_random_walk("NKPOPOPONOPQRQPON") << "\n";
}
