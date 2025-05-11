#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
class Shape {
protected:
    int side;
public:
Shape(int side=0):side(side){}
    virtual double plostina()=0;
    virtual void pecati(){}
    virtual int getType(){}
};
class Square:public Shape {
public:
    Square(int side=0):Shape(side){}
    double plostina() {return side*side;}
    void print(){cout<<"Kvadrat so plostina"<<plostina<<endl;}
    int getType(){return 1;}
};
class Circle:public Shape  {
public:
Circle(int side=0):Shape(side){}
    double plostina() {return M_PI*side*side;}
    void print(){cout<<"Krug so plostina"<<plostina<<endl;}
    int getType(){return 2;}
};
class Triangle:public Shape  {
public:
Triangle(int side=0):Shape(side){}
    double plostina(){return sqrt(3)/4*side*side;}
    void print(){cout<<"Trijagolnik so plostina"<<plostina<<endl;}
    int getType(){return 3;}
};
void checkNumTypes(Shape** niza, int n) {
    int k=0,kr=0,t=0;
    for (int i=0; i<n; i++) {
        if (niza[i]->getType()==1) {
            k++;
        }
        else if (niza[i]->getType()==2) {
            kr++;
        }
        else {
            t++;
        }
    }
    cout << "Broj na kvadrati vo nizata = " << k << endl;
    cout << "Broj na krugovi vo nizata = " << kr << endl;
    cout << "Broj na triagolnici vo nizata = " << t << endl;
}

int main()
{
    int n;
    cin >> n;

    Shape **shape = new Shape *[n];

    int classType;
    int side;

    for (int i = 0; i < n; ++i)
    {
        cin >> classType;
        cin >> side;

        if (classType == 1)
            shape[i] = new Square(side);
        else if (classType == 2)
            shape[i] = new Circle(side);
        else if (classType == 3)
            shape[i] = new Triangle(side);
    }

    for (int i = 0; i < n; ++i)
        shape[i]->pecati();

    checkNumTypes(shape, n);

    return 0;
}