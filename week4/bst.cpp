#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);  
        } else {
            node->right = insert(node->right, value); 
        }
        return node;
    }


    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);  
            cout << node->data << " ";  
            inorder(node->right);  
        }
    }


    bool search(Node* node, int value) {
        if (node == nullptr) {
            return false; 
        }
        if (node->data == value) {
            return true; // Value found
        } else if (value < node->data) {
            return search(node->left, value); 
        } else {
            return search(node->right, value); 
        }
    }

 
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left; // Traverse left until we find the minimum
        }
        return node;
    }

    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node; // Node not found
        }

        // Recur down the tree
        if (value < node->data) {
            node->left = deleteNode(node->left, value); 
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value); 
        } else {
            // Node to be deleted found
            if (node->left == nullptr) {
                Node* temp = node->right; 
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left; 
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);


            node->data = temp->data;


            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

public:
  
    BST() {
        root = nullptr;
    }
    void insert(int value) {
        root = insert(root, value);
    }
    void inorder() {
        inorder(root);
        cout << endl;
    }
    bool search(int value) {
        return search(root, value);
    }
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "In-order Traversal: ";
    tree.inorder();  // Output: 20 30 40 50 60 70 80

    int searchValue = 40;
    if (tree.search(searchValue)) {
        cout << searchValue << " found in the BST." << endl;
    } else {
        cout << searchValue << " not found in the BST." << endl;
    }

    tree.deleteNode(20);
    cout << "After deleting 20, In-order Traversal: ";
    tree.inorder();  // Output: 30 40 50 60 70 80

    tree.deleteNode(70);
    cout << "After deleting 70, In-order Traversal: ";
    tree.inorder();  // Output: 30 40 50 60 80

    tree.deleteNode(50);
    cout << "After deleting 50, In-order Traversal: ";
    tree.inorder();  // Output: 30 40 60 80

    return 0;
}
