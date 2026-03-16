#include <cinttypes>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

bool path_sum(BinarySearchTreeNode* tree, int target) {
    if (!tree) { return false; }
    if (!tree->left && !tree->right) { return target == tree->data; }
    bool left = path_sum(tree->left, target - tree->data);
    bool right = path_sum(tree->right, target - tree->data);

    return left || right;
}

struct path_test_t {
    std::vector<int> data;
    int target;
    bool expected;
};

void test_path_sum() {
    std::vector<path_test_t> tests = {
        path_test_t {
            .data = {5,4,8,11,-1,13,4,7,2,-1,-1,-1,1},
            .target = 22,
            .expected = true
        },
        path_test_t {
            .data = { 1, 2, 3 },
            .target = 5,
            .expected = false
        },
        path_test_t {
            .data = {  },
            .target = 0,
            .expected = false
        },
    };

    for (path_test_t& test : tests) {
        BinarySearchTreeNode* root = nullptr;

        for (int node : test.data) {
            root = insert_node_into_binary_search_tree(root, node);
        }

        bool output = path_sum(root, test.target);
        std::cout << "\n----------------------------------------------------\n";
        std::cout << "Found:    " << (output ? "True" : "False") << "\n";
        std::cout << "Expected: " << (test.expected ? "True" : "False") << "\n";
        std::cout << "Match:    " << (output == test.expected ? "True" : "False") << "\n";
    }
}

void sum_paths_driver(BinarySearchTreeNode* tree, int target, std::vector<int>& path, std::vector<std::vector<int>>& paths) {
    if (!tree) { return; }

    path.push_back(tree->data);
    if (!tree->left && !tree->right) {
        if (tree->data == target) {
            paths.push_back(path);
        }
    } else {
        sum_paths_driver(tree->left, target - tree->data, path, paths);
        sum_paths_driver(tree->right, target - tree->data, path, paths);
    }
    path.pop_back();
}

std::vector<std::vector<int>> sum_paths(BinarySearchTreeNode* tree, int target) {
    std::vector<std::vector<int>> paths;
    std::vector<int> path;

    sum_paths_driver(tree, target, path, paths);

    return paths;
}

struct all_path_test_t {
    std::vector<int> data;
    int target;
    std::vector<std::vector<int>> expected;
};

void test_all_paths() {
    std::vector<all_path_test_t> tests = {
        all_path_test_t {
            .data = { 5,4,8,11,13,4,7,2,5,1 },
            .target = 22,
            .expected = { {5,4,11,2},{5,8,4,5} },
        },
        all_path_test_t {
            .data = { 1, 2, 3 },
            .target = 5,
            .expected = { },
        },
        all_path_test_t {
            .data = { 1, 2 },
            .target = 0,
            .expected = { },
        },
    };

    for (all_path_test_t& test : tests) {
        BinarySearchTreeNode* root = nullptr;

        for (int node : test.data) {
            root = insert_node_into_binary_search_tree(root, node);
        }

        std::vector<std::vector<int>> output = sum_paths(root, test.target);

        std::cout << "Found:\n";
        for (std::vector<int>& path : output) {
            print_vector(path);
        }
        std::cout << "\nExpected:\n";
        for (std::vector<int>& path : test.expected) {
            print_vector(path);
        }

        bool match = output.size() == test.expected.size();
        for (size_t i = 0; i < output.size() && match; i++) {
            if (output[i] != test.expected[i]) {
                match = false;
                break;
            }
        }
        std::cout << "Match: " << (match ? "True" : "False") << "\n";
    }
}

int tree_height(BinarySearchTreeNode* tree) {
    if (!tree) { return -1; }
    return 1 + std::max(tree_height(tree->left), tree_height(tree->right));
}

void test_tree_height() {
    std::vector<int> data = { 3, 2, 1, 5, 4, 6, 7 };
    int expected = 3;

    BinarySearchTreeNode* root = nullptr;
    for (int node : data) {
        root = insert_node_into_binary_search_tree(root, node);
    }

    int output = tree_height(root);
    std::cout << "Output:   " << output << "\n";
    std::cout << "Expected: " << expected << "\n";
    std::cout << "Match:    " << (output == expected ? "True" : "False") << "\n";
}

bool check_bst(BinarySearchTreeNode* root) {
    if (!root) { return false; }
        bool left = true;
        bool right = true;

    if (root->left) {
        if (root->left->data >= root->data) {
            return false;
        } else {
            left = check_bst(root->left);
        }
    }

    if (root->right) {
        if (root->right->data <= root->data) {
            return false;
        } else {
            right = check_bst(root->right);
        }
    }

    return left && right;
}


void test_check_tree() {
    bool expected;

    BinarySearchTreeNode* root = new BinarySearchTreeNode(3);
    root->left = new BinarySearchTreeNode(5);
    root->left->left = new BinarySearchTreeNode(1);
    root->left->right = new BinarySearchTreeNode(4);

    root->right = new BinarySearchTreeNode(2);
    root->right->left = new BinarySearchTreeNode(6);

    bool output = check_bst(root);
    std::cout << "Output:   " << output << "\n";
    std::cout << "Expected: " << expected << "\n";
    std::cout << "Match:    " << (output == expected ? "True" : "False") << "\n";
}

int main(void) {
    test_check_tree();
}
