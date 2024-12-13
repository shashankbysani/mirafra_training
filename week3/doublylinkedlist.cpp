#include <iostream>
using namespace std;
class Node {
public:
    int data;   
    Node* prev; 
    Node* next; 

    Node(int value) { 
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Class for Doubly Linked List
class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() {
        head = nullptr;
    }
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) { 
            temp = temp->next;
        }
        temp->next = newNode;   
        newNode->prev = temp;   
    }
    void displayForward() {
        Node* temp = head;
        cout << "Doubly Linked List (Forward): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void displayReverse() {
        if (head == nullptr) return;

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        cout << "Doubly Linked List (Reverse): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
    ~DoublyLinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList d11;

    dlo.insertAtEnd(10);
    dlo.insertAtEnd(20);
    dlo.insertAtEnd(30);
    dlo.insertAtEnd(40);
    dlo.displayForward();
    dlo.displayReverse();
}
