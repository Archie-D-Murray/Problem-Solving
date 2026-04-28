#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

int TakeSteps(int nArray, int nSteps, vector<string> grid) {
    // Write your code here
    int index = 0;
    std::unordered_map<int, int> loops;

    for (int i = 0; i < nSteps; i++) {
        if (loops.find(index) == loops.end()) {
            loops[index] = i;
        } else {
            nSteps = nSteps % (i - loops[index]);
            loops.clear();
            i = 0;
        }
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
        // moves[grid[index / nArray][index % nArray]](&index, nArray); // wtf template issues
    }

    return index;
}
