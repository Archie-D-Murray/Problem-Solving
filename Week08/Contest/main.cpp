#include <csignal>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const char* bool_to_str(bool value) {
    return value ? "True" : "False";
}

struct ivec2 {
    int x;
    int y;

};

// Mark: Q1
bool is_power_3(int64_t value) {
    return value > 0 && (4052555153018976267l % value) == 0;
}

struct power_3_test_t {
    int64_t input;
    bool expected;
};

void test_is_power_3() {
    std::vector<power_3_test_t> tests = {
        power_3_test_t {
            4052555153018976267l,
            true
        },
        power_3_test_t {
            9,
            true
        },
        power_3_test_t {
            2,
            false
        }
    };

    for (power_3_test_t& test : tests) {
        std::cout << "\n---------------------------\n";
        bool output = is_power_3(test.input);
        std::cout << "Output:   " << bool_to_str(output) << "\n";
        std::cout << "Expected: " << bool_to_str(test.expected) << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "---------------------------\n";
    }
}

// Mark: Q2

int split_count(std::string& str, size_t start, size_t length) {
    if (length == 1) { return 1; }
    char min = 10;
    char max = 0;
    for (size_t i = start; i < start + length; i++) {
        if (str[i] - '0' < min) {
            min = str[i] - '0';
        }
        if (str[i] - '0' > max) {
            max = str[i] - '0';
        }
        if (max - min > 1) {
            return split_count(str, start, length / 2) + split_count(str, start + length / 2, length / 2);
        }
    }
    return 1;
}

int split_count_no_subtraction(std::string& str, size_t start, size_t length) {
    if (length == 1) { return 1; }
    char min = '0' + 10;
    char max = '0';
    for (size_t i = start; i < start + length; i++) {
        if (str[i] < min) {
            min = str[i];
        }
        if (str[i] > max) {
            max = str[i];
        }
        if (max - min > 1) {
            return split_count(str, start, length / 2) + split_count(str, start + length / 2, length / 2);
        }
    }
    return 1;
}

struct split_test_t {
    std::string input;
    int expected;
};

void test_split_count() {
    std::vector<split_test_t> tests = {
        split_test_t {
            .input = "11112222",
            .expected = 1,
        },
        split_test_t {
            .input = "12123434",
            .expected = 2,
        },
        split_test_t {
            .input = "64444444",
            .expected = 4,
        },
    };

    for (split_test_t& test : tests) {
        std::cout << "\n---------------------------\n";
        int output = split_count(test.input, 0, test.input.size());
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   " << (output) << "\n";
        std::cout << "Expected: " << (test.expected) << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "---------------------------\n";
    }
}

// Mark: Q3

// n: Target
// m: Sides
int64_t count_ways(int m, int n) {
    std::vector<int64_t> previous = std::vector<int64_t>(n, 0);
    previous[0] = 1;

    // 1->3 = 6, 2->4 = 9 <- 6 - 1 (prev min) + 4 (new limit)
    int64_t sum = previous[0];

    for (size_t i = 1; i < n; i++) {

        previous[i] = sum;
        sum += previous[i];

        if (i >= m) {
            sum -= previous[i - m];
        }
    }

    return previous[n - 1];
}

struct ways_test_t {
    int target;
    int sides;
    int64_t expected;
};

void test_ways_count() {
    std::vector<ways_test_t> tests = {
        ways_test_t {
            .target = 10,
            .sides = 6,
            .expected = 248
        },
        ways_test_t {
            .target = 10,
            .sides = 2,
            .expected = 55
        },
        ways_test_t {
            .target = 50,
            .sides = 6,
            .expected = 196131794875135
        },
    };

    for (ways_test_t& test : tests) {
        std::cout << "\n---------------------------\n";
        int64_t output = count_ways(test.sides, test.target);
        std::cout << "Output:   " << (output) << "\n";
        std::cout << "Expected: " << (test.expected) << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "---------------------------\n";
    }
}

