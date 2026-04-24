#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

static char dog_letters[26] = {0};
static char cat_letters[26] = {0};

int32_t dog_letter_mask = 0;
int32_t cat_letter_mask = 0;

std::string cat_dog_str(std::string& word) {
    int dog = 0;
    int cat = 0;

    bool dog_active = false;
    bool cat_active = false;

    int dog_length = 0;
    int cat_length = 0;

    for (char ch : word) {
        int bit = 1 << (std::tolower(ch) - 'a');

        if (dog_letter_mask & bit) {
            dog_active = true;
            dog_length++;
        } else if (dog_active) {
            dog = std::max(dog_length, dog);
            dog_length = 0;
        }

        if (cat_letter_mask & bit) {
            cat_active = true;
            cat_length++;
        } else if (cat_active) {
            cat = std::max(cat_length, cat);
            cat_length = 0;
        }
    }
    
    if (dog_active) {
        dog = std::max(dog_length, dog);
    }
    
    if (cat_active) {
        cat = std::max(cat_length, cat);
    }

    if (cat == dog) {
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

    dog_letters['d' - 'a'] = 1;
    dog_letters['o' - 'a'] = 1;
    dog_letters['g' - 'a'] = 1;

    dog_letter_mask |= 1 << ('d' - 'a');
    dog_letter_mask |= 1 << ('o' - 'a');
    dog_letter_mask |= 1 << ('g' - 'a');
    
    cat_letters['c' - 'a'] = 1;
    cat_letters['a' - 'a'] = 1;
    cat_letters['t' - 'a'] = 1;

    cat_letter_mask |= 1 << ('c' - 'a');
    cat_letter_mask |= 1 << ('a' - 'a');
    cat_letter_mask |= 1 << ('t' - 'a');

    std::vector<cat_dog_test_t> tests = {
        cat_dog_test_t {
            .input = "obtain",
            .expected = "CAT",
        },
        cat_dog_test_t {
            .input = "suggestion",
            .expected = "DOG",
        },
        cat_dog_test_t {
            .input = "german",
            .expected = "NEITHER",
        },
    };

    for (cat_dog_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::string output = cat_dog_str(test.input);
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

int stationary_numbers(std::vector<int>& values) {
    std::vector<int> sorted = std::vector<int>(values.size());
    memcpy(sorted.data(), values.data(), sizeof(int) * values.size());

    std::stable_sort(sorted.begin(), sorted.end());

    int stationary = 0;

    for (size_t i = 0; i < values.size(); i++) {
        if (sorted[i] == values[i]) {
            stationary++;
        }
    }

    return stationary;
}

struct stationary_test_t {
    std::vector<int> input;
    int expected;
};

void test_stationary_numbers() {
    std::vector<stationary_test_t> tests = {
        stationary_test_t {
            .input = { 5, 2, 4, 2, 5 },
            .expected = 3,
        }
    };


    for (stationary_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        int output = stationary_numbers(test.input);
        std::cout << "Input:    ";
        print_vector(test.input);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

std::string check_dependencies(int A, int B, std::vector<int>& dependencies) {
    std::unordered_map<int, std::unordered_set<int>> dependency_graph;

    for (size_t i = 0; i < dependencies.size(); i += 2) {
        printf("Added dependency from %2d -> %2d\n", dependencies[i], dependencies[i + 1]);
        dependency_graph[dependencies[i]].insert(dependencies[i + 1]);
    }

    std::queue<int> queue;
    queue.push(A);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        for (int dependency : dependency_graph[current]) {
            printf("Pushing dependency %2d associated with value %2d\n", dependency, current);
            queue.push(dependency);

            if (dependency == B) {
                return "TRUE";
            }
        }
    }

    return "FALSE";
}

struct dependency_test_t {
    int a;
    int b;
    std::vector<int> dependencies;
    std::string expected;
};

void test_dependencies() {
    std::vector<dependency_test_t> tests = {
        dependency_test_t {
            .a = 8,
            .b = 6,
            .dependencies = { 6, 7, 6, 2, 1, 3, 1, 0, 1, 4, 1, 6, 5, 9, 9, 8, 8, 1 },
            .expected = "TRUE",
        },
        dependency_test_t {
            .a = 19,
            .b = 1,
            .dependencies = { 13, 17, 19, 1, 14, 7, 11, 2, 14, 5, 7, 8, 5, 13, 5, 11, 7, 16, 11, 3, 1, 4, 1, 12, 19, 15, 1, 0, 15, 10, 16, 9, 14, 19, 13, 6, 13, 18 },
            .expected = "TRUE",
        }
    };

    for (dependency_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::string output = check_dependencies(test.a, test.b, test.dependencies);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

int path_length(int v0, int v1, std::vector<int>& edges) {
    std::unordered_map<int, std::unordered_map<int, int>> graph;

    for (size_t i = 0; i < edges.size(); i += 3) {
        graph[edges[i + 0]][edges[i + 1]] = edges[i + 2];
        graph[edges[i + 1]][edges[i + 0]] = edges[i + 2];
    }

    std::queue<std::pair<int, int>> queue;

    queue.push(std::make_pair(v0, 0));

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        for (const std::pair<int, int>& connection : graph[current.first]) {
            if (connection.first == v1) {
                return current.second + connection.second;
            } else {
                queue.push(std::make_pair(connection.first, current.second + connection.second));
            }
        }
    }

    return -1;
}

struct path_test_t {
    int start;
    int end;
    std::vector<int> edges;
    int expected;
};

void test_path_length() {
    std::vector<path_test_t> tests = {
        path_test_t {
            .start = 8,
            .end = 1,
            .edges = { 0, 5, 865, 0, 6, 423, 0, 2, 947, 5, 9, 180, 5, 4, 98, 5, 8, 111, 5, 3, 658, 6, 1, 633, 2, 7, 323 },
            .expected = 2032,
        },
    };

    for (path_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        int output = path_length(test.start, test.end, test.edges);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

int main(void) {
    test_cat_dog();
}
