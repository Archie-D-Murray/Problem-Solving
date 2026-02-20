#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

std::string reverse_vowels(std::string& s) {
    static std::unordered_set<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
    std::vector<std::pair<char, size_t>> stack;
    size_t front = 0;
    size_t back = s.size() - 1;
    while (front < back) {
        if (!vowels.count(std::tolower(s[front]))) {
            front++;

            if (!vowels.count(std::tolower(s[back]))) {
                back--;
            }
        } else if (vowels.count(std::tolower(s[back]))) {
            char swap = s[back];
            s[back] = s[front];
            s[front] = swap;
            front++;
            back--;
        } else {
            if (!vowels.count(std::tolower(s[back]))) {
                back--;
            }
        }
    }

    return s;
}

void test_reverse_vowels() {
    std::vector<std::pair<std::string, std::string>> tests {
        { "hello", "holle" },
        { "leetcode", "leotcede" }
    };

    for (std::pair<std::string, std::string>& test : tests) {
        std::string output = reverse_vowels(test.first);
        std::cout << "Input:    " << test.first << "\n";
        std::cout << "Ouput:    " << output << "\n";
        std::cout << "Expected: " << test.second << "\n";
        std::cout << "Match:    " << (output == test.second ? "TRUE" : "FALSE") << "\n"; 
    }
}

bool isomorphic(std::string& s, std::string& t) {
    char stot[256] = {0};
    char ttos[256] = {0};

    for (size_t i = 0; i < s.size(); i++) {
        char ch_s = s[i];
        char ch_t = t[i];

        if (!stot[ch_s]) {
            stot[ch_s] = ch_t;
        } else if (stot[ch_s] != ch_t) {
            return false;
        } 
        if (!ttos[ch_t]) {
            ttos[ch_t] = ch_s; 
        } else if (ttos[ch_t] != ch_s) {
            return false;
        }
    }

    return true;
}

struct isomorphic_test_t {
    std::string input;
    std::string test;
    bool expected;
};

void test_isomorphic() {
    std::vector<isomorphic_test_t> tests {
        isomorphic_test_t { "egg", "add", true },
        isomorphic_test_t { "foo", "bad", false },
        isomorphic_test_t { "paper", "title", true },
        isomorphic_test_t { "badc", "baba", false }
    };

    for (isomorphic_test_t& test : tests) {
        bool output = isomorphic(test.input, test.test);
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Test:     " << test.test << "\n";
        std::cout << "Ouput:    " << (output ? "TRUE" : "FALSE") << "\n";
        std::cout << "Expected: " << (test.expected ? "TRUE" : "FALSE") << "\n";
        std::cout << "Match:    " << (output == test.expected ? "TRUE" : "FALSE") << "\n"; 
    }
}

bool find_first_line(std::string& line, std::string& pattern, size_t* out) {
    size_t pos = line.find(pattern[0]);
    size_t end = line.npos;
    while (pos != end && line.size() - pattern.size() >= pos) {
        pos = line.find(pattern, pos);
        if (pos != end) {
            *out = pos;
            return true;
        } else {
            pos = line.find(pattern[0], pos + 1);
        }
    }
    return false;
}

std::string grid_search(std::vector<std::string>& G, std::vector<std::string>& P) {
    for (size_t start = 0; start < G.size(); start++) {
        size_t pos = 0;
        if (!find_first_line(G[start], P[0], &pos)) { continue; }
        for (size_t i = 1; i < P.size(); i++) {
            std::string& line = G[start + i];
            size_t p_pos = line.find(P[i][0], pos);
            if (p_pos != pos) { break;}
            if (!line.find(P[i], p_pos)) { 
                break;
            }
            if (i == P.size() - 1) {
                return "YES";
            }
        }
    }
    return "NO";
}

struct grid_search_test_t {
    std::vector<std::string> grid;
    std::vector<std::string> pattern;
    std::string expected;
};

void test_grid_search() {
    grid_search_test_t test = {
        {
            "7283455864",
            "6731158619",
            "8988242643",
            "3830589324",
            "2229505813",
            "5633845374",
            "6473530293",
        },
        {
            "9505", "3845", "3530"
        },
        "YES"
    };

    std::string output = grid_search(test.grid, test.pattern);
    std::cout << "Grid:\n";
    for (std::string& line : test.grid) {
        std::cout << line << "\n";
    }
    std::cout << "\nPattern: ";
    print_vector(test.pattern);
    std::cout << "Output:   " << output << "\n";
    std::cout << "Expected: " << test.expected << "\n";
    std::cout << "Match:    " << (output == test.expected ? "TRUE" : "FALSE") << "\n";
}

int queen_attacks(int n, int k, int r_q, int c_q, std::vector<std::vector<int>> obstacles) {
    return 0;
}

struct queen_attacks_test_t {
    std::pair<int, int> pos;
    int grid_size;
    std::vector<std::vector<int>> obstacles;
    int expected;
};

void test_queen_attacks() {
    std::vector<queen_attacks_test_t> tests = {
        queen_attacks_test_t { 
            .pos = {4,4},
            .grid_size = 4,
            .obstacles = {},
            .expected = 9
        },
        queen_attacks_test_t { 
            .pos = {4,3},
            .grid_size = 5,
            .obstacles = {
                {5,5},
                {4,2},
                {2,3}
            },
            .expected = 10
        },
        queen_attacks_test_t {
            .pos = {1,1},
            .grid_size = 1,
            .obstacles = {},
            .expected = 0
        }
    };

    for (queen_attacks_test_t& test : tests) {
        int output = queen_attacks(test.grid_size, test.obstacles.size(), test.pos.first, test.pos.second, test.obstacles);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "TRUE" : "FALSE") << "\n";
    }
}

int main(void) {
    test_grid_search();
}
