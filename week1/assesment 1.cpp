#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    string category;
    int quantity;

    Product(int id, string name, double price, string category, int quantity): id(id), name(name), price(price), category(category), quantity(quantity) 
        {
            
        }

    virtual void display() const 
    {
        cout << name << " - " << price << " - " << category;
    }

    virtual ~Product()
    {
         }
};

// Electronics class
class Electronics : public Product {
public:
    int warrantyYears;
Electronics(int id, string name, double price, int warrantyYears, int quantity): Product(id, name, price, "Electronics", quantity), warrantyYears(warrantyYears) {}

    void display() const override 
    {
        Product::display();
        cout << " - Warranty: " << warrantyYears << " years" << endl;
    }
};

// Clothing class
class Clothing : public Product {
public:
    string size;

Clothing(int id, string name, double price, string size, int quantity): Product(id, name, price, "Clothing", quantity), size(size) {}
void display() const override
{
        Product::display();
        cout << " - Size: " << size << endl;
    }
};

// Inventory class
class Inventory {
private:
    vector<Product*> products;

public:
    Inventory(const vector<Product*>& products) : products(products)
    {
        
    }
Product* getProductById(int id) {
        for (auto product : products) {
            if (product->id == id && product->quantity > 0) {
                return product;
            }
        }
        return nullptr;
    }
void reduceInventory(const vector<Product*>& cartProducts) {
        for (auto cartProduct : cartProducts) {
            for (auto product : products) {
                if (product->id == cartProduct->id) {
                    product->quantity--;
                }
            }
        }
    }
void displayProducts(const string& category) const {
        cout << "Available products in category: " << category << "\n";
        for (const auto& product : products) {
            if (product->category == category && product->quantity > 0) {
                cout << product->id << ". ";
                product->display();
                cout << " - Quantity: " << product->quantity << endl;
            }
        }
    }
void displayProductQuantity(int id) const {
        for (const auto& product : products) {
            if (product->id == id) {
                cout << "Product ID: " << product->id << " - " << product->name 
                     << " - Available Quantity: " << product->quantity << endl;
                return;
            }
        }
        cout << "Invalid product ID or product is out of stock.\n";
    }
 ~Inventory() {
        for (auto product : products) {
            delete product;
        }
    }
};

class Cart {
private:
    vector<Product*> products;
public:
    void addProduct(Product* product) {
        products.push_back(product);
        cout << "Added " << product->name << " to the cart.\n";
    }
void viewCart() const 
{
        cout << "Your cart:\n";
        for (const auto& product : products) {
            product->display();
            cout << endl;
        }
    }
 double getTotal() const {
        double total = 0;
        for (const auto& product : products) {
            total += product->price;
        }
        return total;
    }
const vector<Product*>& getProducts() const {
        return products;
    }
};
class Payment {
public:
void checkout(double amount) 
{
        cout << "Your total is " << amount << ". Choose a payment option:\n";
        cout << "1. Credit card\n2. Debit card\n3. Cash on Delivery\n";
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "Processing Credit card payment\n";
                break;
            case 2:
                cout << "Processing Debit card payment\n";
                break;
            case 3:
                cout << "Processing Cash on Delivery\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }
};

void displayCategories(const vector<string>& categories) 
{
    cout << "Available categories:\n";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i] << "\n";
    }
}

int main() {
    vector<Product*> productList = {
        new Electronics(1, "Laptop", 999.99, 2, 5),
        new Electronics(2, "Smartphone", 499.99, 1, 10),
        new Electronics(3, "Headphones", 199.99, 1, 15),
        new Electronics(4, "Smartwatch", 299.99, 2, 7),
        new Clothing(5, "T-Shirt", 19.99, "M", 25),
        new Clothing(6, "Jeans", 49.99, "L", 30),
        new Clothing(7, "Jacket", 89.99, "XL", 12),
        new Clothing(8, "Sneakers", 59.99, "10", 20)
    };
Inventory inventory(productList);
    vector<string> categories = { "Electronics", "Clothing" };
    Cart cart;
    Payment payment;
    int choice;
cout << "Welcome to the store!\n";
bool running = true;
    while (running) {
        cout << "\nMain Menu:\n";
        cout << "1. View Categories\n";
        cout << "2. View Product Quantity\n";
        cout << "3. Checkout\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
 switch (choice) {
  case 1: {
    displayCategories(categories);
    cout << "Enter the category number to view products: ";
    cin >> choice;

    if (choice < 1 || choice > categories.size())
    {
    cout << "Invalid category number. Please try again.\n";
    continue;
    }

    string selectedCategory = categories[choice - 1];
    inventory.displayProducts(selectedCategory);
                
    cout << "Enter the product ID to add to cart (0 to go back to categories): ";
    cin >> choice;
    if (choice == 0) continue;
      Product* product = inventory.getProductById(choice);
     if (product) {
                    cart.addProduct(product);
    } else {
  cout << "Invalid product ID or product is out of stock.\n";
                }
        break;
            }
  case 2: {
     cout << "Enter Product ID to check availability: ";
   cin >> choice;
    inventory.displayProductQuantity(choice);
                break;
            }
            case 3: {
                cart.viewCart();
                double total = cart.getTotal();
                payment.checkout(total);

     // Reduce inventory
 inventory.reduceInventory(cart.getProducts());
cout << "\nThank you for shopping with us!\n";
    cout << "Total Price: $" << total << "\n";
              break;
            }
case 4:
  running = false;
 cout << "Thank you for shoping\n";
 break;
 default:
cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}