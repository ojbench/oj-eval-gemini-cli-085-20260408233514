#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

/**
 * Builds a binary tree from the extended preorder traversal sequence.
 * Reads from standard input.
 * -1 represents a null node.
 * -2 represents the end of the input sequence.
 * 
 * @return The root of the constructed binary tree.
 */
Node* buildTree() {
    int val;
    // Read the next value. If EOF or -2 is encountered, return nullptr.
    if (!(cin >> val) || val == -2) {
        return nullptr;
    }
    // -1 indicates a null node.
    if (val == -1) {
        return nullptr;
    }
    
    // Create the current node and recursively build its left and right subtrees.
    Node* node = new Node(val);
    node->left = buildTree();
    node->right = buildTree();
    return node;
}

/**
 * Recursively prunes the binary tree.
 * A subtree is pruned if and only if all nodes in the subtree have the value 0.
 * 
 * @param node The root of the current subtree.
 * @return true if the subtree rooted at `node` should be pruned, false otherwise.
 */
bool prune(Node* node) {
    // An empty subtree is considered prunable.
    if (!node) {
        return true;
    }
    
    // Recursively prune the left and right subtrees.
    bool left_prune = prune(node->left);
    bool right_prune = prune(node->right);
    
    // If the left subtree should be pruned, delete it to prevent memory leaks.
    if (left_prune) {
        delete node->left;
        node->left = nullptr;
    }
    
    // If the right subtree should be pruned, delete it to prevent memory leaks.
    if (right_prune) {
        delete node->right;
        node->right = nullptr;
    }
    
    // The current node can be pruned if its value is 0 and both its subtrees can be pruned.
    if (node->val == 0 && left_prune && right_prune) {
        return true;
    }
    
    return false;
}

// Global variable to handle spacing in the output.
bool first = true;

/**
 * Prints the extended preorder traversal of the binary tree.
 * 
 * @param node The root of the current subtree.
 */
void printTree(Node* node) {
    if (!first) {
        cout << " ";
    }
    first = false;
    
    // If the node is null, print -1.
    if (!node) {
        cout << "-1";
        return;
    }
    
    // Print the current node's value and recursively print its subtrees.
    cout << node->val;
    printTree(node->left);
    printTree(node->right);
}

/**
 * Recursively deletes the binary tree to free allocated memory.
 * 
 * @param node The root of the current subtree.
 */
void deleteTree(Node* node) {
    if (!node) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    // Optimize standard I/O operations for performance.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Step 1: Build the binary tree from input.
    Node* root = buildTree();
    
    // Step 2: Prune the binary tree.
    // If the entire tree should be pruned, delete the root and set it to nullptr.
    if (prune(root)) {
        delete root;
        root = nullptr;
    }
    
    // Step 3: Print the pruned binary tree.
    printTree(root);
    cout << "\n";
    
    // Step 4: Clean up remaining allocated memory.
    deleteTree(root);
    
    return 0;
}