#include <cstdlib>
#include <iostream>
#include <queue>
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

struct trust_data {
    int trusted_count;
    bool trusts_others;
};

int find_judge(int n, std::vector<std::vector<int>>& trust) {
    std::vector<trust_data> mapped = std::vector<trust_data>(n);

    int judge = -1;

    if (trust.size() == 0 && n > 1) { return -1; }
    if (trust.size() == 0 && n == 1) { return 1; }

    for (size_t i = 0; i < trust.size(); i++) {
        int person = trust[i][0];
        int trustee = trust[i][1];
        mapped[trustee - 1].trusted_count++;
        mapped[person - 1].trusts_others = true;

        if (mapped[trustee - 1].trusted_count == n - 1 && !mapped[trustee - 1].trusts_others) {
            judge = trustee;
        }
    }

    if (judge == -1) {
        return -1;
    }

    if (!mapped[judge - 1].trusts_others && mapped[judge - 1].trusted_count == n - 1) {
        return judge;
    } else {
        return -1;
    }
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
        judge_test_t {
            .n = 3,
            .trust = { { 1, 2 }, { 2, 3 } },
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
    if (source == destination) { return true; }
    if (edges.size() == 0) { return false; }

    std::unordered_map<int, std::unordered_set<int>> graph;

    for (int i = 0; i < edges.size(); ++i) {
        graph[edges[i][0]].insert(edges[i][1]);
        graph[edges[i][1]].insert(edges[i][0]);
    }

    std::queue<int> queue;
    std::vector<bool> visited = std::vector<bool>(n);
    queue.push(source);

    while (!queue.empty()) {
        int current = queue.front();
        visited[current] = true;
        queue.pop();
        for (int neighbour : graph[current]) {
            if (neighbour == destination) {
                return true;
            }

            if (neighbour != current && !visited[neighbour]) {
                queue.push(neighbour);
            }
        }
    }

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
        std::cout << "Output:   " << bool_to_str(output) << "\n";
        std::cout << "Expected: " << bool_to_str(test.expected) << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

std::vector<int> shortest_reach(int n, std::vector<std::vector<int>>& edges, int s) {
    if (s > n) {
        s = 1;
    } 

    std::vector<int> distances = std::vector<int>(n, -1);

    std::unordered_map<int, std::unordered_map<int, int>> connections;

    for (size_t i = 0; i < edges.size(); i++) {
        if (connections[edges[i][0] - 1].count(edges[i][1] - 1)) {
            connections[edges[i][0] - 1][edges[i][1] - 1] = std::min(connections[edges[i][0] - 1][edges[i][1] - 1], edges[i][2]);
        } else {
            connections[edges[i][0] - 1][edges[i][1] - 1] = edges[i][2];
        }

        if (connections[edges[i][1] - 1].count(edges[i][0] - 1)) {
            connections[edges[i][1] - 1][edges[i][0] - 1] = std::min(connections[edges[i][1] - 1][edges[i][0] - 1], edges[i][2]);
        } else {
            connections[edges[i][1] - 1][edges[i][0] - 1] = edges[i][2];
        }
    }

    std::queue<std::pair<int, int>> queue;

    queue.push(std::make_pair(s - 1, 0));

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        if (current.second < distances[current.first] || distances[current.first] == -1) {
            distances[current.first] = current.second;

            for (const std::pair<int, int>& connection : connections[current.first]) {
                queue.push(std::make_pair(connection.first, connection.second + current.second));
            }
        }
    }

    distances.erase(distances.begin() + (s - 1));

    return distances;
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
            .s = 1,
            .expected = { 24, 3, 15 }
        },
        shortest_reach_test_t {
            .n = 5,
            .edges = { { 1, 2, 5 }, { 2, 3, 6 }, { 3, 4, 2 }, { 1, 3, 15 } },
            .s = 1,
            .expected = { 5, 11, 13, -1 }
        },
        shortest_reach_test_t {
            .n = 5,
            .edges = { { 1, 2, 10 }, { 1, 3, 6  }, { 2, 4, 8  }, },
            .s = 2,
            .expected = { 10, 16, 8, -1 }
        },
        shortest_reach_test_t {
            .n = 20,
            .edges = {
                { 1, 7, 45 },
                { 2, 14, 15 },
                { 3, 7, 29 },
                { 4, 1, 48 },
                { 5, 1, 66 },
                { 6, 7, 17 },
                { 7, 14, 15 },
                { 8, 14, 43 },
                { 9, 1, 27 },
                { 10, 1, 33 },
                { 11, 14, 64 },
                { 12, 14, 27 },
                { 13, 7, 66 },
                { 14, 7, 54 },
                { 15, 14, 56 },
                { 16, 7, 21 },
                { 17, 1, 20 },
                { 18, 1, 34 },
                { 19, 7, 52 },
                { 20, 14, 14 },
                { 9, 14, 9 },
                { 15, 1, 39 },
                { 12, 1, 24 },
                { 9, 1, 16 },
                { 1, 2, 33 },
                { 18, 1, 46 },
                { 9, 1, 28 },
                { 15, 14, 3 },
                { 12, 1, 27 },
                { 1, 2, 5 },
                { 15, 1, 34 },
                { 1, 2, 28 },
                { 9, 7, 16 },
                { 3, 7, 23 },
                { 9, 7, 21 },
                { 9, 14, 19 },
                { 3, 1, 20 },
                { 3, 1, 5 },
                { 12, 14, 19 },
                { 3, 14, 2 },
                { 12, 1, 46 },
                { 3, 14, 5 },
                { 9, 14, 44 },
                { 6, 14, 26 },
                { 9, 14, 16 },
                { 9, 14, 34 },
                { 6, 7, 42 },
                { 3, 14, 27 },
                { 1, 7, 9 },
                { 1, 7, 41 },
                { 15, 14, 19 },
                { 12, 7, 13 },
                { 3, 7, 10 },
                { 1, 7, 2 },
            },
            .s = 17,
            .expected = { 20, 25, 25, 68, 86, 39, 22, 70, 36, 53, 91, 35, 88, 27, 30, 43, 54, 74, 41 }
        },
    };

    for (shortest_reach_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::vector<int> output = shortest_reach(test.n, test.edges, test.s);
        std::cout << "Input:    " << "Node Count: " << test.n << ", Start Value: " << test.s << "\n";
        std::cout << "Output:   ";
        print_vector(output);
        std::cout << "Expected: ";
        print_vector(test.expected);
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

int main(void) {
    test_shortest_reach();
}
