#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int highest_degree_vertex(int N, int M, std::vector<int> connections) {
    int max = 0;
    int node = -1;
    std::unordered_map<int, std::unordered_set<int>> map;
    for (size_t i = 0; i < connections.size(); i += 2) {
        map[connections[i]].insert(connections[i + 1]);
        if (map[connections[i]].size() > max) {
            max = map[connections[i]].size();
            node = connections[i];
        } else if (map[connections[i]].size() == max && connections[i] < node) {
            node = connections[i];
        }
        map[connections[i + 1]].insert(connections[i]);
        if (map[connections[i + 1]].size() > max) {
            max = map[connections[i + 1]].size();
            node = connections[i + 1];
        } else if (map[connections[i + 1]].size() == max && connections[i + 1] < node) {
            node = connections[i + 1];
        }
    }

    return node;
}

void build_connection_map(std::unordered_map<int, std::unordered_set<int>>& map, std::vector<int>& connections) {
    for (size_t i = 0; i < connections.size(); i += 2) {
        map[connections[i]].insert(connections[i + 1]);
        map[connections[i + 1]].insert(connections[i]);
    }
}

struct graph_int_test_t {
    int nodes;
    int count_connections;
    std::vector<int> connections;
    int expected;
};

void test_highest_degree() {
    std::vector<graph_int_test_t> tests = {
        graph_int_test_t {
            .nodes = 5,
            .count_connections = 3,
            .connections = { 4, 3, 2, 4, 1, 4 },
            .expected = 4
        },
        graph_int_test_t {
            .nodes = 50,
            .count_connections = 119,
            .connections = {
14, 32, 27, 31, 7, 38, 17, 35, 17, 13, 36, 35, 40, 27, 17, 0, 26, 5, 12, 10, 44, 6, 38, 20, 15, 48, 18, 47, 15, 42, 6, 31, 33, 1, 48, 44, 44, 38, 3, 6, 29, 25, 36, 41, 35, 24, 3, 0, 5, 16, 25, 23, 0, 37, 26, 11, 26, 45, 13, 12, 40, 31, 24, 31, 47, 5, 25, 13, 1, 23, 22, 1, 15, 1, 2, 46, 47, 44, 27, 44, 45, 44, 25, 22, 48, 10, 10, 49, 37, 20, 12, 34, 5, 22, 38, 11, 31, 28, 20, 2, 7, 24, 1, 41, 9, 32, 48, 13, 12, 35, 28, 10, 4, 15, 11, 14, 5, 30, 22, 46, 36, 30, 13, 7, 3, 32, 48, 37, 16, 7, 43, 36, 16, 47, 28, 32, 1, 14, 41, 44, 32, 25, 23, 5, 25, 19, 6, 42, 47, 45, 37, 13, 37, 21, 37, 3, 29, 37, 15, 33, 26, 4, 38, 13, 2, 14, 42, 3, 11, 39, 17, 5, 4, 40, 2, 35, 49, 4, 38, 25, 26, 29, 20, 30, 7, 11, 40, 28, 6, 21, 11, 31, 45, 29, 38, 21, 37, 34, 45, 46, 46, 25, 22, 12, 20, 6, 23, 43, 32, 7, 29, 7, 11, 9, 27, 47, 0, 6, 21, 28, 49, 46, 47, 35, 36, 23, 43, 29, 18, 2, 34, 24, 43, 14, 41, 42, 46, 28
            },
            .expected = 25
        },
        graph_int_test_t {
            .nodes = 100,
            .count_connections = 258,
            .connections = {
7, 43, 1, 73, 37, 58, 10, 44, 31, 49, 69, 1, 8, 38, 38, 92, 57, 23, 26, 93, 33, 40, 84, 64, 36, 87, 70, 91, 61, 1, 57, 34, 75, 22, 47, 45, 84, 66, 58, 7, 68, 51, 91, 94, 46, 29, 70, 12, 55, 19, 30, 21, 32, 72, 92, 61, 43, 35, 50, 60, 23, 67, 66, 61, 69, 74, 69, 63, 72, 13, 10, 35, 67, 24, 15, 67, 88, 99, 53, 60, 67, 89, 1, 63, 63, 29, 68, 0, 51, 40, 19, 6, 36, 28, 49, 74, 1, 49, 76, 38, 14, 76, 55, 26, 18, 33, 96, 17, 19, 65, 36, 16, 52, 22, 84, 88, 10, 1, 91, 55, 15, 75, 76, 63, 60, 51, 8, 67, 29, 21, 86, 54, 84, 27, 22, 41, 10, 41, 71, 89, 36, 51, 79, 11, 68, 18, 59, 5, 72, 12, 48, 40, 50, 11, 83, 50, 63, 11, 52, 51, 1, 31, 65, 95, 3, 4, 26, 86, 63, 13, 83, 1, 17, 59, 67, 66, 86, 84, 64, 95, 72, 16, 82, 52, 7, 48, 81, 32, 49, 19, 25, 12, 53, 10, 18, 22, 80, 51, 4, 5, 46, 0, 15, 62, 50, 91, 44, 55, 51, 44, 30, 24, 94, 79, 73, 37, 48, 63, 16, 32, 90, 43, 73, 75, 2, 47, 50, 96, 6, 21, 70, 87, 22, 63, 88, 89, 20, 58, 35, 29, 66, 85, 70, 52, 95, 56, 69, 55, 87, 99, 14, 54, 36, 33, 6, 14, 75, 37, 98, 16, 47, 82, 89, 97, 67, 6, 91, 32, 10, 37, 17, 14, 56, 58, 65, 63, 82, 54, 56, 8, 85, 0, 23, 22, 17, 56, 61, 74, 89, 19, 55, 80, 73, 43, 27, 42, 32, 69, 79, 10, 16, 7, 13, 76, 9, 99, 33, 24, 52, 46, 53, 70, 70, 93, 17, 84, 40, 66, 33, 38, 46, 34, 50, 5, 43, 63, 6, 97, 7, 89, 19, 23, 43, 19, 86, 20, 59, 47, 53, 89, 40, 61, 48, 35, 90, 22, 49, 82, 22, 96, 53, 80, 59, 72, 36, 54, 20, 0, 52, 41, 86, 35, 54, 38, 53, 48, 84, 68, 82, 60, 15, 30, 57, 77, 67, 43, 20, 62, 99, 5, 16, 91, 22, 42, 11, 31, 59, 11, 69, 20, 82, 16, 29, 41, 76, 50, 88, 38, 24, 31, 23, 97, 97, 49, 42, 18, 54, 75, 16, 84, 11, 86, 14, 84, 42, 93, 79, 80, 58, 15, 23, 69, 56, 94, 90, 75, 22, 30, 71, 2, 93, 6, 49, 24, 18, 91, 96, 71, 31, 67, 95, 5, 22, 27, 58, 39, 51, 49, 78, 13, 26, 40, 14, 49, 49, 44, 81, 37, 41, 12, 62, 13, 50, 10, 6, 2, 99, 21, 92, 88, 23, 28, 91, 71, 34, 12, 3, 70, 52, 5, 23, 40, 87, 97, 25, 38, 58, 47, 69, 92, 10, 33, 32, 73, 10, 54, 73, 15, 43, 39, 28, 51, 34, 37, 0, 88, 99, 90, 81, 77, 10, 48, 67, 92, 48, 26
            },
            .expected = 10
        }
    };

    for (graph_int_test_t& test : tests) {
        int output = highest_degree_vertex(test.nodes, test.count_connections, test.connections);

        std::cout << "\n--------------------------------------------\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "--------------------------------------------\n";
    }
}

