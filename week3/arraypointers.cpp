#include <iostream>
using namespace std;

int main() {
    
    int* arr[3];
    arr[0] = new int(10); 
    arr[1] = new int(20); 
    arr[2] = new int(30); 
    cout << "Values in the array of pointers:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] = " << *arr[i] << endl;
    }
    *arr[1] = 50; // Changing the value at pointer 1

    cout << "\nValues after modification:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] = " << *arr[i] << endl;
    }
    for (int i = 0; i < 3; i++) {
        delete arr[i];
    }

    cout << "\nMemory is free." << endl;

    return 0;
}
