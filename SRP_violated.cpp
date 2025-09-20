#include<iostream>
#include<vector>

using namespace std; 

// Product class Representing 
class Product {
public: 
    string name ;
    double price ;
    
    Product (string name , double price) {
        this->name = name;
        this->price = price;
    }
};


// Violated SRR : Shopping Cart is Handling multiple Responsibilities at a single time 

class ShoppingCart { 
private :
    vector<Product*> products;
public : 
    void addProduct(Product* p){
        products.push_back(p);
    }

    const vector<Product* >& getProducts(){
        return products;
    }

    // Calculate Total Price of Products in Cart
    double calculateTotalPrice(){
        double total = 0.0; 
        for ( auto i : products) {
            total+= i->price;
        }
        return total;
    }

    // Violation of SRP : Shopping Cart is handling print Invoice also 
    void printInvoice(){
        cout<< "Shopping Cart Invoice "<<endl;
        for (auto i : products){
            cout << "Product Name : " << i->name << " Price : " << i->price << endl;
        }

        cout << "Total Price : " << calculateTotalPrice() << endl;
    }

    // Violation of SRP : Saves to Db
    void SaveToDatabase(){
        cout << "Saving Shopping Cart to Database "<<endl;
    }
};

int main() {
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Product 1", 100.0));
    cart->addProduct(new Product("Product 2", 200.0));
    cart->printInvoice();
    cart->SaveToDatabase();
    return 0;
}

