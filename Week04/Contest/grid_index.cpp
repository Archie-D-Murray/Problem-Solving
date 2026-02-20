#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// WARN: Does not work!
// #define FUNCTION_PTR_LOOKUP

#ifdef FUNCTION_PTR_LOOKUP

void up(size_t* index, size_t width) {
    (*index) -= width;
}

void down(size_t* index, size_t width) {
    (*index) += width;
}

void right(size_t* index, size_t width) {
    (*index) += 1;
}

void left(size_t* index, size_t width) {
    (*index) -= 1;
}


typedef void (*move_t(size_t*, size_t));

// Leaving blank and initialising using emplace or just moves['^'] = &up; does not work either
std::unordered_map<char, move_t> moves = {
    { '^', &up },
    { 'v', &down },
    { '>', &right },
    { '<', &left },
};

#endif

int32_t grid_index(int32_t nArray, int32_t nSteps, std::vector<std::string>& grid) {
    size_t index = 0;
    std::unordered_map<size_t, size_t> loops;

    for (size_t i = 0; i < nSteps; i++) {

        // This if statement massively optimises but is not necessary for C++
        if (!loops.count(index)) {
            loops[index] = i;
        } else {
            nSteps = nSteps % (i - loops[index]);
            loops.clear();
            i = 0;
        }

        #ifdef FUNCTION_PTR_LOOKUP

        moves[grid[index / nArray][index % nArray]](&index, nArray);
        
        #else

        char ch = grid[index / nArray][index % nArray];
        switch (ch) {
            case '>':
                index++;
            break;

            case '<':
                index--;
            break;

            case '^':
                index -= nArray;
            break;

            case 'v':
                index += nArray;
            break;
        }

        #endif
    }

    return index;
}

int main(void) {
    int32_t width = 16;
    int32_t steps = 8217;
    std::vector<std::string> grid = {
        ">>>v>>>v>>>v>>>v",
        "^v<<^<v<^v<<^<<v",
        "^>>>>^>>^>>>>>^v",
        "^<<<v<<<<<<<<<<v",
        ">>>^>>>v>>>>>>^v",
        "^<<v<v<v^<<v<v<v",
        ">>^v^v^v>>^v^v^v",
        "^<<<^<^<^v<<^<^<",
        ">>>v>>>v^v>>>>>v",
        "^<<v^<v<^v^v<v<v",
        ">>^>>^>>^>^v^v^v",
        "^<<<<<<v<<v<^<^<",
        ">>>v>>^v>^>v>>>v",
        "^<<>^v<<^v<v^v<<",
        ">>^v<>>v^v^>^>>v",
        "^<<<^<<<^<^<<<<<",
    };

    std::cout << "Expected: 9 -> Got: " << grid_index(width, steps, grid) << "\n";
}