// Mark: Q4

struct obstacle_t {
    int64_t value;
    ivec2 position;
};

class obstacle_compare_t {
public:
    bool operator()(const obstacle_t& s, const obstacle_t& o) {
        return s.value < o.value;
    }
};

bool operator==(const ivec2& s, const ivec2& o) {
    return (s.x == o.x) && (s.y == o.y);
}

template<> struct std::hash<ivec2> {
    std::size_t operator() (const ivec2& vec) const noexcept {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};

enum fill_type { normal, inverted };

void fill_grid(std::vector<int64_t>& grid, int nx, int ny, std::unordered_set<ivec2>& obstacle_positions, fill_type fill_mode, bool allow_obstacles = false) {
    bool found_obstacle = false;
    if (fill_mode == normal) {
        for (int i = nx - 1; i >= 0; i--) {
            if (obstacle_positions.count(ivec2{ i, ny - 1 }) && allow_obstacles) {
                found_obstacle = true;
                // std::cout << "Set Row:      [ " << i << ", " << ny - 1 << " ]\n";
            }
            grid[nx * (ny - 1) + i] = !found_obstacle;
        }

        found_obstacle = false;
        for (int i = ny - 1; i >= 0; i--) {
            if (obstacle_positions.count(ivec2{ nx - 1, i }) && allow_obstacles) {
                // std::cout << "Set column:   [ " << nx - 1 << ", " << i << " ]\n";
                found_obstacle = true;
            }
            grid[nx * i + nx - 1] = !found_obstacle;
        }

        for (int y = ny - 2; y >= 0; y--) {
            for (int x = nx - 2; x >= 0; x--) {
                if (!allow_obstacles || !obstacle_positions.count(ivec2{x, y})) {
                    grid[y * nx + x] = grid[(y + 1) * nx + x] + grid[y * nx + x + 1];
                } else {
                    // std::cout << "Set obstacle: [ " << x << ", " << y << " ]\n";
                    grid[y * nx + x] = 0;
                }
            }
        }
    } else {
        for (int i = 0; i < nx; i++) {
            if (obstacle_positions.count(ivec2{ i, 0 }) && allow_obstacles) {
                found_obstacle = true;
                // std::cout << "Set Row:      [ " << i << ", " << 0 << " ]\n";
            }
            grid[nx * 0 + i] = !found_obstacle;
        }

        found_obstacle = false;
        for (int i = 0; i < ny; i++) {
            if (obstacle_positions.count(ivec2{ 0, i }) && allow_obstacles) {
                // std::cout << "Set column:   [ " << 0 << ", " << i << " ]\n";
                found_obstacle = true;
            }
            grid[nx * i + 0] = !found_obstacle;
        }

        for (int y = 1; y < ny; y++) {
            for (int x = 1; x < nx; x++) {
                if (!allow_obstacles || !obstacle_positions.count(ivec2{x, y})) {
                    grid[y * nx + x] = grid[(y - 1) * nx + x] + grid[y * nx + x - 1];
                } else {
                    // std::cout << "Set obstacle: [ " << x << ", " << y << " ]\n";
                    grid[y * nx + x] = 0;
                }
            }
        }
    }
}

int64_t robot_paths(int nx, int ny, int k, std::vector<std::vector<int>>& obstacle_positions) {
    std::vector<int64_t> grid = std::vector<int64_t>(nx * ny);
    std::unordered_set<ivec2> obstacles = std::unordered_set<ivec2>(obstacle_positions.size());
    for (std::vector<int>& pos : obstacle_positions) {
        obstacles.insert(ivec2 { pos[0], pos[1] });
    }
    fill_grid(grid, nx, ny, obstacles, fill_type::normal);

    // auto old = std::cout.flags();
    // std::cout << std::scientific;
    // std::cout.precision(2);
    // std::cout << "\nGrid: \n";
    // for (size_t y = 0; y < ny; y++) {
    //     for (size_t x = 0; x < nx; x++) {
    //         std::cout << (double) grid[y * nx + x] << ", ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "\n";


    std::unordered_map<ivec2, int64_t> obstacle_map;
    obstacle_map.reserve(obstacle_positions.size());
    std::priority_queue<obstacle_t, std::vector<obstacle_t>, obstacle_compare_t> obstacle_heap;
    for (ivec2 position : obstacles) {
        obstacle_map[position] = grid[position.y * nx + position.x];
    }

    fill_grid(grid, nx, ny, obstacles, fill_type::inverted);
    for (ivec2 position : obstacles) {
        int64_t product = grid[position.y * nx + position.x];
        obstacle_map[position] *= grid[position.y * nx + position.x];;
    }

    for (std::pair<ivec2, int64_t> pair : obstacle_map) {
        // std::cout << "Calculated obstacle value at [ " << pair.first.x << ", " << pair.first.y << " ] - Value: " << pair.second << "\n";
        obstacle_heap.push(obstacle_t { pair.second, pair.first });
    }


    obstacles.clear();
    for (int i = 0; i < k; i++) {
        // std::cout << "Removed obstacle at [ " << obstacle_heap.top().position.x << ", " << obstacle_heap.top().position.y << " ] - Value: " << obstacle_heap.top().value << "\n";
        obstacle_heap.pop();
    }

    while (!obstacle_heap.empty()) {
        obstacles.insert(obstacle_heap.top().position);
        // std::cout << "Kept obstacle at [ " << obstacle_heap.top().position.x << ", " << obstacle_heap.top().position.y << " ] - Value: " << obstacle_heap.top().value << "\n";
        obstacle_heap.pop();
    }

    fill_grid(grid, nx, ny, obstacles, fill_type::normal, true);
    // std::cout << "\nObstacle Grid: \n";
    // std::cout << std::scientific;
    // std::cout.precision(2);
    // for (size_t y = 0; y < ny; y++) {
    //     for (size_t x = 0; x < nx; x++) {
    //         std::cout << (double) grid[y * nx + x] << ", ";
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "\n";

    return grid[0];
}

struct robot_test_t {
    int nx;
    int ny;
    int k;
    std::vector<std::vector<int>> obstacle_positions;
    int64_t expected;
};

// #define torture_test

void test_robot_paths() {
    std::vector<robot_test_t> tests = {
        #ifndef torture_test
        robot_test_t {
            .nx = 3,
            .ny = 2,
            .k = 1,
            .obstacle_positions = {
                {1, 1}
            },
            .expected = 3
        },
        robot_test_t {
            .nx = 6,
            .ny = 6,
            .k = 2,
            .obstacle_positions = {
                { 0, 2 },
                { 4, 4 },
                { 5, 2 },
                { 5, 4 },
            },
            .expected = 176
        },
        #else
        robot_test_t {                  //  20 10 8 4
            .nx = 1000,                   // 1 0
            .ny = 1000,                   // 1 3
            .k = 5,                     // 5 0
            .obstacle_positions = {     // 9 7
                { 595, 418 },
                { 513, 575 },
                { 766, 492 },
                { 780, 714 },
                { 811, 215 },
                { 636, 284 },
                { 590, 480 },
                { 752, 728 },
                { 569, 475 },
                { 620, 523 },
                { 805, 689 },
                { 585, 779 },
                { 601, 713 },
                { 716, 468 },
                { 824, 425 },
                { 510, 579 },
                { 501, 554 },
                { 551, 460 },
                { 914, 506 },
                { 646, 515 },
            },
            .expected = 5819285640465217080l
        },
        #endif
    };

    for (robot_test_t& test : tests) {
        std::cout << "\n---------------------------\n";
        int64_t output = robot_paths(test.nx, test.ny, test.k, test.obstacle_positions);

        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "---------------------------\n";
    }
}

int main(void) {
    test_split_count();
}
