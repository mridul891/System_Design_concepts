#include<iostream>
#include<vector> 
using namespace std; 

// Product class Representing
class Product { 
public : 
    string name;
    double price; 

    Product(string name , double price ){
        this->name = name;
        this->price = price;
    }
};
// SRP Non Violated : Shopping Cart is handling only one Responsibility at a time
class ShoppingCart{
private : 
    vector<Product*> products;
public :
    void addProduct(Product* p){
        products.push_back(p);
    }
    
    const vector<Product*>& getProducts(){
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
};
// Invoice class handling only Invoice related functionality
class ShoppingCartInvoice{
private : 
    ShoppingCart* cart;
public:
    ShoppingCartInvoice(ShoppingCart* cart){
        this->cart=cart;
    }

    void printInvoice(){
        cout << " SHoping Cart INvoice" << endl ; 
        for (auto  i : cart->getProducts()){
            cout << "Product Name : " << i->name << " Price : " << i->price << endl;
        }
        cout << "Total Price:" << cart->calculateTotalPrice() << endl;
    }
};

class ShoppingCartDB{
private : 
    ShoppingCart* cart;
public : 
    ShoppingCartDB(ShoppingCart* cart){
        this->cart=cart;
    }

    void SaveToDatabase(){
        cout << "Saving Shopping Cart to Database "<<endl;
    }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Product 1", 100.0));
    cart->addProduct(new Product("Product 2", 200.0));

    ShoppingCartInvoice* invoice = new ShoppingCartInvoice(cart);
    invoice->printInvoice();

    ShoppingCartDB* db = new ShoppingCartDB(cart);
    db->SaveToDatabase();
    
    return 0;
}