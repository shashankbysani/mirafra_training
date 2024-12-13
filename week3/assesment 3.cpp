#include <iostream>
#include <vector>
#include <string>
using namespace std;

// to store menu and price
class MenuItem {
public:
	string name;
	double price;

	MenuItem(string name, double price) : name(name), price(price) {}
};

//to store Restaurant names 
class Restaurant {
public:
	string name;
	vector<MenuItem> menu;

	Restaurant(string name) : name(name) {}

	void addMenuItem(string itemName, double price) {
		MenuItem item(itemName,price);
		menu.push_back(item);
	}

	void displayMenu()const {
		cout << "Menu for " << name << ":\n";
		for (size_t i = 0; i < menu.size(); i++) {
			cout << i + 1 << ". " << menu[i].name << " - " << menu[i].price << endl;
		}
	}
};

// to store order details
class Order {
public:
	string restaurantName;
	vector<string> items;
	double totalPrice;

Order(string rName, vector<string> its, double tPrice) {
    restaurantName = rName; 
    items = its; 
    totalPrice = tPrice;
    }
};
// using circular ll to store order details
class OrderNode {
public:
	Order* order;
	OrderNode* next;

	OrderNode(Order* order) : order(order), next(nullptr) {}
};

// using circular ll and queues to manage order
class DeliverySystem {
private:
	OrderNode* front;
	OrderNode* rear;

public:
	DeliverySystem() {
	    front=nullptr;
	    rear=nullptr;
	}

	void enqueue(Order* order) {
		OrderNode* newNode = new OrderNode(order);
		if (front==nullptr) {
			front = rear = newNode;
			rear->next = front;
		} else {
			rear->next = newNode;
			rear = newNode;
			rear->next = front;
		}
	}

	void processOrder() {
		if (front==nullptr) {
			cout << "No orders to process.\n";
			return;
		}

		OrderNode* temp = front;
		cout << "Processing Order from " << temp->order->restaurantName << ":\n";
		for (const auto& item : temp->order->items) {
			cout << "- " << item << endl;
		}
		cout << "Total Price: " << temp->order->totalPrice << endl;

		// to delete the completed order from queue
		if (front == rear) {
			front = rear = nullptr;
		} else {
			front = front->next;
			rear->next = front;
		}
		delete temp->order;
		delete temp;
	}

	void displayOrders() {
		if (front==nullptr) {
			cout << "No orders in the queue.\n";
			return;
		}

		OrderNode* temp = front;
		cout << "Orders in the queue:\n";
		do {
			cout << "- Order from " << temp->order->restaurantName
			     << " | Total Price: " << temp->order->totalPrice << endl;
			temp = temp->next;
		} while (temp != front);
	}
};


int main() {
	vector<Restaurant> restaurants;
	DeliverySystem deliverySystem;

	int choice;
	do {
		cout <<endl<< " WELCOME TO ZOMATO "<<endl;
		cout <<endl<< "Food Ordering and Delivery System"<<endl;
		cout << "1. Add Restaurant "<<endl;
		cout << "2. Add Menu Item"<<endl;
		cout << "3. View Restaurants"<<endl;
		cout << "4. Place Order"<<endl;
		cout << "5. Process Next Order"<<endl;
		cout << "6. View Orders"<<endl;
		cout << "7. Exit "<<endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Enter restaurant name: ";
			string name;
			cin.ignore();
			getline(cin, name);
			Restaurant reso(name);
			restaurants.push_back(reso);
			cout << "Restaurant added."<<endl;
			break;
		}
		case 2: {
			cout << "Select a restaurant in Below list: "<<endl;
			for (size_t i = 0; i < restaurants.size(); i++) {
				cout << i + 1 << ". " << restaurants[i].name << endl;
			}
			int resChoice;
			cin >> resChoice;

			if (resChoice > 0 && resChoice <= restaurants.size()) {
				cout << "Enter menu item name: ";
				string itemName;
				cin.ignore();
				getline(cin, itemName);
				cout << "Enter the price: ";
				double price;
				cin >> price;
				restaurants[resChoice - 1].addMenuItem(itemName, price);
				cout << "Menu items added."<<endl;
			} else {
				cout << "Invalid choice."<<endl;
			}
			break;
		}
		case 3: {
			for (int i=0;i<restaurants.size();i++) {
				cout << "Restaurant: " << restaurants[i].name << endl;
				restaurants[i].displayMenu();
			}
			break;
		}
		case 4: {
			cout << "Select a restaurant to order: "<<endl;
			for (size_t i = 0; i < restaurants.size(); i++) {
				cout << i + 1 << ". " << restaurants[i].name << endl;
			}
			int resChoice;
			cin >> resChoice;

			if (resChoice > 0 && resChoice <= restaurants.size()) {
				Restaurant& selectedRestaurant = restaurants[resChoice - 1];
				selectedRestaurant.displayMenu();

				vector<string> orderedItems;
				double totalPrice = 0;
				cout << "Enter food item numbers to order (Press 0 to finish your order): "<<endl;
				while (true) {
					int itemChoice;
					cin >> itemChoice;
					if (itemChoice == 0)
						break;
					if (itemChoice > 0 && itemChoice <= selectedRestaurant.menu.size()) {
						orderedItems.push_back(selectedRestaurant.menu[itemChoice - 1].name);
						totalPrice += selectedRestaurant.menu[itemChoice - 1].price;
					} else {
						cout << "Invalid fooditem number."<<endl;
					}
				}

				if (!orderedItems.empty()) {
					Order* newOrder = new Order(selectedRestaurant.name, orderedItems, totalPrice);
					deliverySystem.enqueue(newOrder);
					cout << "Order placed successfully."<<endl;
				} else {
					cout << "No fooditems are ordered."<<endl;
				}
			} else {
				cout << "Invalid choice."<<endl;
			}
			break;
		}
		case 5:
			deliverySystem.processOrder();
			break;
		case 6:
			deliverySystem.displayOrders();
			break;
		case 7:
			cout << "Thanks for ordering on ZOMATO.";
			break;
		default:
			cout << "Invalid choice."<<endl;
		}
	} while (choice != 7);

	return 0;
}
