#include <iostream>
#include <cstring>

using namespace std;
class Transport {
protected:
  char destination[50];
int price;
int path;
public:
    Transport(char *destination="",int price=0, int path=0 ) {
        strcpy(this->destination,destination);
        this->price=price;
        this->path=path;
    }
    virtual int cenaTransport() {
        return price;
    }
    bool operator<(const Transport& p) {
        return path<p.path;
    }
    char *getDestination() {
        return destination;
    }
    int getPath() {
        return path;
    }
    virtual ~Transport(){}
    virtual void print() {
        cout<<destination<<" "<<path<<" "<<price<<endl;
    }

};
class AvtomobilTransport:public Transport {
    bool shofer;
public:
    AvtomobilTransport(char *destination="",int price=0, int path=0 , bool shofer=false):Transport(destination,price,path) {
        this->shofer=shofer;
    }
    int cenaTransport() {
        if (shofer) {
            price+=price*0.2;
        }
        return price;
    }
    void print() {
        Transport::print();
    }
};
class KombeTransport:public Transport {
    int brLugje;
public:
    KombeTransport(char *destination="",int price=0, int path=0 ,int brLugje=0):Transport(destination,price,path) {
        this->brLugje=brLugje;
    }
    int cenaTransport() {
        int brojach=0;
        for (int i=0;i<brLugje;i++) {
            brojach+=200;
        }
        price-=brojach;
        return price;
    }
    void print() {
        Transport::print();
    }

};
void pecatiPoloshiPonudi(Transport **t,int el,Transport &x) {

    for (int i = 0; i < el-1; i++) {
        for (int j = i+1; j < el; j++) {
            if (*t[j] < *t[i]) {
                Transport *temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }
        for (int i=0; i<el;i++) {
            if (t[i]->cenaTransport() > x.cenaTransport()) {
                t[i]->print();
            }
        }


    }






int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
