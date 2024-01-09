#include <iostream>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(NULL), right(NULL), height(1) {}
};

class AVLTree {
public:
    Node* insert(Node* root, int key) {
        if (!root) {
            return new Node(key);
        }

        if (key < root->key) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1) {
            if (key < root->left->key) {
                return rotateRight(root);
            } else {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }

        if (balance < -1) {
            if (key > root->right->key) {
                return rotateLeft(root);
            } else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        return root;
    }

    int getHeight(Node* node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (!node) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateLeft(Node* y) {
        Node* x = y->right;
        Node* T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* rotateRight(Node* x) {
        Node* y = x->left;
        Node* T2 = y->right;

        y->right = x;
        x->left = T2;

        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    void preorderTraversal(Node* root) {
        if (!root) {
            return;
        }
        std::cout << root->key << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
};

int main() {
    AVLTree avl;
    Node* root = NULL;
    int keys[] = {30, 10, 20, 25, 40, 50};
    
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i) {
        root = avl.insert(root, keys[i]);
    }

    std::cout << "Preorder Traversal dari AVL Tree yang Seimbang: ";
    avl.preorderTraversal(root);

    return 0;
}
