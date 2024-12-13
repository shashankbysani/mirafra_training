#include <iostream>
#include <stack>
#include <queue>
#include <ctime>
#include <unistd.h>
using namespace std;

// Vehicle Class
class Vehicle {
public:
    string vehicleID;
    int priorityLevel; // normal=0,emergency=1
    time_t entryTime;
    time_t exitTime;

    Vehicle(string id, int priority) : vehicleID(id), priorityLevel(priority) {
        entryTime = time(nullptr); // entry time
    }

    void setExitTime() {
        exitTime = time(nullptr); // exit time
    }

    int getDuration() const {
        return difftime(exitTime, entryTime); //return the parkd time
    }
};

class ParkingBay {
    stack<Vehicle> parkingSlots;
    int maxCapacity;

public:
    ParkingBay(int capacity) : maxCapacity(capacity) {}

    bool isFull() const {
        return parkingSlots.size() >= maxCapacity;
    }

    bool isEmpty() const {
        return parkingSlots.empty();
    }

    void parkVehicle(const Vehicle &v) {
        if (isFull()) {
            cout << "Parking bay is full!" << endl;
            return;
        }
        parkingSlots.push(v);
        cout << "Vehicle " << v.vehicleID << " parked in the bay." << endl;
        cout << endl;
    }

    Vehicle exitVehicle() {
        if (isEmpty()) {
            cout << "Parking bay is empty!" << endl;
        }
        Vehicle v = parkingSlots.top();
        parkingSlots.pop();
        return v;
    }

    int getOccupiedSlots() const {
        return parkingSlots.size();
    }
};

class WaitingArea {
    queue<Vehicle> generalQueue;
    queue<Vehicle> priorityQueue;

public:
    void addGeneralVehicle(const Vehicle &v) {
        generalQueue.push(v);
        cout << "Vehicle " << v.vehicleID << " added to general waiting queue." << endl;
    }

    void addPriorityVehicle(const Vehicle &v) {
        priorityQueue.push(v);
        cout << "Priority vehicle " << v.vehicleID << " added to priority queue." << endl;
    }

    bool hasPriorityVehicle() const {
        return !priorityQueue.empty();
    }

    bool hasGeneralVehicle() const {
        return !generalQueue.empty();
    }

    Vehicle dequeuePriorityVehicle() {
        if (!hasPriorityVehicle()) {
            cout << "No priority vehicles in the queue!" << endl;
        }
        Vehicle v = priorityQueue.front();
        priorityQueue.pop();
        return v;
    }

    Vehicle dequeueGeneralVehicle() {
        if (!hasGeneralVehicle()) {
            cout << "No general vehicles in the queue!" << endl;
        }
        Vehicle v = generalQueue.front();
        generalQueue.pop();
        return v;
    }

    int getPriorityQueueSize() const {
        return priorityQueue.size();
    }

    int getGeneralQueueSize() const {
        return generalQueue.size();
    }
};

class SmartParkingSystem {
    ParkingBay parkingBay;
    WaitingArea waitingArea;
    double totalRevenue;

public:
    SmartParkingSystem(int capacity) : parkingBay(capacity), totalRevenue(0.0) {}

    void vehicleEntry(const string &vehicleID, int priority) {
        Vehicle v(vehicleID, priority);
        if (!parkingBay.isFull()) {
            parkingBay.parkVehicle(v);
        } else {
            if (priority == 1) {
                waitingArea.addPriorityVehicle(v);
            } else {
                waitingArea.addGeneralVehicle(v);
            }
        }
    }

    void vehicleExit() {
        if (parkingBay.isEmpty()) {
            cout << "Parking bay is empty!" << endl;
        }

        Vehicle v = parkingBay.exitVehicle();
        v.setExitTime();
        double fee = calculateFee(v);
        totalRevenue += fee;

        cout << "Vehicle " << v.vehicleID << " exited. Duration: " << v.getDuration()
             << " second(s). Fee: $" << fee << endl;

        if (waitingArea.hasPriorityVehicle()) {
            parkingBay.parkVehicle(waitingArea.dequeuePriorityVehicle());
        } else if (waitingArea.hasGeneralVehicle()) {
            parkingBay.parkVehicle(waitingArea.dequeueGeneralVehicle());
        }
    }

    double calculateFee(const Vehicle &v) const {
        double rate = (v.priorityLevel == 1) ? 20 : 10; // Per second
        return v.getDuration() * rate;
    }

    void displayReport() const {
        cout <<endl <<"    Parking System Report  "<<endl;
        cout<<endl;
        cout << "Total Revenue: $" << totalRevenue << endl;
        cout << "Occupied Slots: " << parkingBay.getOccupiedSlots() << endl;
        cout << "Priority Queue Size: " << waitingArea.getPriorityQueueSize() << endl;
        cout << "General Queue Size: " << waitingArea.getGeneralQueueSize() << endl;
    }
};
int main() {
    SmartParkingSystem parkingSystem(3); // parking slots limit is set here

    parkingSystem.vehicleEntry("car", 0); 
    parkingSystem.vehicleEntry("ambulance", 1); 
    parkingSystem.vehicleEntry("jeep", 0); 
    parkingSystem.vehicleEntry("bike", 0); 
    parkingSystem.vehicleEntry("police", 1);

    parkingSystem.displayReport();
    sleep(5);
    parkingSystem.vehicleExit(); 
    cout<<endl;
    sleep(5);
    parkingSystem.vehicleExit();
    cout<<endl;
    sleep(4);
    parkingSystem.displayReport();
    cout<<endl;

    return 0;
}