int max_friend_group(int N, int M, std::vector<int> connections) {
    std::unordered_map<int, std::unordered_set<int>> map;
    build_connection_map(map, connections);

    int max = 0;
    std::vector<int> stack;
    stack.resize(N);
    std::vector<bool> visited;
    visited.resize(N);


    for (size_t node = 0; node < N; node++) {
        int count = 0;
        stack.clear();
        visited.clear();

        stack.push_back(node);

        while (!stack.empty()) {
            int back = stack.back();
            if (!visited[back]) {
                count++;
                visited[back] = true;
            }
            stack.pop_back();
            for (int connection : map[back]) {
                if (!visited[connection]) {
                    stack.push_back(connection);
                }
            }
        }

        if (count > max) {
            max = count;
        }
    }

    return max;
}

void test_friend_group() {
    std::vector<graph_int_test_t> tests = {
        graph_int_test_t {
            .nodes = 10,
            .count_connections = 8,
            .connections = { 9, 3, 9, 7, 2, 1, 8, 9, 4, 0, 6, 0, 0, 2, 3, 5 },
            .expected = 5
        },
        graph_int_test_t {
            .nodes = 20,
            .count_connections = 16,
            .connections = { 7, 2, 1, 19, 6, 9, 15, 0, 19, 14, 11, 5, 4, 5, 13, 9, 1, 2, 17, 6, 10, 5, 9, 3, 7, 0, 16, 12, 18, 7, 15, 8 },
            .expected = 9
        },
        graph_int_test_t {
            .nodes = 50,
            .count_connections = 45,
            .connections = { 44, 45, 3, 5, 23, 48, 33, 8, 29, 17, 14, 8, 43, 48, 7, 39, 35, 45, 22, 32, 48, 2, 38, 21, 13, 7, 41, 8, 49, 3, 19, 5, 9, 29, 22, 28, 23, 18, 3, 6, 8, 36, 34, 45, 27, 49, 15, 30, 33, 31, 40, 21, 19, 25, 40, 15, 48, 24, 29, 47, 12, 45, 27, 16, 7, 8, 10, 38, 1, 48, 33, 37, 42, 1, 48, 20, 10, 29, 8, 46, 22, 11, 47, 4, 44, 0, 32, 49, 13, 26 },
            .expected = 12
        },
    };

    for (graph_int_test_t& test : tests) {
        int output = max_friend_group(test.nodes, test.count_connections, test.connections);

        std::cout << "\n--------------------------------------------\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "--------------------------------------------\n";
    }
}

