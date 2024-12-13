#include <iostream>
#include <stdexcept>
using namespace std;
class Stack {
private:
    int* arr;      
    int top;       
    int capacity;  

public:

    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }
    void push(int value) {
        if (top == capacity - 1) {
            throw overflow_error("Stack Overflow");
        }
        arr[++top] = value;
    }

    
    int pop() {
        if (top == -1) {
            throw underflow_error("Stack Underflow");
        }
        return arr[top--];
    }

    int peek() const {
        if (top == -1) {
            throw underflow_error("Stack is Empty");
        }
        return arr[top];
    }

    ~Stack() {
        delete[] arr;
    }
};

class Queue {
private:
    int* arr;      
    int front;     
    int rear;      
    int capacity;  
    int size;      

public:
    // Constructor
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    // Enqueue operation to add an element to the queue
    void enqueue(int value) {
        if (size == capacity) {
            throw overflow_error("Queue Overflow");
        }
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        size++;
    }

    // Dequeue operation to remove the front element from the queue
    int dequeue() {
        if (size == 0) {
            throw underflow_error("Queue Underflow");
        }
        int dequeuedValue = arr[front];
        front = (front + 1) % capacity;
        size--;
        return dequeuedValue;
    }

    // Front operation to view the front element
    int frontElement() const {
        if (size == 0) {
            throw underflow_error("Queue is Empty");
        }
        return arr[front];
    }

    // Destructor to free memory
    ~Queue() {
        delete[] arr;
    }
};

int main() {
    Stack stack(5);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Top element in Stack: " << stack.peek() << endl;
    cout << "Popped element from Stack: " << stack.pop() << endl;

    try {
        cout << "Popped element from Stack: " << stack.pop() << endl;
        cout << "Popped element from Stack: " << stack.pop() << endl;
        cout << "Popped element from Stack: " << stack.pop() << endl; 
    } catch (const underflow_error& e) {
        cout << e.what() << endl;
    }
    Queue queue(5);
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    cout << "Front element in Queue: " << queue.frontElement() << endl;
    cout << "Dequeued element from Queue: " << queue.dequeue() << endl;

    try {
        cout << "Dequeued element from Queue: " << queue.dequeue() << endl;
        cout << "Dequeued element from Queue: " << queue.dequeue() << endl;
        cout << "Dequeued element from Queue: " << queue.dequeue() << endl; 
    } catch (const underflow_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
