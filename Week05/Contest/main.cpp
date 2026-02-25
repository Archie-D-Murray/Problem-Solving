#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <ostream>
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

int main(void) {
    test_parent();
}
