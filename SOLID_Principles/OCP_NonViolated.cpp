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
        cout << "Shopping Cart Invoice" << endl ; 
        for (auto  i : cart->getProducts()){
            cout << "Product Name : " << i->name << " Price : " << i->price << endl;
        }
        cout << "Total Price:" << cart->calculateTotalPrice() << endl;
    }
};


// Abstract Class to follow OCP
class Persistence{
private:
    ShoppingCart* cart ; 
public : 
    virtual void Save(ShoppingCart* cart)=0; //Pure Virtual Function
};

class SqlPersistence : public Persistence{
private : 
    ShoppingCart* cart;
public : 

    void Save(ShoppingCart* cart) override{
        cout << "Saving Shopping Cart to SQLDatabase "<<endl;
    }
};

class FilePersistence : public Persistence{
    private : 
        ShoppingCart* cart;
    public : 
        void Save(ShoppingCart* cart) override{
            cout << "Saving Shopping Cart to File "<<endl;
        }
};

class MongoPersistence : public Persistence{
    private : 
    ShoppingCart* cart;
    public : 
        void Save(ShoppingCart* cart) override{
            cout << "Saving Shopping Cart to Mongo Database "<<endl;   
        }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Product 1", 100.0));
    cart->addProduct(new Product("Product 2", 200.0));

    ShoppingCartInvoice* invoice = new ShoppingCartInvoice(cart);
    invoice->printInvoice();

    Persistence* Sqldb = new SqlPersistence();
    Persistence* Mongodb = new MongoPersistence();
    Persistence* FileDb = new FilePersistence();

    Sqldb->Save(cart);
    Mongodb->Save(cart);
    FileDb->Save(cart);
    return 0;
}