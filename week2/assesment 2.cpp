#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct WarehouseLocation {
	int aisle;
	int bin;
	int row;
	string item_id;

// constr initialization
	WarehouseLocation(int a, int b, int r, string id)
		: aisle(a), bin(b), row(r), item_id(id) {}
};

// Structforlocation and quaintity adding
struct InventoryItem {
	WarehouseLocation location;
	int quantity;

	// constr  initialise
	InventoryItem(int aisle, int bin, int row, string id, int qty)
		: location(aisle, bin, row, id), quantity(qty) {}
};

class Warehouse {
private:
	vector<InventoryItem> inventory;

public:
	// to add items
	void addItem(int aisle, int bin, int row, const string& item_id, int quantity)
	{
		for (auto& item : inventory)
		{
			if (item.location.aisle == aisle && item.location.bin == bin &&
			        item.location.row == row && item.location.item_id == item_id)
			{

				// If item exists, increase the quantity
				item.quantity += quantity;
cout << "Added " << quantity << " of " << item_id << " at ("<< aisle << ", " << bin << ", " << row << ")." << endl;
				return;
			}
		}

		// new item adding to inventery
		if (quantity > 0)
		{
			inventory.push_back(InventoryItem(aisle, bin, row, item_id, quantity));
cout << "Added " << quantity << " of " << item_id << " at ("<< aisle << ", " << bin << ", " << row << ")." << endl;
		}
	}

	void removeItem(int aisle, int bin, int row, const string& item_id, int quantity)
	{
		for (auto it = inventory.begin(); it != inventory.end(); ++it)
		{
			if (it->location.aisle == aisle && it->location.bin == bin &&
			        it->location.row == row && it->location.item_id == item_id)
			{

				if (it->quantity >= quantity)
				{
					it->quantity -= quantity;
cout << "Removed " << quantity << " of " << item_id << " from ("<< aisle << ", " << bin << ", " << row << ")." << endl;

					if (it->quantity == 0)
					{
						inventory.erase(it);  // erase item
						cout << "Item " << item_id << " is now completely removed from inventory." << endl;
					}
				}
				else
				{
					cout << "Not enough stock to remove." << endl;
				}
				return;
			}
		}
		cout << "Item not found in the specified location." << endl;
	}

	//  quantity of  item in location
	int getQuantity(int aisle, int bin, int row, const string& item_id)
	{
		for (const auto& item : inventory) {
			if (item.location.aisle == aisle && item.location.bin == bin &&item.location.row == row && item.location.item_id == item_id)
			{
				return item.quantity;
			}
		}
		return 0;
	}

	// to display all items
	void displayInventory()
	{
		cout << "Inventory List:" << endl;
		if (inventory.empty())
		{
			cout << "No items in inventory." << endl;
		}
		for (const auto& item : inventory)
		{
cout << "Aisle: " << item.location.aisle << ", Bin: " << item.location.bin<< ", Row: " << item.location.row << ", Item: " << item.location.item_id
			     << ", Quantity: " << item.quantity << endl;
		}
	}

	// used for one loc to another transfer
	void transferItem(int fromAisle, int fromBin, int fromRow, const string& item_id,
	                  int toAisle, int toBin, int toRow, int quantity)
	{
		int currentQuantity = getQuantity(fromAisle, fromBin, fromRow, item_id);

		if (currentQuantity >= quantity)
		{
			removeItem(fromAisle, fromBin, fromRow, item_id, quantity);
			addItem(toAisle, toBin, toRow, item_id, quantity);
cout << "Transferred " << quantity << " of " << item_id<< " from (" << fromAisle << ", " << fromBin << ", " << fromRow
			     << ") to (" << toAisle << ", " << toBin << ", " << toRow << ")." << endl;
		} else
		{
			cout << "Not enough stock to transfer." << endl;
		}
	}

	// to check low stocks
	void checkLowStock(int threshold)
	{
		cout << "Low-Stock Alert (Threshold: " << threshold << "):" << endl;
		bool foundLowStock = false;
		for (const auto& item : inventory)
		{
			if (item.quantity < threshold)
			{
cout << "Item: " << item.location.item_id << " at ("<< item.location.aisle << ", " << item.location.bin << ", "
				     << item.location.row << ") has low stock: " << item.quantity << endl;
				foundLowStock = true;
			}
		}
		if (!foundLowStock)
		{
			cout << "No low-stock items found." << endl;
		}
	}
};
void displayMenu()
{
	cout << "\nWarehouse Inventory System Menu:"<<endl;
	cout << "1. Add Item "<<endl;
	cout << "2. Remove Item"<<endl;
	cout << "3. Check Stock"<<endl;
	cout << "4. Display Inventory"<<endl;
	cout << "5. Transfer Item "<<endl;
	cout << "6. To view low stock"<<endl;
	cout << "7. Exit" <<endl;
	cout << "Enter your choice: ";
}

int main() {
	Warehouse warehouse;
	int choice;
	int aisle, bin, row, quantity, threshold;
	string item_id;

	while (true) {
		displayMenu();
		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "Enter aisle, bin, row, item ID and quantity: ";
			cin >> aisle >> bin >> row >> item_id >> quantity;
			warehouse.addItem(aisle, bin, row, item_id, quantity);
			break;
		}
		case 2: {
			cout << "Enter aisle, bin, row, item ID and quantity to remove: ";
			cin >> aisle >> bin >> row >> item_id >> quantity;
			warehouse.removeItem(aisle, bin, row, item_id, quantity);
			break;
		}
		case 3: {
			cout << "Enter aisle, bin, row and item ID to check stock: ";
			cin >> aisle >> bin >> row >> item_id;
	cout << "Quantity of " << item_id << " at ("<< aisle << ", " << bin << ", " << row << "): "
			     << warehouse.getQuantity(aisle, bin, row, item_id) << endl;
			break;
		}
		case 4: {
			warehouse.displayInventory();
			break;
		}
		case 5: {
			int toAisle, toBin, toRow;
			cout << "Enter from aisle, bin, row, item ID, to aisle, bin, row and quantity to transfer: ";
			cin >> aisle >> bin >> row >> item_id >> toAisle >> toBin >> toRow >> quantity;
			warehouse.transferItem(aisle, bin, row, item_id, toAisle, toBin, toRow, quantity);
			break;
		}
		case 6: {
			cout << "Enter stock threshold for lowstock alert: ";
			cin >> threshold;
			warehouse.checkLowStock(threshold);
			break;
		}
		case 7: {
			cout << "Exiting the system.\n";
			return 0;
		}
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}