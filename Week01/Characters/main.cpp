#include <iostream>
#include <unordered_map>
#include <string>

int count_chars(std::string list, std::string str);

int main(int argc, const char* argv[]) {

    std::string a_list = "abc";
    std::string a_test = "aabbcc";
    std::cout << count_chars(a_list, a_test) << "\n";
    std::string b_list = "abcd";
    std::string b_test = "xyzw";
    std::cout << count_chars(b_list, b_test) << "\n";
    std::string c_list = "xyz";
    std::string c_test = "z";
    std::cout << count_chars(c_list, c_test) << "\n";

    return 0;
}

struct Adjacents {
    char left = '\0';
    char right = '\0';
};

bool contains(Adjacents& adj, char c) {
    return c == adj.left || c == adj.right;
}

int count_chars(std::string str) {

    static std::unordered_map<char, Adjacents> chars;

    if (chars.empty()) {
        for (char c = 'A'; c <= 'Z'; c++) {
            Adjacents adj;
            if (c - 1 >= 'A') {
                adj.left = c - 1;
            }
            if (c + 1 <= 'Z') {
                adj.right = c + 1;
            }
            chars[c] = adj;
        }
    }

    for (char c : str) {
        if ()
    }

    return result;
}
