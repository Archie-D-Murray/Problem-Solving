#include <cstdlib>
#include <iostream>
#include <vector>

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

int find_judge(int n, std::vector<std::vector<int>>& trust) {


    return 0;
}

struct judge_test_t {
    int n;
    std::vector<std::vector<int>> trust;
    int expected;
};

void test_find_judge() {
    std::vector<judge_test_t> tests = {
        judge_test_t {
            .n = 2,
            .trust = { { 1, 2 } },
            .expected = 2,
        },
        judge_test_t {
            .n = 3,
            .trust = { { 1, 3 }, { 2, 3 } },
            .expected = 3,
        },
        judge_test_t {
            .n = 3,
            .trust = { { 1, 3 }, { 2, 3 }, { 3, 1 } },
            .expected = -1,
        },
    };

    for (judge_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        int output = find_judge(test.n, test.trust);
        std::cout << "Input:    " << test.n << "\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

bool valid_path(int n, std::vector<std::vector<int>>& edges, int source, int destination) {
    return false;
}

struct valid_path_test_t {
    int n;
    std::vector<std::vector<int>> edges;
    int source;
    int destination;
    bool expected;
};

void test_valid_path() {
    std::vector<valid_path_test_t> tests = {
        valid_path_test_t {
            .n = 3,
            .edges = { { 0, 1 }, { 1, 2 }, { 2, 0 } },
            .source = 0,
            .destination = 2,
            .expected = true,
        },
        valid_path_test_t {
            .n = 6,
            .edges = { { 0, 1 }, { 0, 2 }, { 3, 5 }, { 5, 4 }, { 4, 3 } },
            .source = 0,
            .destination = 5,
            .expected = false,
        },
    };

    for (valid_path_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        bool output = valid_path(test.n, test.edges, test.source, test.destination);
        std::cout << "Input:    " << test.n << "\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

std::vector<int> shortest_reach(int n, std::vector<std::vector<int>>& edges, int s) {
    return {};
}

struct shortest_reach_test_t {
    int n;
    std::vector<std::vector<int>> edges;
    int s;
    std::vector<int> expected;
};

void test_shortest_reach() {
    std::vector<shortest_reach_test_t> tests = { 
        shortest_reach_test_t {
            .n = 4,
            .edges = { { 1, 2, 24 }, { 1, 4, 20 }, { 3, 1, 3 }, { 4, 3, 12 } },
            .s = 5,
            .expected = { 24, 3, 15 }
        },
        shortest_reach_test_t {
            .n = 5,
            .edges = { { 1, 2, 5 }, { 2, 3, 6 }, { 3, 4, 2 }, { 1, 3, 15 } },
            .s = 1,
            .expected = { 5, 11, 13, -1 }
        },
    };

    for (shortest_reach_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::vector<int> output = shortest_reach(test.n, test.edges, test.s);
        std::cout << "Input:    " << test.n << ", " << test.s << "\n";
        std::cout << "Output:   ";
        print_vector(output);
        std::cout << "Expected: ";
        print_vector(test.expected);
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

int main(void) {

}
