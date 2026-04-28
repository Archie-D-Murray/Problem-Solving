#include <queue>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

struct ivec2 {
    int x;
    int y;

};

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
    std::priority_queue<obstacle_t, std::vector<obstacle_t>, obstacle_compare_t> obstacle_heap;
    for (ivec2 position : obstacles) {
        obstacle_map[position] = grid[position.y * nx + position.x];
    }

    fill_grid(grid, nx, ny, obstacles, fill_type::inverted);
    for (ivec2 position : obstacles) {
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

long PathCount(int nx, int ny, int numObstacles, int k, vector<vector<int>> obstacles) {
    // Write your code here
    return robot_paths(nx, ny, k, obstacles);
}