int shortest_distance(int N, int M, std::vector<int>& connections, int A, int B) {
    int distance = -1;
    
    std::unordered_map<int, std::unordered_set<int>> map;
    build_connection_map(map, connections);
    std::queue<std::pair<int, int>> queue;
    std::vector<bool> visited = std::vector<bool>(N);

    queue.push(std::make_pair(A, 0));
    visited[A] = true;

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        visited[current.first] = true;
        queue.pop();

        if (current.first == B) {
            return current.second;
        }

        for (int connection : map[current.first]) {
            if (!visited[connection]) {
                queue.push(std::make_pair(connection, current.second + 1));
            }
        }
    }

    return distance;
}

struct shortest_distance_test_t {
    int current;
    int target;
    int nodes;
    int connection_count;
    std::vector<int> connections;
    int expected;
};

void test_shortest_distance() {
    std::vector<shortest_distance_test_t> tests = {
        shortest_distance_test_t {
            .current = 3,
            .target = 2,
            .nodes = 10,
            .connection_count = 8,
            .connections = { 8, 6, 4, 5, 3, 7, 2, 3, 5, 0, 8, 4, 5, 1, 0, 9 },
            .expected = 1
        }
    };

    for (shortest_distance_test_t& test : tests) {
        int output = shortest_distance(test.nodes, test.connection_count, test.connections, test.current, test.target);
        std::cout << "\n--------------------------------------------\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "--------------------------------------------\n";
    }
}

struct ivec2 {
    int x;
    int y;

};

bool operator==(const ivec2& s, const ivec2& o) {
    return (s.x == o.x) && (s.y == o.y);
}

