#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* buildTree() {
    int val;
    if (!(cin >> val) || val == -2) {
        return nullptr;
    }
    if (val == -1) {
        return nullptr;
    }
    Node* node = new Node(val);
    node->left = buildTree();
    node->right = buildTree();
    return node;
}

bool prune(Node* node) {
    if (!node) return true;
    bool left_prune = prune(node->left);
    bool right_prune = prune(node->right);
    
    if (left_prune) {
        delete node->left;
        node->left = nullptr;
    }
    if (right_prune) {
        delete node->right;
        node->right = nullptr;
    }
    
    if (node->val == 0 && left_prune && right_prune) {
        return true;
    }
    return false;
}

bool first = true;
void printTree(Node* node) {
    if (!first) cout << " ";
    first = false;
    if (!node) {
        cout << "-1";
        return;
    }
    cout << node->val;
    printTree(node->left);
    printTree(node->right);
}

void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Node* root = buildTree();
    if (prune(root)) {
        delete root;
        root = nullptr;
    }
    
    printTree(root);
    cout << "\n";
    
    deleteTree(root);
    
    return 0;
}

