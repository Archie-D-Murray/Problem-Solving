#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <xutility>

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
    while (pos != end && line.size() - pattern.size() > pos) {
        if (line.substr(pos, pattern.size()) == pattern) {
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
            if (line.substr(pos, P[i].size()) != P[i]) {
                break;
            }

            if (i + 1 == P.size()) {
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

struct ivec2 {
    int x;
    int y;
};

bool ivec2_elements_equal(const ivec2& vec) {    
    return abs(vec.x) - abs(vec.y) == 0;
}

int ivec2_dist(const ivec2& vec) {
    if (ivec2_elements_equal(vec)) {
        return abs(vec.x);
    } else {
        if (abs(vec.x) > abs(vec.y)) {
            return abs(vec.x);
        } else {
            return abs(vec.y);
        }
    }
}

enum dir_t { up, down, left, right, up_left, up_right, down_left, down_right, count };

dir_t get_dir(ivec2 diff) {
    if (diff.x == 0) {
        return diff.y < 0 ? dir_t::up : dir_t::down;
    } else if (diff.y == 0) {
        return diff.x < 0 ? dir_t::left : dir_t::right;
    } else if (ivec2_elements_equal(diff)) {
        if (diff.y > 0) {
            return diff.x < 0 ? dir_t::down_left : dir_t::down_right;
        } else {
            return diff.x < 0 ? dir_t::up_left : dir_t::up_right;
        }
    }

    return dir_t::count;
}

std::unordered_map<dir_t, std::string> dir_to_name = {
    {up, "UP"},        
    {down, "DOWN"},      
    {left, "LEFT"},      
    {right, "RIGHT"},     
    {up_left, "UP_LEFT"},   
    {up_right, "UP_RIGHT"},  
    {down_left, "DOWN_LEFT"}, 
    {down_right, "DOWN_RIGHT"},
    {count, "NONE"}
};

int queen_attacks(int n, int k, int r_q, int c_q, std::vector<std::vector<int>> obstacles) {
    int moves[dir_t::count] = {0};

    ivec2 queen = ivec2 { r_q, c_q };

    moves[dir_t::up]         = queen.y - 1;
    moves[dir_t::down]       = std::max(0, n - queen.y);
    moves[dir_t::left]       = queen.x - 1;
    moves[dir_t::right]      = std::max(0, n - queen.x);
    moves[dir_t::up_left]    = std::min(moves[dir_t::up], moves[dir_t::left]);
    moves[dir_t::up_right]   = std::min(moves[dir_t::up], moves[dir_t::right]);
    moves[dir_t::down_left]  = std::min(moves[dir_t::down], moves[dir_t::left]);
    moves[dir_t::down_right] = std::min(moves[dir_t::down], moves[dir_t::right]);

    std::unordered_set<long> processed;

    for (std::vector<int>& pos : obstacles) {
        ivec2 obstacle = { pos[0], pos[1] };

        long idx = obstacle.y * n + obstacle.x;
        if (processed.count(idx)) { continue; }
        else { processed.insert(idx); }

        ivec2 diff = { obstacle.x - queen.x, obstacle.y - queen.y };
        dir_t dir = get_dir(diff);

        if (dir == dir_t::count) { continue; }
        moves[dir] = std::min(moves[dir], ivec2_dist(diff) - 1);
    }

    int sum = 0;
    for (size_t i = 0; i < dir_t::count; i++) {
        sum += moves[i];
    }
    return sum;}

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
            .pos = {3, 4},
            .grid_size = 5,
            .obstacles = {
                {5,5},
                {2,4},
                {3,2}
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

    size_t i = 0;
    for (queen_attacks_test_t& test : tests) {
        std::cout << "\nTest: " << i << "\n";
        std::cout << "----------------------------------------\n";
        int output = queen_attacks(test.grid_size, test.obstacles.size(), test.pos.first, test.pos.second, test.obstacles);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "TRUE" : "FALSE") << "\n";
        std::cout << "----------------------------------------\n";
        i++;
    }
}

int main(void) {
    test_queen_attacks();
}
