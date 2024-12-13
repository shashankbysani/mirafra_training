#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool isThreaded;

    Node(int value) : data(value), left(nullptr), right(nullptr), isThreaded(false) {}
};

class ThreadedBST {
private:
    Node* root;

    Node* leftmost(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

public:
    ThreadedBST() : root(nullptr) {}
    void insert(int value) {
        if (!root) {
            root = new Node(
                value);
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->data) {
                if (!current->left)
                    break;
                current = current->left;
            } else {
                if (current->isThreaded)
                    break;
                if (!current->right)
                    break;
                current = current->right;
            }
        }

        Node* newNode = new Node(value);
        if (value < parent->data) {
            parent->left = newNode;
            newNode->right = parent;
            newNode->isThreaded = true;
        } else {
            if (parent->isThreaded) {
                newNode->right = parent->right;
                newNode->isThreaded = true;
                parent->isThreaded = false;
            }
            parent->right = newNode;
        }
    }
    void inorder() {
        Node* current = leftmost(root);

        while (current) {
            cout << current->data << " ";
            if (current->isThreaded)
                current = current->right;
            else
                current = leftmost(current->right);
        }
    }
};

int main() {
    ThreadedBST tbst;
    tbst.insert(20);
    tbst.insert(10);
    tbst.insert(30);
    tbst.insert(5);
    tbst.insert(15);
    tbst.insert(25);
    tbst.insert(35);

    cout << "Inorder Traversal: ";
    tbst.inorder();
    cout << endl;

    return 0;
}