template<> struct std::hash<ivec2> {
    std::size_t operator() (const ivec2& vec) const noexcept {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};

int shortest_path(std::vector<std::string> maze, int nx, int ny) {
    std::unordered_map<ivec2, std::unordered_set<ivec2>> adj;

    std::vector<ivec2> stack;

    stack.push_back({0, 0});

    while (!stack.empty()) {
        ivec2 cur = stack.back();
        stack.pop_back();

        if (cur.x > 0 && maze[cur.y][cur.x - 1] == '.') {
            stack.push_back({ cur.x - 1, cur.y });
            adj[cur].insert(stack.back());
            adj[stack.back()].insert(cur);
            maze[cur.y][cur.x - 1] = 'x';
        }
        if (cur.y > 0 && maze[cur.y - 1][cur.x] == '.') {
            stack.push_back({ cur.x, cur.y - 1 });
            adj[cur].insert(stack.back());
            adj[stack.back()].insert(cur);
            maze[cur.y - 1][cur.x] = 'x';
        }
        if (cur.x < nx - 1 && maze[cur.y][cur.x + 1] == '.') {
            stack.push_back({ cur.x + 1, cur.y });
            adj[cur].insert(stack.back());
            adj[stack.back()].insert(cur);
            maze[cur.y][cur.x + 1] = 'x';
        }
        if (cur.y < ny - 1 && maze[cur.y + 1][cur.x] == '.') {
            stack.push_back({ cur.x, cur.y + 1 });
            adj[cur].insert(stack.back());
            adj[stack.back()].insert(cur);
            maze[cur.y + 1][cur.x] = 'x';
        }
    }

    std::unordered_set<ivec2> visited = std::unordered_set<ivec2>(adj.size());
    std::queue<std::pair<ivec2, int>> queue;
    int distance = -1;

    visited.insert(ivec2 {0, 0});
    queue.push(std::make_pair(ivec2 {0, 0}, 1));

    ivec2 end = { nx - 1, ny - 1 };
    while (!queue.empty()) {
        std::pair<ivec2, int> cur = queue.front();
        queue.pop();

        if (cur.first == end) {
            return cur.second;
        } else {
            for (ivec2 connection : adj[cur.first]) {
                if (visited.count(connection)) { continue; }
                visited.insert(connection);
                queue.push(std::make_pair(connection, cur.second + 1));
            }
        }
    }

    return distance;
}

struct shortest_path_test_t {
    std::vector<std::string> maze;
    int expected;
};

void test_shortest_path() {
    std::vector<shortest_path_test_t> tests = {
        shortest_path_test_t {
            .maze = {
                "..###",
                "#...#",
                "###.#",
                "#...#",
                "###..",
            },
            .expected = 9
        },
        shortest_path_test_t {
            .maze = {
                "..###################",
                "#...#.......#.....#.#",
                "###.#.#####.#.###.#.#",
                "#.#...#...#.#.#...#.#",
                "#.#######.#.#.###.#.#",
                "#.........#.#...#.#.#",
                "#.###.#####.#.#.#.#.#",
                "#...#.#.....#.#.#.#.#",
                "#####.#.#####.#.#.#.#",
                "#.....#.....#.#.#...#",
                "#.###.#####.###.#####",
                "#.#.#.#...#...#.....#",
                "#.#.#.###.###.#.###.#",
                "#.#.#.#.....#.#.#...#",
                "#.#.#.#.###.#.###.###",
                "#.#...#...#.#...#...#",
                "#.#.#####.#####.###.#",
                "#.#.......#...#...#.#",
                "#.#########.#.###.#.#",
                "#...........#.......#",
                "###################..",
            },
            .expected = 53
        },
    };

    for (shortest_path_test_t& test : tests) {
        int output = shortest_path(test.maze, test.maze[0].size(), test.maze.size());
        std::cout << "\n--------------------------------------------\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
        std::cout << "--------------------------------------------\n";
    }
}

int main(void) {
    test_shortest_path();
}
