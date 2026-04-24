#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const char* bool_to_str(bool value) {
    return value ? "True" : "False";
}

template<typename T> void print_vector(std::vector<T> vector, bool new_line = true) {
    std::cout << "[ ";
    size_t i = 0;
    for (size_t i = 0; i < vector.size(); i++) {
        if (i < vector.size() - 1) {
            std::cout << vector[i] << ", ";
        } else {
            std::cout << vector[i];
        }
    }
    if (new_line) {
        std::cout << " ] \n";
    } else {
        std::cout << " ]";
    }
}

void mini_max(std::vector<int>& arr) {
    int min = INT_MAX;
    int max = 0;
    int64_t total = 0;

    for (int value : arr) {
        if (value < min) {
            min = value;
        } 
        if (value > max) {
            max = value;
        }

        total += value;
    }

    std::cout << total - max << " " << total - min << "\n";
}

struct mini_max_test_t {
    std::vector<int> array;
    std::string expected;
};

void test_mini_max() {
    std::vector<mini_max_test_t> tests = {
        mini_max_test_t {
            .array = { 1, 2, 3, 4, 5 },
            .expected = "10 14"
        }
    };

    for (mini_max_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::cout << "Input:    ";
        print_vector(test.array);

        std::cout << "Output:   ";
        mini_max(test.array);

        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "------------------------------------\n";
    }
}

class big_string_compare_t {
public:
    bool operator()(const std::string& l, const std::string& r) {
        if (l.size() != r.size()) {
            return l.size() < r.size();
        } else {
            return l <= r;
        }
    }
};

std::vector<std::string> big_sort(std::vector<std::string>& numbers) {
    std::stable_sort(numbers.begin(), numbers.end(), big_string_compare_t {});
    return numbers;
}

struct big_sort_test_t {
    std::vector<std::string> input;
    std::vector<std::string> expected;

};

void test_big_sort() {
    std::vector<big_sort_test_t> tests = {
        big_sort_test_t {
            .input = { 
                "6",
                "31415926535897932384626433832795",
                "1",
                "3",
                "10",
                "3",
            },
            .expected = {
                "1",
                "3",
                "3",
                "6",
                "10",
                "31415926535897932384626433832795",
            }
        }
    };

    for (big_sort_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::cout << "Input:    ";
        print_vector(test.input);
        std::cout << "Expected: ";
        print_vector(test.expected);
        std::cout << "Output:   ";
        std::vector<std::string> output = big_sort(test.input);
        print_vector(output);
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

struct freq_char_t {
    char ch;
    int count;
};

struct compare_freq_t {

    bool operator()(const freq_char_t& l, const freq_char_t& r) {
        if (l.count == r.count) {
            return l.ch <= r.ch;
        }
        return l.count > r.count;
    };
};


std::string freq_sort(std::string& s) {
    constexpr size_t chars = 128;
    std::vector<freq_char_t> freq = std::vector<freq_char_t>(chars);
    for (char ch : s) {
        freq[ch].ch = ch;
        freq[ch].count++;
    }

    std::stable_sort(freq.begin(), freq.end(), compare_freq_t {});

    std::string str;
    str.reserve(s.size());

    for (int i = 0; i < chars; i++) {
        if (freq[i].ch == '\0') { continue; }
        for (int j = 0; j < freq[i].count; j++) {
            str.push_back(freq[i].ch);
        }
    }

    return str;
}

struct freq_sort_test_t {
    std::string input;
    std::string expected;
};

void test_freq_sort() {
    std::vector<freq_sort_test_t> tests = {
        freq_sort_test_t {
            .input = "cccaaa",
            .expected = "aaaccc",
        }
    };

    for (freq_sort_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::string output = freq_sort(test.input);
        std::cout << "Input:    " << test.input << "\n";
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

struct num_freq_t {
    int num;
    int count;
};

struct compare_num_freq_t {

    bool operator()(const num_freq_t& l, const num_freq_t& r) {
        if (l.count == r.count) {
            return l.num <= r.num;
        }
        return l.count >= r.count;
    };
};

std::vector<int> top_k_freq(std::vector<int>& nums, int k, bool faster) {
    std::unordered_map<int, int> mapped;
    std::vector<num_freq_t> sorted;
    for (int value : nums) {
        if (!mapped.count(value)) {
            mapped[value] = (int) sorted.size();
            sorted.push_back(num_freq_t { value, 1 });
        } else {
            sorted[mapped[value]].count++;
        }
    }

    std::stable_sort(sorted.begin(), sorted.end(), compare_num_freq_t {});

    std::vector<int> top_k = std::vector<int>(k);

    for (int i = 0; i < k; i++) {
        top_k[i] = sorted[i].num;
    }

    return top_k;
}

std::vector<int> top_k_freq(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> mapped;
    for (int value : nums) {
        mapped[value]++;
    }
    std::vector<num_freq_t> sorted = std::vector<num_freq_t>(0);
    sorted.reserve(mapped.size());

    for (const std::pair<int, int>& pair : mapped) {
        sorted.push_back(num_freq_t { pair.first, pair.second });
    }

    std::stable_sort(sorted.begin(), sorted.end(), compare_num_freq_t {});

    std::vector<int> top_k = std::vector<int>(k);

    for (int i = 0; i < k; i++) {
        top_k[i] = sorted[i].num;
    }

    return top_k;
}

std::vector<int> top_k_freq(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> mapped;
    for (int value : nums) {
        mapped[value]++;
    }
    std::vector<num_freq_t> sorted = std::vector<num_freq_t>(0);
    sorted.reserve(mapped.size());

    for (const std::pair<int, int>& pair : mapped) {
        sorted.push_back(num_freq_t { pair.first, pair.second });
    }

    std::stable_sort(sorted.begin(), sorted.end(), compare_num_freq_t {});

    std::vector<int> top_k = std::vector<int>(k);

    for (int i = 0; i < k; i++) {
        top_k[i] = sorted[i].num;
    }

    return top_k;
}
std::vector<int> top_k_freq(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> mapped;
    for (int value : nums) {
        mapped[value]++;
    }
    std::vector<num_freq_t> sorted = std::vector<num_freq_t>(0);
    sorted.reserve(mapped.size());

    for (const std::pair<int, int>& pair : mapped) {
        sorted.push_back(num_freq_t { pair.first, pair.second });
    }

    std::stable_sort(sorted.begin(), sorted.end(), compare_num_freq_t {});

    std::vector<int> top_k = std::vector<int>(k);

    for (int i = 0; i < k; i++) {
        top_k[i] = sorted[i].num;
    }

    return top_k;
}

struct top_k_freq_test_t {
    int k;
    std::vector<int> nums;
    std::vector<int> expected;
};

void test_top_k_freq() {
    std::vector<top_k_freq_test_t> tests = {
        top_k_freq_test_t {
            .k = 2,
            .nums = { 1, 1, 1, 2, 2, 2, 3 },
            .expected = { 1, 2 }
        }
    };

    for (top_k_freq_test_t& test : tests) {
        std::cout << "\n------------------------------------\n";
        std::vector<int> output = top_k_freq(test.nums, test.k);
        std::cout << "Input: K:" << test.k << ": ";
        print_vector(test.nums);
        std::cout << "Output:   ";
        print_vector(output);
        std::cout << "Expected: ";
        print_vector(test.expected);
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "------------------------------------\n";
    }
}

int main(void) {
    test_top_k_freq();
}
