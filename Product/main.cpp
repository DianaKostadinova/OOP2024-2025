#include <iostream>
#include <cstring>
using namespace std;
class NegativeValueException {
string text;
public:
    NegativeValueException(string text) {
        this->text=text;
    }
    void print() {
        cout<<text;
    }
};
class Discount {
public:
    virtual float discount_price()=0;
    virtual float price()=0;
    virtual void print_rule(){};
    static float euro;
    static float dollar;
    virtual ~Discount(){}
};
class Product {
protected:
    string name;
    float cena;
public:
    Product(string name="", float cena=0):name(name),cena(cena) {

    }
    float getCena(){return cena;}
    void print() {
        cout<<"Product {"<<name<<", price="<<cena<<"}"<<endl;
    }
    float changePrice(float cena) {
        if (cena<0) throw NegativeValueException("Vnesena e negativns vrednoost za cena!\n");
        this->cena=cena;
        return cena;
    }
};
class FoodProduct:public Product, public Discount {
    float callories;
public:
    FoodProduct(string name="", float cena=0, float callories=0):Product(name,cena), callories(callories){}
    float discount_price() override{
        return getCena();
    };
    float price() override {
        return getCena();
    };
    void print_rule() {
        cout << "Nema popust za proizvodite od tip na hrana" << endl;
    }
};
class Drinks:public Product, public Discount {
    string brand;
    bool alchoholic;
public:
   Drinks(string name="", float cena=0, string brand="", bool alchoholic=false):Product(name,cena),brand(brand), alchoholic(alchoholic){}
float discount_price() override {
    if (this->alchoholic&&(getCena()/Discount::euro)>20) {
        return 0.95*getCena();
    }
       if (!this->alchoholic&&(this->brand=="Coca-Cola")) {
           return 0.9*getCena();
       }
       return getCena();
   }
    float price() override {
       return getCena();
   }
    void print_rule(){
       cout << "Site alkoholni pijaloci poskapi od 20 evra imaat popust od 5 % , dodeka pak nealkoholnite od brendot Coca - Cola imaat popust od 10 % "<<endl;
   }
};
class Cosmetics:public Product, public Discount {
    int weight;
public:
    Cosmetics(string name="", float cena=0, int weight=0):Product(name,cena), weight(weight){}
    float discount_price() override {
        if (getCena()/Discount::dollar>20)
            return 0.86*getCena();
        if (getCena()/Discount::euro>5)
            return 0.88*getCena();
        return getCena();
    }
    float price() {
        return getCena();
    }
    void print_rule(){
        cout << "Site kozmeticki proizvodi poskapi od 5 evra imaat popust od 12%, dodeka pak onie koi se poskapi od 20 dolari imaat popust 14%" << endl;
    }
};
float Discount::euro = 61.7;
float Discount::dollar = 44.5;
float total_discount(Discount **d, int n) {
    float discount=0;
    for (int i=0; i<n; i++) {
        discount += d[i]->discount_price();
        cout << "Prvicna cena: " << d[i]->price() << endl;
        cout << "So popust: " << d[i]->discount_price() << endl;
        d[i]->print_rule();
    }
    return discount;
}
int main() {
    int n = 0;
    float newPrice;
    Discount **d = new Discount*[10];
    d[n++] = new FoodProduct("leb", 30);
    d[n++] = new Drinks("viski", 1350, "Jack Daniel's", true);
    d[n++] = new FoodProduct("sirenje", 390, 105);
    d[n++] = new Drinks("votka", 850, "Finlandia", true);
    d[n++] = new Cosmetics("krema", 720, 100);
    d[n++] = new Drinks("sok", 50, "Coca-Cola", false);
    d[n++] = new Cosmetics("parfem", 3500, 50);

    cout << "Vkupnata cena na site proizvodi e: " << total_discount(d, n) << endl;

    //se menuva cenata na site Kozmeticki proizvodi
    cout << "Promena na cenata na kozmetickite proizvodi " << endl;
    for (int i = 0; i < n; ++i) {
        Cosmetics* c = dynamic_cast<Cosmetics *>(d[i]);
        if (c != 0){
            c->print();
            cin >> newPrice;
            try{
                c->changePrice(newPrice);
            }
            catch (NegativeValueException i){
                i.print();
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        delete d[i];
    }
    delete[] d;

    return 0;
}