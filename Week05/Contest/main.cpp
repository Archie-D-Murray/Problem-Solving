#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <ostream>
#include <unordered_map>
#include <utility>
#include <vector>

class BinarySearchTreeNode {
public:
    int data;
    BinarySearchTreeNode* left;
    BinarySearchTreeNode* right;

    BinarySearchTreeNode(int node_data) {
        data = node_data;
        left = right = NULL;
    }
};

BinarySearchTreeNode* insert_node_into_binary_search_tree(BinarySearchTreeNode* root, int node_data) {
    if (!root) {
        root = new BinarySearchTreeNode(node_data);
    } else {
        if (node_data <= root->data) {
            root->left = insert_node_into_binary_search_tree(root->left, node_data);
        } else {
            root->right = insert_node_into_binary_search_tree(root->right, node_data);
        }
    }

    return root;
}

void print_binary_search_tree_inorder_traversal(BinarySearchTreeNode* root, std::string sep, std::ofstream& fout) {
    if (!root) {
        return;
    }

    print_binary_search_tree_inorder_traversal(root->left, sep, fout);

    if (root->left) {
        fout << sep;
    }

    fout << root->data;

    if (root->right) {
        fout << sep;
    }

    print_binary_search_tree_inorder_traversal(root->right, sep, fout);
}

/*
 * Complete the 'GetDepth' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_BINARY_SEARCH_TREE tree
 *  2. INTEGER k
 */

/*
 * For your reference:
 *
 * BinarySearchTreeNode {
 *     int data;
 *     BinarySearchTreeNode* left;
 *     BinarySearchTreeNode* right;
 * };
 *
 */

void ParentDriver(BinarySearchTreeNode* node, int search, int* parent) {
    if (!node) { return; }

    if (node->data == search) {
        return;
    } else if (node->data > search) {
        *parent = node->data;
        ParentDriver(node->left, search, parent);
    } else {
        *parent = node->data;
        ParentDriver(node->right, search, parent);
    }
}

int DepthDriver(BinarySearchTreeNode* node, int search, int depth) {
    if (!node) {
        return -1;
    }

    if (node->data == search) {
        return depth;
    } else if (node->data > search) {
        return DepthDriver(node->left, search, depth + 1);
    } else {
        return DepthDriver(node->right, search, depth + 1);
    }
}

int GetParent(BinarySearchTreeNode* tree, int k) {
    int parent = -1;
    ParentDriver(tree, k, &parent);

    return parent;
}

int GetDepth(BinarySearchTreeNode* tree, int k) {
    return DepthDriver(tree, k, 0);
}

struct depth_test_t {
    std::vector<int> inputs;
    int search;
    int expected;
};

void test_depth() {
    std::vector<depth_test_t> tests = {
        { { 30028, 46260, 59582, 16018, 20647, }, 16018, 1 },
        { { 67180, 80995, 87549, 92737, 95165, 81904, 83360, 72730, 73595, 80763, 68052, 44563, 48994, 49926, 61164, 47881, 7021, 13996, 24827, 2393 }, 23548, -1 },
    };

    for (depth_test_t& test : tests) {
        BinarySearchTreeNode* root = nullptr;
        for (int value : test.inputs) {
            root = insert_node_into_binary_search_tree(root, value);
        }
        int depth = GetDepth(root, test.search);

        std::cout << "Found " << test.search << " at depth " << depth << " expected: " << test.expected << "\n";
    }

}

void test_parent() {
    
    std::vector<depth_test_t> tests = {
        { { 66283, 79227, 81447, 43367, 59575 }, 81447, 79227 },
        { { 68331, 81258, 16731, 26836, 57643, 42580, 80776, 49054, 88086, 69957, 68917, 95745, 95609, 35336, 12705, 12209, 30430, 20657, 75884, 69224 }, 68331, -1 },
    };

    for (depth_test_t& test : tests) {
        BinarySearchTreeNode* root = nullptr;
        for (int value : test.inputs) {
            root = insert_node_into_binary_search_tree(root, value);
        }
        int parent = GetParent(root, test.search);

        std::cout << "Found " << test.search << " with parent " << parent << " expected: " << test.expected << "\n";
    }
}

std::string is_heap(std::vector<int>& arr) {
    if (arr.size() < 2) { return "Neither"; }
    bool max = arr[0] > arr[1];
    for (size_t i = 0; 2 * i + 2 < arr.size(); i++) {
        if (max) {
            if (arr[i] < arr[2 * i + 1] || arr[i] < arr[2 * i + 2]) {
                return "Neither";
            }
        } else {
            if (arr[i] > arr[2 * i + 1] || arr[i] > arr[2 * i + 2]) {
                return "Neither";
            }
        }
    }

    return max ? "Max" : "Min";
}

struct heap_test_t {
    std::vector<int> arr;
    std::string expected;
};

void test_heap() {
    std::vector<heap_test_t> tests = {
        heap_test_t {
            .arr = { 98215, 71775, 95635, 37514, 65570, 77259, 87886, 7848 },
            .expected = "Max"
        },
        heap_test_t {
            .arr = {165, 1217, 23582, 7907, 7039, 45039, 86416, 78843, 67420, 93903, 85839, 86473},
            .expected = "Min"
        },
        heap_test_t {
            .arr = {32319, 61352, 18302, 91880, 25160, 53643, 45346, 2434, 11738, 51769, 44052, 8368, 55129, 35148, 18811, 97159, 88247, 55284, 39313, 32498},
            .expected = "Neither"
        },
    };

    for (heap_test_t& test : tests) {
        std::string output = is_heap(test.arr);
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Found:    " << output << "\n";
        std::cout << "Match:    " << (test.expected == output ? "TRUE" : "FALSE") << "\n";
        std::cout << "\n";
    }
}

int max_even(BinarySearchTreeNode* tree) {
    if (!tree || tree->data & 1) { return 0; }

    int left = max_even(tree->left);
    int right = max_even(tree->right);

    return tree->data + std::max(left, right);
}

struct max_test_t {
    std::vector<int> arr;
    int expected;
};

void test_max_even() {
    std::vector<max_test_t> tests = {
        max_test_t { 
            .arr = { 63144, 77162, 84092, 44215, 52331 },
            .expected = 224398
        },
        max_test_t { 
            .arr = { 47446, 82216, 96928, 98437, 98620, 84882, 94903, 60156, 74960, 75661, 57106, 22064, 35952, 43027, 44197, 31382, 12075, 12551, 15088, 2121 },
            .expected = 311472
        },
        max_test_t { 
            .arr = { 6352, 26718, 73638, 41108, 73455, 56991, 69122, 5562, 69939, 27471, 83575, 45955, 13487, 16578, 22833, 17598, 93689, 22930, 39993, 9266 },
            .expected = 147816
        },
        max_test_t { 
            .arr = { 18336, 51277, 24496, 23147, 21577, 49085, 12328, 60708, 2185, 43028, 50540, 28232, 556, 68448, 53789, 28097, 9308, 43161, 20585, 53078 },
            .expected = 30664
        },
    };

    for (max_test_t& test : tests) {

        BinarySearchTreeNode* root = nullptr;

        for (int value : test.arr) {
            root = insert_node_into_binary_search_tree(root, value);
        }

        int output = max_even(root);
        std::cout << "Expected: " << test.expected << "\n";
        std::cout << "Found:    " << output << "\n";
        std::cout << "Match:    " << (test.expected == output ? "TRUE" : "FALSE") << "\n";
        std::cout << "\n";
    }
}

int main(void) {
    test_max_even();
}
