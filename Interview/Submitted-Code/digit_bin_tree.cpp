#include <string>

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
