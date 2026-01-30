#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'winningLotteryTicket' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts STRING_ARRAY tickets as parameter.
 */

bool isWinningTicket(std::string& ticket, std::string& other) {
    static std::unordered_set<char> unique(10);
    for (char c : ticket) {
        unique.insert(c);

        if (unique.size() >= 10) {
            unique.clear();
            return true;
        }
    }

    for (char c : other) {
        unique.insert(c);

        if (unique.size() >= 10) {
            unique.clear();
            return true;
        }
    }

    bool winning = unique.size() >= 10;

    unique.clear();

    return winning;
}

long winningLotteryTicket(vector<string> tickets) {
    constexpr int ALL_DIGITS = (1 << 10) - 1;
    constexpr int MAX_MASKS = 1 << 10;
    long maskCount[MAX_MASKS] = {0}; // All possible numbers in range [1,10^6]
    // Mask is used as index into array

    for (const string& ticket : tickets) {
        int mask = 0;
        for (char ch : ticket) {
            if (ch != '\0') {
                mask |= 1 << (ch - '0');
            }
        }
        maskCount[mask]++;
    }

    long winning = 0;

    for (int first = 0; first < MAX_MASKS; first++) {
        if (maskCount[first] == 0) { continue; }
        if ((first | first) == ALL_DIGITS) { // Same value
            long count = maskCount[first];
            winning += count * (count - 1) / 2; // Removing self pairs
        }

        for (int second = first + 1; second < MAX_MASKS; second++) { // Checking if other masks complete
            if (maskCount[second] == 0) { continue; }

            if ((first | second) == ALL_DIGITS) {
                winning += maskCount[first] * maskCount[second]; // Any of first can pair with second
            }
        }
    }

    return winning;
}

int main()
{
    vector<string> tickets = {
        "129300455",
        "5559948277",
        "012334556",
        "56789",
        "123456879",
    };

    long result = winningLotteryTicket(tickets);

    cout << result << "\n";

    return 0;
}
