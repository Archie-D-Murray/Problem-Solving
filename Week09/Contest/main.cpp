#include <cassert>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

struct ivec2 {
    int x;
    int y;

};

bool operator==(const ivec2& s, const ivec2& o) {
    return (s.x == o.x) && (s.y == o.y);
}

ivec2 operator-(const ivec2& l, const ivec2 r) {
    return ivec2 { l.x - r.x, l.y - r.y };
}

int magnitude(const ivec2& vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

template<> struct std::hash<ivec2> {
    std::size_t operator() (const ivec2& vec) const noexcept {
        return std::hash<int>{}(vec.x) ^ (std::hash<int>{}(vec.y) << 1);
    }
};

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

int leaderboard_position(std::string& name, std::vector<std::string>& leaderboard) {
    int found_score = -1;
    std::map<int, int> scores;

    for (std::string& entry : leaderboard) {
        size_t space = entry.find(' ');
        if (space == entry.npos) { continue; }
        int score = -1;
        if (!sscanf(entry.data() + space, "%d", &score)) { continue; }
        if (entry.substr(0, space) == name && score != -1) {
            found_score = score;
        }
        scores[score]++;
    }

    int place = 0;
    for (const std::pair<int, int>& score : scores) {
        if (score.first < found_score) {
            place += score.second;
        } else if (score.first == found_score ){
            place++;
            break;
        }
    }

    return place;
}

struct leaderboard_test_t {
    std::string name;
    std::vector<std::string> leaderboard;
    int expected;
};

void test_leaderboard() {
    std::vector<leaderboard_test_t> tests = {
        leaderboard_test_t {
            .name = "Tomasine",
            .leaderboard = {
                "Ardath 1",
                "Kerstin 1",
                "Tomasine 4",
                "Cordula 4",
                "Valene 1",
            },
            .expected = 4, 
        }
    };

    for (leaderboard_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        int output = leaderboard_position(test.name, test.leaderboard);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

struct point_t {
    ivec2 diff;
    int index;
};

class point_compare_less_t {
public:
    bool operator()(const point_t& s, const point_t& o) {
        return magnitude(s.diff) > magnitude(o.diff);
    }
};

int k_nearest_neighbour(int k, std::vector<std::vector<int>>& points) {
    ivec2 nearest = ivec2 { points[0][0], points[0][1] };
    std::priority_queue<point_t, std::vector<point_t>, point_compare_less_t> queue;

    for (size_t i = 1; i < points.size(); i++) {
        queue.push(point_t { 
            .diff = ivec2 { points[i][0], points[i][1] } - nearest, 
            .index = (int) i
        });
    }

    for (size_t i = 0; i < k - 1; i++) {
        queue.pop();
    }

    return queue.top().index;
}

struct nearest_neighbour_test_t {
    std::vector<std::vector<int>> points;
    int k;
    int expected;
};

void test_nearest_neighbour(void) {
    std::vector<nearest_neighbour_test_t> tests = {
        nearest_neighbour_test_t {
            .points = {
                { 4265, -3125 },
                { -14915, -12966 },
                { 626 ,-1058 },
                { -9387, 3399 },
                { 7811 ,-7897 },
                { -505, 4113 },
                { -1495, 7029 },
                { -6231, 13595 },
                { 13200, 6397 },
                { -5, 8896 },
            },
            .k = 5,
            .expected = 9
        },
        nearest_neighbour_test_t {
            .points = {
                { -15783, 7729 },
                { -15864, 1356 },
                { 2967, 3168 },
                { 4208, 2661 },
                { 16187, 15656 },
                { 1085, -12472 },
                { 12463, -7384 },
                { -15590, 2608 },
                { 13867, -5497 },
                { 12734, -14939 },
            },
            .k = 2,
            .expected = 1
        }
    };

    for (nearest_neighbour_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        int output = k_nearest_neighbour(test.k, test.points);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

int reverse_binary_search(std::vector<int>& values, int pattern, int nSearch) {
    size_t upper = values.size();
    size_t lower = 0;
    
    for (size_t i = 0; i < nSearch; i++) {
        if (pattern & 0x1) {
            lower = (lower + upper) / 2;
        } else {
            upper = (lower + upper) / 2;
        }
        pattern >>= 1;
    }

    return values[lower];
}

struct rev_bin_search_t {
    std::vector<int> values;
    int pattern;
    int searches;
    int expected;
};

void test_reverse_search(void) {
    std::vector<rev_bin_search_t> tests = {
        rev_bin_search_t {
            .values = { 
                50,82,91,161,265,335,436,624,773,953
            },
            .pattern = 0x1,
            .searches = 3,
            .expected = 335,
        },
        rev_bin_search_t {
            .values = { 
                23, 92, 200, 480, 795, 843, 871, 935, 937, 976
            },
            .pattern = 3,
            .searches = 3,
            .expected = 935,
        },
    };

    for (rev_bin_search_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        int output = reverse_binary_search(test.values, test.pattern, test.searches);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

struct entry_t {
    int time;
    int id;
};

int times_compare(const void* l, const void* r) {
    int compare = ((entry_t*) l)->time - ((entry_t*) r)->time;
    if (compare == 0) {
        return ((entry_t*) l)->id - ((entry_t*) r)->id;
    } else {
        return compare;
    }
}

int max_concurrent_occupancy(std::vector<std::vector<int>>& timesAndIDs) {
    std::vector<entry_t> entries = std::vector<entry_t>(timesAndIDs.size());
    for (size_t i = 0; i < timesAndIDs.size(); i++) {
        entries.push_back(entry_t { timesAndIDs[i][0], timesAndIDs[i][1] });
    }
    std::qsort(entries.data(), entries.size(), sizeof(entries[0]), &times_compare);

    size_t max_concurrent = 0;
    std::unordered_set<int> concurrent;
    for (const entry_t& entry : entries) {
        if (concurrent.count(entry.id)) {
            concurrent.erase(entry.id);
        } else {
            concurrent.insert(entry.id);
        }
        max_concurrent = std::max(concurrent.size(), max_concurrent);
    }

    return max_concurrent;
}

struct concurrent_occupancy_test_t {
    std::vector<std::vector<int>> data;
    int expected;
};

void test_max_concurrent_occupancy(void) {
    std::vector<concurrent_occupancy_test_t> tests = {
        concurrent_occupancy_test_t {
            .data = {{ 5, 11209 }, { 6, 59752 }, { 8, 11209 }, { 13, 39712 }, { 19, 39013 }, { 4, 39013 }, { 3, 66310 }, { 11, 39712 }, { 17, 59752 }, { 14, 66310  }},
            .expected = 4,
        },
        concurrent_occupancy_test_t {
            .data = {{ 7, 11909 }, { 19, 56077 }, { 5, 40847 }, { 15, 40847 }, { 9, 11909 }, { 15, 56077 }, { 11, 39117 }, { 2, 25117 }, { 11, 39117 }, { 19, 25117  }},
            .expected = 3,
        },
        concurrent_occupancy_test_t {
            .data = { { 19, 48413 }, { 2, 12491 }, { 13, 94996 }, { 2, 63118 }, { 19, 62627 }, { 20, 22914 }, { 16, 53350 }, { 18, 75057 }, { 14, 14469 }, { 19, 53350 }, { 12, 43751 }, { 13, 10809 }, { 6, 72612 }, { 6, 94245 }, { 10, 59370 }, { 16, 73618 }, { 12, 14492 }, { 15, 12491 }, { 4, 96975 }, { 7, 59370 }, { 11, 14469 }, { 10, 63118 }, { 16, 47918 }, { 16, 22914 }, { 5, 75057 }, { 4, 33360 }, { 9, 73618 }, { 15, 94245 }, { 17, 62627 }, { 5, 10809 }, { 9, 94103 }, { 0, 48413 }, { 19, 47918 }, { 8, 72612 }, { 15, 33360 }, { 4, 94103 }, { 0, 43751 }, { 0, 96975 }, { 3, 94996 }, { 14, 14492  }},
            .expected =  12,
        },
        concurrent_occupancy_test_t {
            .data = { { 17, 70002 }, { 9, 26674 }, { 3, 92936 }, { 2, 83330 }, { 1, 56702 }, { 5, 16209 }, { 10, 37308 }, { 12, 90648 }, { 6, 48807 }, { 19, 21022 }, { 11, 16209 }, { 5, 60929 }, { 3, 68191 }, { 17, 80856 }, { 19, 43127 }, { 2, 37308 }, { 10, 33665 }, { 11, 70002 }, { 12, 99922 }, { 3, 33665 }, { 12, 92936 }, { 13, 80856 }, { 9, 56702 }, { 5, 26674 }, { 3, 43127 }, { 15, 68191 }, { 2, 43107 }, { 16, 34364 }, { 2, 40874 }, { 18, 40874 }, { 7, 34364 }, { 5, 48807 }, { 8, 21022 }, { 13, 95672 }, { 8, 60929 }, { 12, 99922 }, { 19, 95672 }, { 12, 90648 }, { 6, 43107 }, { 15, 83330  }} ,
            .expected = 13,

        },
        concurrent_occupancy_test_t {
            .data = {
                { 549, 50953 }, { 121, 60716 }, { 891, 70054 }, { 8, 82918 }, { 66, 37639 }, { 13, 46292 }, { 134, 15891 }, { 12, 75069 }, { 362, 29192 }, { 502, 87775 }, { 371, 47494 }, { 976, 48596 }, { 579, 67838 }, { 635, 51606 }, { 174, 18747 }, { 21, 15186 }, { 723, 26620 }, { 395, 85474 }, { 708, 97422 }, { 781, 33042 }, { 629, 41703 }, { 873, 17361 }, { 374, 29192 }, { 72, 86835 }, { 403, 15138 }, { 823, 76588 }, { 855, 18277 }, { 297, 14013 }, { 638, 35733 }, { 595, 69184 }, { 301, 99175 }, { 382, 57092 }, { 812, 32244 }, { 245, 69614 }, { 374, 34078 }, { 763, 52463 }, { 749, 57890 }, { 595, 96677 }, { 526, 68915 }, { 184, 63853 }, { 32, 52463 }, { 765, 40875 }, { 923, 41510 }, { 376, 75418 }, { 557, 80755 }, { 633, 34229 }, { 912, 27866 }, { 499, 41204 }, { 12, 52388 }, { 850, 60297 }, { 212, 41510 }, { 957, 49576 }, { 730, 38750 }, { 630, 26620 }, { 804, 93089 }, { 241, 69220 }, { 167, 86015 }, { 265, 57397 }, { 10, 75028 }, { 497, 43348 }, { 682, 86050 }, { 147, 32244 }, { 747, 57890 }, { 955, 26829 }, { 846, 97334 }, { 989, 76617 }, { 479, 29503 }, { 708, 64480 }, { 673, 51614 }, { 214, 31446 }, { 323, 63182 }, { 893, 41750 }, { 904, 77201 }, { 752, 70054 }, { 758, 81568 }, { 683, 28705 }, { 943, 59663 }, { 716, 48026 }, { 99, 63590 }, { 795, 93616 }, { 240, 67838 }, { 999, 43511 }, { 794, 46673 }, { 522, 60646 }, { 356, 15891 }, { 4, 28070 }, { 327, 92320 }, { 366, 15892 }, { 823, 62398 }, { 408, 41204 }, { 990, 66102 }, { 490, 61383 }, { 435, 54822 }, { 816, 92818 }, { 934, 54960 }, { 361, 27433 }, { 556, 79222 }, { 57, 64480 }, { 601, 69653 }, { 173, 79065 }, { 596, 84590 }, { 513, 92320 }, { 661, 81568 }, { 908, 99088 }, { 369, 44264 }, { 354, 43881 }, { 474, 24022 }, { 330, 97730 }, { 817, 58025 }, { 914, 33785 }, { 115, 62336 }, { 796, 50953 }, { 878, 65488 }, { 533, 27866 }, { 920, 89770 }, { 389, 62398 }, { 2, 88965 }, { 203, 40875 }, { 826, 60297 }, { 65, 51508 }, { 764, 57924 }, { 427, 53026 }, { 904, 88919 }, { 196, 15186 }, { 18, 66278 }, { 704, 33190 }, { 688, 47494 }, { 256, 92086 }, { 500, 45123 }, { 697, 57924 }, { 902, 53738 }, { 400, 88510 }, { 697, 31446 }, { 204, 35163 }, { 159, 96677 }, { 294, 70800 }, { 869, 92086 }, { 836, 80483 }, { 576, 43209 }, { 66, 58025 }, { 492, 33042 }, { 374, 86015 }, { 894, 69184 }, { 533, 64383 }, { 844, 41703 }, { 751, 81814 }, { 721, 88703 }, { 978, 68915 }, { 434, 77289 }, { 49, 57092 }, { 768, 88703 }, { 508, 90790 }, { 457, 20266 }, { 550, 17122 }, { 239, 92844 }, { 562, 86735 }, { 533, 10755 }, { 344, 62037 }, { 751, 39681 }, { 431, 74269 }, { 209, 93871 }, { 676, 60742 }, { 679, 56118 }, { 65, 62039 }, { 289, 32007 }, { 854, 28149 }, { 253, 48026 }, { 412, 62039 }, { 471, 23660 }, { 390, 48525 }, { 632, 47885 }, { 136, 49576 }, { 724, 21624 }, { 803, 18277 }, { 546, 76921 }, { 753, 40356 }, { 798, 26829 }, { 750, 21068 }, { 791, 43579 }, { 688, 52388 }, { 913, 68989 }, { 941, 64863 }, { 864, 26809 }, { 462, 55682 }, { 276, 43881 }, { 352, 73065 }, { 358, 68989 }, { 499, 38750 }, { 265, 81594 }, { 682, 10982 }, { 858, 69846 }, { 621, 87775 }, { 721, 22972 }, { 775, 85184 }, { 579, 11695 }, { 975, 20266 }, { 536, 99650 }, { 354, 75028 }, { 931, 21068 }, { 862, 43579 }, { 499, 89770 }, { 691, 35733 }, { 745, 99469 }, { 977, 58091 }, { 750, 43348 }, { 103, 76937 }, { 257, 41028 }, { 475, 24022 }, { 377, 29299 }, { 964, 75418 }, { 273, 24654 }, { 336, 17361 }, { 614, 40692 }, { 952, 65651 }, { 738, 76921 }, { 66, 84781 }, { 873, 70800 }, { 757, 39229 }, { 731, 29057 }, { 65, 86835 }, { 608, 45123 }, { 981, 32295 }, { 318, 51508 }, { 721, 19275 }, { 426, 37443 }, { 620, 10200 }, { 383, 42641 }, { 693, 75956 }, { 340, 72100 }, { 570, 46842 }, { 106, 85184 }, { 376, 60716 }, { 14, 58729 }, { 585, 76617 }, { 91, 99650 }, { 695, 23660 }, { 510, 95406 }, { 969, 57397 }, { 363, 31938 }, { 718, 56118 }, { 862, 49950 }, { 9, 24654 }, { 977, 89365 }, { 485, 60742 }, { 145, 64666 }, { 595, 49950 }, { 685, 15200 }, { 983, 72100 }, { 558, 14013 }, { 215, 69220 }, { 853, 34229 }, { 761, 64383 }, { 344, 25559 }, { 637, 10755 }, { 596, 17122 }, { 233, 39681 }, { 252, 43209 }, { 301, 88965 }, { 851, 74269 }, { 118, 95502 }, { 457, 26809 }, { 754, 10960 }, { 704, 49141 }, { 725, 66746 }, { 405, 74253 }, { 39, 19275 }, { 806, 64666 }, { 350, 59663 }, { 183, 66278 }, { 477, 61383 }, { 441, 29503 }, { 487, 99088 }, { 503, 80755 }, { 44, 55682 }, { 946, 18162 }, { 24, 17587 }, { 232, 39665 }, { 699, 11695 }, { 866, 75069 }, { 866, 88919 }, { 76, 34078 }, { 93, 28705 }, { 878, 79222 }, { 958, 33190 }, { 254, 35163 }, { 69, 41750 }, { 686, 58729 }, { 27, 63590 }, { 75, 29299 }, { 680, 93871 }, { 910, 53026 }, { 193, 79401 }, { 847, 28483 }, { 134, 46292 }, { 903, 90790 }, { 639, 47885 }, { 845, 75956 }, { 219, 93616 }, { 876, 63182 }, { 232, 65651 }, { 682, 62770 }, { 530, 65488 }, { 558, 40356 }, { 813, 41028 }, { 865, 77201 }, { 984, 53102 }, { 586, 99175 }, { 128, 75089 }, { 584, 76588 }, { 757, 61609 }, { 343, 27433 }, { 273, 86735 }, { 372, 84270 }, { 248, 31938 }, { 18, 25520 }, { 824, 53102 }, { 896, 44264 }, { 587, 89365 }, { 712, 79065 }, { 86, 33785 }, { 520, 58091 }, { 690, 25559 }, { 854, 48596 }, { 37, 42641 }, { 124, 32295 }, { 226, 62770 }, { 625, 34881 }, { 491, 15138 }, { 698, 17587 }, { 761, 40692 }, { 618, 60646 }, { 38, 62336 }, { 966, 84590 }, { 181, 92844 }, { 906, 73065 }, { 560, 76937 }, { 184, 15730 }, { 391, 81594 }, { 229, 74253 }, { 321, 84270 }, { 482, 77289 }, { 364, 95406 }, { 820, 75089 }, { 59, 46673 }, { 459, 10200 }, { 103, 93089 }, { 477, 62037 }, { 763, 37443 }, { 839, 43511 }, { 705, 92818 }, { 406, 79401 }, { 666, 29057 }, { 879, 51606 }, { 187, 28149 }, { 401, 49141 }, { 703, 97334 }, { 413, 81814 }, { 916, 28070 }, { 415, 46842 }, { 915, 15200 }, { 95, 15892 }, { 855, 18162 }, { 616, 74598 }, { 908, 28483 }, { 35, 99469 }, { 994, 61609 }, { 531, 22972 }, { 626, 80483 }, { 160, 97422 }, { 958, 64863 }, { 138, 53738 }, { 393, 86050 }, { 320, 97730 }, { 936, 84781 }, { 242, 69614 }, { 583, 25520 }, { 314, 54960 }, { 510, 95502 }, { 957, 66102 }, { 969, 51614 }, { 634, 69653 }, { 665, 39229 }, { 17, 10960 }, { 936, 85474 }, { 471, 34881 }, { 289, 39665 }, { 0, 48525 }, { 435, 18747 }, { 296, 69846 }, { 400, 54822 }, { 697, 74598 }, { 202, 63853 }, { 133, 37639 }, { 979, 32007 }, { 208, 82918 }, { 364, 10982 }, { 429, 15730 }, { 822, 21624 }, { 438, 88510 }, { 472, 66746 },
            },
            .expected = 102,
        }
    };

    for (concurrent_occupancy_test_t& test : tests) {
        std::cout << "\n-------------------------------\n";
        int output = max_concurrent_occupancy(test.data);
        std::cout << "Output:   " << output << "\n";
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Match:    " << bool_to_str(output == test.expected) << "\n";
        std::cout << "-------------------------------\n";
    }
}

int main(void) {
    test_max_concurrent_occupancy();

    return 0;
}
