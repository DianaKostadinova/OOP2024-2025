#include <iostream>
#include <cstring>
using namespace std;
class Theater {
protected:
    char *name;
    char *city;
    int capacity;
    double grade[11];
    double price;
    int popust;
    void copy(const Theater& t) {
        this->name=new char[strlen(t.name)+1];
        this->city=new char[strlen(t.city)+1];
        strcpy(this->name,t.name);
        strcpy(this->city, t.city);
        this->capacity=t.capacity;
        for (int i=0; i<10; i++) {
            this->grade[i]=t.grade[i];
        }
        this->price=t.price;
        this->popust=t.popust;
    }
public:
    Theater(char *name="", char *city="", int capacity=0, double *grade=0, int price=0, int popust=0) {
        this->name=new char[strlen(name)+1];
        this->city=new char[strlen(city)+1];
        strcpy(this->name,name);
        strcpy(this->city, city);
        this->capacity=capacity;
        for (int i=0; i<10; i++) {
            this->grade[i]=grade[i];
        }
        this->price=price;
        this->popust=popust;

    }
    Theater(const Theater& t) {
        copy(t);
    }
    Theater& operator=(const Theater& t) {
        if (this!=&t) {
            delete[]name;
            delete[]city;
            copy(t);
        }
        return *this;
    }
   double avgRating() {
        double sum=0;
      for (int i=0; i<10; i++) {
          sum+=grade[i];
      }
        return sum/10.0;
    }
    virtual double finalTicketPrice() {
        double cena;
        if (avgRating()<2.0) {
           cena=price*0.8;
        }
        else if (avgRating()>=2.0 &&avgRating()<4.0) {
            cena=price;
        }
        else if (avgRating()>=4.0) {
            cena= price*1.2;
        }
        cena-=cena*popust/100;
        return cena;
    }
    virtual void print() {
        cout<<"City: "<<city<<" Name: "<<name<<" Rating: "<<avgRating()<<" Price: "<<finalTicketPrice()<<endl;
    }
};
class MovieTheater: public Theater {
    double sirina;
    double visina;
    bool tride;
    void copy(const MovieTheater& m) {
        Theater::copy(m);
        this->sirina=m.sirina;
        this->visina=m.visina;
        this->tride=m.tride;
    }
public:
    MovieTheater(char *name="", char *city="", int capacity=0, double *grade=0, int price=0, int popust=0,double sirina=0, double visina=0, bool tride=false):Theater(name,city,capacity,grade,price, popust) {
        this->sirina=sirina;
        this->visina=visina;
        this->tride=tride;
    }
    MovieTheater(const MovieTheater& m):Theater(m) {
        copy(m);
    }
    MovieTheater& operator=(const MovieTheater& m) {
        if (this!=&m) {
            copy(m);
        }
        return *this;
    }
    ~MovieTheater(){}
    double finalTicketPrice() {
        double cena;
        if (tride) {
            cena=price+price*0.3;
        }
        else cena=price;
        cena-=cena*popust/100;
        return cena;
    }
    void print() override {
        Theater::print();
        cout<<"Width: "<<sirina<<" Visina: "<<visina<<" Dali 3D? "<<(tride ? "yes":"No")<<endl;;
    }

};
Theater MostExpensiveTheater(int n,Theater**t) {
Theater* min=nullptr;
    for (int i=0; i<n; i++) {
        if (min==nullptr || min->finalTicketPrice()<t[i]->finalTicketPrice()) {
            min=t[i];
        }
    }
    return *min;

}
int main() {
    int n;
    cin >> n;

    char name[100];
    char city[100];
    int capacity;
    double reviews[10];
    double baseTicketPrice;
    int discount;
    double screenWidth, screenHeight;
    bool is3D;

    if (n == 1) {
        cout << "TESTING CLASS THEATER:" << endl;
        cout << "==============================" << endl;
        for (int i = 0; i < 3; ++i) {
            cin >> name >> city >> capacity;
            for (int j = 0; j < 10; ++j)
                cin >> reviews[j];
            cin >> baseTicketPrice >> discount;

            Theater t(name, city, capacity, reviews, baseTicketPrice, discount);
            t.print();
            cout << "------------------------------";
        }
    } else if (n == 2) {
        cout << "TESTING CLASS MOVIE THEATERS:" << endl;
        cout << "==============================" << endl;
        for (int i = 0; i < 3; ++i) {
            cin >> name >> city >> capacity;
            for (int j = 0; j < 10; ++j)
                cin >> reviews[j];
            cin >> baseTicketPrice >> discount >> screenWidth >> screenHeight >> is3D;

            MovieTheater mt(name, city, capacity, reviews, baseTicketPrice, discount, screenWidth, screenHeight, is3D);
            mt.print();
            cout << "------------------------------";
        }
    } else if (n == 3) {
        cout << "TESTING MostExpensiveTheater FUNCTION:" << endl;
        cout << "==============================" << endl;

        Theater *theaters[6];
        int type;
        for (int i = 0; i < 5; ++i) {
            cin >> type;

            if (type == 1) { // Theater
                cin >> name >> city >> capacity;
                for (int j = 0; j < 10; ++j)
                    cin >> reviews[j];
                cin >> baseTicketPrice >> discount;
                theaters[i] = new Theater(name, city, capacity, reviews, baseTicketPrice, discount);
            } else { // MovieTheater
                cin >> name >> city >> capacity;
                for (int j = 0; j < 10; ++j)
                    cin >> reviews[j];
                cin >> baseTicketPrice >> discount;
                cin >> screenWidth >> screenHeight >> is3D;
                theaters[i] = new MovieTheater(name, city, capacity, reviews, baseTicketPrice, discount,
                screenWidth, screenHeight, is3D);
            }
        }

        MostExpensiveTheater(5, theaters);

        for (int i = 0; i < 5; ++i) {
            delete theaters[i];
        }
    }
    return 0;
}