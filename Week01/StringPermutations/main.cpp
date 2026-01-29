// #include <bits/stdc++.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
 * Complete the 'CountAnagrams' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts STRING S as parameter.
 */


long CountAnagrams(string S) {
    std::unordered_map<char, size_t> seen;
    for (char ch : S) {
        seen[ch]++;
    }

    long result = 1;
    size_t processed = 0;
    for (std::pair<char, size_t> pair : seen) {
        for (size_t i = 0; i < pair.second; i++) {
            processed++;
            result *= processed; 
            result /= i + 1; 
            // Dividing by count ensures same permutation doesn't work until processed gets to final instance of permutation
        }
    }

    return result;
}

int main()
{
    string S = "abab";

    long perms = CountAnagrams(S);

    cout << perms << "\n";

    return 0;
}


