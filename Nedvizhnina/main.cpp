#include <iostream>
#include <cstring>
using namespace std;
class Nedviznina {
protected:
    char *address;
    int kvadrat;
    int c;
    void copy(const Nedviznina& n) {
        this->address=new char[strlen(n.address)+1];
        strcpy(this->address, n.address);
        this->kvadrat=n.kvadrat;
        this->c=n.c;
    }
public:
    Nedviznina(char *address="", int kvadrat=0, int c=0) {
        this->address=new char[strlen(address)+1];
        strcpy(this->address, address);
        this->kvadrat=kvadrat;
        this->c=c;
    }
    Nedviznina(const Nedviznina& n) {
        copy(n);
    }
    Nedviznina& operator=(const Nedviznina& n) {
        if (this!=&n) {
            delete[]address;
            copy(n);
        }
        return *this;
    }
    ~Nedviznina(){delete[]address;}
    int cena() {
        return kvadrat*c;
    }
    void pecati() {
        cout<<address<<" "<<c<<" "<<kvadrat<<endl;
    }
    double danokNaImot() {
        return 0.05*cena();
    }
    friend istream& operator>>(istream& is,  Nedviznina& v) {
        char temp[256];
        is>>temp;
        delete[]v.address;
        v.address=new char[strlen(temp)+1];
        strcpy(v.address,temp);
     is>>v.c>>v.kvadrat;
        return is;
    }
    char* getAdresa() {
        return address;
    }
};
class Vila:public Nedviznina {
    int danok;
public:
    Vila(char *address="", int kvadrat=0, int c=0, int danok=0):Nedviznina(address,kvadrat,c) {
        this->danok=danok;
    }
    Vila(const Vila& v):Nedviznina(v) {
        this->danok=v.danok;
    }
    Vila& operator=(const Vila & v) {
        if (this!=&v) {
            Nedviznina::copy(v);
            this->danok=v.danok;
        }
        return *this;
    }
    ~Vila(){delete[]address;}
    void print() {
       Nedviznina::pecati();
        cout<<danok<<endl;
    }
    friend istream& operator>>(istream& is,  Vila& v) {
        delete[]v.address;
        char temp[256];
        is >> temp;
        v.address = new char[strlen(temp)+1];
        strcpy(v.address, temp);
        is>>v.c>>v.kvadrat>>v.danok;
        return is;
    }
    int danokNaImot() {
        return cena()*(5+danok)/100;
    }
char* getAdresa() {
        return address;
    }
};

int main()
{
    Nedviznina n;
    Vila v;
    cin >> n;
    cin >> v;
    n.pecati();
    cout << "Danok za: " << n.getAdresa() << ", e: " << n.danokNaImot() << endl;
    v.pecati();
    cout << "Danok za: " << v.getAdresa() << ", e: " << v.danokNaImot() << endl;
    return 0;
}