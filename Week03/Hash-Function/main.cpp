#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
int hash(std::string S) {
    int64_t hash = 0;

    const int32_t m = 2147483647;
    const int32_t A = 48271;

    for (char ch : S) {
        hash = ((hash + ch) * A) % m;
    }

    return hash % 256;
}

int main(void) {
    std::vector<std::string> tests = {
        "Friends, Romans, countrymen, lend me your ears; I come to bury Caesar, not to praise him.The evil that men do lives after them; The good is oft interred with their bones; So let it be with Caesar. The noble Brutus Hath told you Caesar was ambitious : If it were so, it was a grievous fault, And grievously hath Caesar answer'd it.",
        "abcdefghijklmnop"
    };

    for (std::string& test : tests) {
        std::cout << "Input: " << test << " Hash: " << hash(test) << "\n";
     }
}
