#include <cassert>
#include <cstdint>
#include <functional>
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

// Reprentation of an obstacle using value and pos
struct obstacle_t {
    int64_t value;
    ivec2 position;
};

// Comparer class that forces priority queue to sort by largest value first
class obstacle_compare_t {
public:
    bool operator()(const obstacle_t& s, const obstacle_t& o) {
        return s.value < o.value;
    }
};

bool operator==(const ivec2& s, const ivec2& o) {
    return (s.x == o.x) && (s.y == o.y);
}

// Hash function allowing ivec2's to be used with stl maps/sets
template<> struct std::hash<ivec2> {
    std::size_t operator() (const ivec2& vec) const noexcept {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};

enum fill_type { normal, inverted };

// Flood fill the grid from bottom left to top right (fill mode may be inverted to do from opposite side)
void fill_grid(std::vector<int64_t>& grid, int nx, int ny, std::unordered_set<ivec2>& obstacle_positions, fill_type fill_mode, bool allow_obstacles = false) {
    bool found_obstacle = false;
    if (fill_mode == normal) {
        // Fill bottom row right to left
        for (int i = nx - 1; i >= 0; i--) {
            if (obstacle_positions.count(ivec2{ i, ny - 1 }) && allow_obstacles) {
                found_obstacle = true;
                // std::cout << "Set Row:      [ " << i << ", " << ny - 1 << " ]\n";
            }
            grid[nx * (ny - 1) + i] = !found_obstacle;
        }

        found_obstacle = false;
        // Fill left column bottom to top
        for (int i = ny - 1; i >= 0; i--) {
            if (obstacle_positions.count(ivec2{ nx - 1, i }) && allow_obstacles) {
                // std::cout << "Set column:   [ " << nx - 1 << ", " << i << " ]\n";
                found_obstacle = true;
            }
            grid[nx * i + nx - 1] = !found_obstacle;
        }

        // Fill rest of grid from bottom right to top left row by row
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
        // Same as normal mode just from opposite corner
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
    // Allocate grid once
    std::vector<int64_t> grid = std::vector<int64_t>(nx * ny);
    // Obstacles to be used in fill algorithm
    std::unordered_set<ivec2> obstacles = std::unordered_set<ivec2>(obstacle_positions.size());

    // Convert obstacles to ivec2 positions used when calculating grid fill
    for (std::vector<int>& pos : obstacle_positions) {
        obstacles.insert(ivec2 { pos[0], pos[1] });
    }

    // First fill of grid
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

    // Map representing obstacle value from position - higher = more likely to remove
    std::unordered_map<ivec2, int64_t> obstacle_map;
    obstacle_map.reserve(obstacle_positions.size());
    std::priority_queue<obstacle_t, std::vector<obstacle_t>, obstacle_compare_t> obstacle_heap;

    // Populate inital obstacle values after first grid fill
    for (ivec2 position : obstacles) {
        obstacle_map[position] = grid[position.y * nx + position.x];
    }

    // Fill grid backwards
    fill_grid(grid, nx, ny, obstacles, fill_type::inverted);
    
    // Compute final value of each obstacle
    for (ivec2 position : obstacles) {
        int64_t product = grid[position.y * nx + position.x];
        obstacle_map[position] *= grid[position.y * nx + position.x];;
    }


    // Put each obstacle into the heap to be sorted

    for (std::pair<ivec2, int64_t> pair : obstacle_map) {
        // std::cout << "Calculated obstacle value at [ " << pair.first.x << ", " << pair.first.y << " ] - Value: " << pair.second << "\n";
        obstacle_heap.push(obstacle_t { pair.second, pair.first });
    }

    // Remove all old obstacles
    obstacles.clear();

    // Pop k highest value obstacles
    for (int i = 0; i < k; i++) {
        // std::cout << "Removed obstacle at [ " << obstacle_heap.top().position.x << ", " << obstacle_heap.top().position.y << " ] - Value: " << obstacle_heap.top().value << "\n";
        obstacle_heap.pop();
    }

    // Replace all remaining obstacles
    while (!obstacle_heap.empty()) {
        obstacles.insert(obstacle_heap.top().position);
        // std::cout << "Kept obstacle at [ " << obstacle_heap.top().position.x << ", " << obstacle_heap.top().position.y << " ] - Value: " << obstacle_heap.top().value << "\n";
        obstacle_heap.pop();
    }

    // Fill grid one last time - this time using obstacle values to set grid points to 0
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

#define torture_test

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
        // std::cout << "\n---------------------------\n";
        int64_t output = robot_paths(test.nx, test.ny, test.k, test.obstacle_positions);
        assert(output == test.expected);
        //
        // std::cout << "Output:   " << output << "\n";
        // std::cout << "Expected: " << test.expected << "\n";
        // std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        // std::cout << "---------------------------\n";
    }
}

int main(void) {
    test_robot_paths();
}
