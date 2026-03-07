#include <cassert>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <stack>
#include <stdbool.h>
#include <vector>

struct ivec2 {
    int x;
    int y;

};

bool operator==(const ivec2& s, const ivec2& o) {
    return (s.x == o.x) && (s.y == o.y);
}

ivec2 operator +(const ivec2& a, const ivec2& b) {
    return ivec2 { a.x + b.x, a.y + b.y };
}

template<> struct std::hash<ivec2> {
    std::size_t operator() (const ivec2& vec) const noexcept {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};

static ivec2 dirs[4] = {
    {  1,  0 },
    { -1,  0 },
    {  0,  1 },
    {  0, -1 },
};

bool is_land(std::vector<std::vector<int>>& grid, ivec2 pos, bool allow_negative = false) {
    if (pos.x < 0 || pos.y < 0 || pos.y >= grid.size() || pos.x >= grid[0].size()) { return false; }
    if (allow_negative) {
        return std::abs(grid[pos.y][pos.x]) == 1;
    } else {
        return grid[pos.y][pos.x] == 1;
    }
}

ivec2 find_first_land(std::vector<std::vector<int>>& grid) {
    ivec2 start = {0, 0};
    for (; start.y < grid.size(); start.y++) {
        for (; start.x < grid[0].size(); start.x++) {
            if (is_land(grid, start)) {
                return start;
            }
        }
        start.x = 0;
    }

    std::cout << "Did not find land in grid - ended at: [" << start.x << ", " << start.y << " ]\n";
    assert(false);
    return { std::max(0, start.x - 1), std::max(0, start.y - 1) };
}

int perimeter_value(std::vector<std::vector<int>>& grid, ivec2 pos) {
    int sum = 4;
    for (size_t i = 0; i < 4; i++) {
        if (is_land(grid, pos + dirs[i], true)) {
            sum--;
        }
    }

    return sum;
}

struct bracket_t {
    char closing;
    bool opening;
};

bracket_t brackets[128] = { 0 };
std::stack<char> stack;

bool process(char ch) {
    if (brackets[ch].opening) {
        char popped = stack.top();
        if (popped != brackets[ch].closing) {
            return false;
        } else {
            stack.pop();
        }
    } else if (brackets[ch].closing) {
        stack.push(ch);
    }

    return true;
}

int island_perimeter(std::vector<std::vector<int>>& grid) {
    brackets['{'] = bracket_t {
        .closing = '}',
        .opening = true
    };

    char chs[] = { '[', ']', '{', '}', '(', ')' };

    std::queue<ivec2> queue;
    int perimeter_sum = 0;

    ivec2 start = find_first_land(grid);
    queue.push(start);

    while (queue.size()) {
        ivec2 current = queue.front();
        grid[current.y][current.x] = -1;
        queue.pop();

        perimeter_sum += perimeter_value(grid, current);
        std::cout << "At node: [ " << current.x << ", " << current.y << " ]\n";

        for (size_t i = 0; i < 4; i++) {
            if (is_land(grid, current + dirs[i])) {
                queue.push(current + dirs[i]);
                grid[current.y + dirs[i].y][current.x + dirs[i].x] = -1;
            }
        }
    }

    return perimeter_sum;
}

struct island_perimeter_test_t {
    std::vector<std::vector<int>> grid;
    int expected;
};

void test_island_perimeter() {
    std::vector<island_perimeter_test_t> tests = {
        island_perimeter_test_t {
            .grid = {
                { 0,1,0,0 },
                { 1,1,1,0 },
                { 0,1,0,0 },
                { 1,1,0,0 },
            },
            .expected = 16
        },
        island_perimeter_test_t {
            .grid = {
                { 1 },
            },
            .expected = 4
        },
        island_perimeter_test_t {
            .grid = {
                { 0,1 },
            },
            .expected = 4
        },
        island_perimeter_test_t {
            .grid = {
                { 0 },
                { 1 }
            },
            .expected = 4
        },
    };
    for (island_perimeter_test_t& test : tests) {
        int output = island_perimeter(test.grid);

        std::cout << "\n-----------------------------------\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << (test.expected == output ? "True" : "False") << "\n";
        std::cout << "-----------------------------------\n";
    }
}

int main(void) {
    test_island_perimeter();
}
