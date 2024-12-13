#include <iostream>
#include <algorithm>  
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;  

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;  
    }
};

class AVLTree {
private:
    Node* root;
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* node) {
        Node* leftChild = node->left;
        Node* rightOfLeftChild = leftChild->right;

     
        leftChild->right = node;
        node->left = rightOfLeftChild;

       
        updateHeight(node);
        updateHeight(leftChild);

        return leftChild;  
    }

    // Left rotate subtree rooted with node
    Node* leftRotate(Node* node) {
        Node* rightChild = node->right;
        Node* leftOfRightChild = rightChild->left;

        // Perform rotation
        rightChild->left = node;
        node->right = leftOfRightChild;

        // Update heights
        updateHeight(node);
        updateHeight(rightChild);

        return rightChild;  // New root
    }

    // Left-Right Rotation
    Node* leftRightRotate(Node* node) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left Rotation
    Node* rightLeftRotate(Node* node) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Insert a node into the AVL Tree
    Node* insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);  // Create new node if tree is empty
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            
            return node;
        }


        updateHeight(node);

      
        int balance = getBalanceFactor(node);

        

        // Left-Left case (Left Heavy)
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);

        // Right-Right case (Right Heavy)
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);

        // Left-Right case (Left Heavy but Right child is deeper)
        if (balance > 1 && value > node->left->data)
            return leftRightRotate(node);


        if (balance < -1 && value < node->right->data)
            return rightLeftRotate(node);

        return node;  
    }

  
    void inOrder(Node* node) {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

public:
    // Constructor
    AVLTree() {
        root = nullptr;
    }

    // Insert a value into the AVL tree
    void insertValue(int value) {
        root = insert(root, value);
    }

    // Perform in-order traversal
    void inOrderTraversal() {
        cout << "In-order Traversal: ";
        inOrder(root);
        cout << endl;
    }
};
int main() {
    AVLTree tree;

    // Inserting nodes into the AVL Tree
    tree.insertValue(50);
    tree.insertValue(30);
    tree.insertValue(20);
    tree.insertValue(40);
    tree.insertValue(70);
    tree.insertValue(60);
    tree.insertValue(80);
    tree.inOrderTraversal();  // Output: In-order Traversal: 20 30 40 50 60 70 80

    return 0;
}
