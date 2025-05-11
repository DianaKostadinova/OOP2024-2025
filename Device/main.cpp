#include <complex.h>
#include <iostream>
#include <cstring>
using namespace std;

enum tip {
	Mobilen=0,
	laptop
};
void typeToInt(tip t) {
	if (t==0)
		cout<<"Mobilen";
	else cout<<"Laptop";
}
class Device {
protected:
	char model[100];
	tip type;
	static double baseHours;
	int year;
public:
	Device(char *model="", tip type=Mobilen,  int year=0) {
		strcpy(this->model,model);
		this->type=type;
		this->year=year;
	}

	double getRepariHours()const {
		double hours=baseHours;
		if (year>2015) {
			hours+=2;

		}
		if ((int)type==1) {
			hours+=2;

		}
		return hours;
	}

	~Device(){}
	 static void setPocetniCasovi(double chas) {
		baseHours=chas;
	}
	int getYear()const{return year;}
	friend ostream &operator<<(ostream& os, const Device& d) {
		os<<d.model<<endl;
		typeToInt(d.type);
		os<<" "<<d.getRepariHours()<<endl;
		return os;
	}

};
double Device::baseHours=1;
class MobileServis {
	char name[100];
	Device* d;
	int nm;
	void copy(const MobileServis& m) {
		strcpy(name,m.name);
		this->nm=m.nm;
		d=new Device[nm+1];
		for (int i=0; i<m.nm; i++) {
			this->d[i]=m.d[i];
		}
	}
public:
	MobileServis(char *name=""):nm(0),d(nullptr) {
		strcpy(this->name,name);
	}
	MobileServis(const MobileServis& m) {
		copy(m);
	}
	MobileServis& operator=(const MobileServis& m) {
		if (this!=&m) {
			delete[]d;
			copy(m);
		}
		return *this;
	}
	MobileServis& operator+=(const Device& dev) {
		if (dev.getYear()<2000||dev.getYear()>2019) {
			cout<<"Невалидна година на производство"<<endl;
			return *this;

		}

		Device*temp=new Device[nm+1];
		for (int i=0; i<nm; i++) {
			temp[i]=d[i];
		}
		temp[nm]=dev;
		nm++;
		delete[]d;
		d=temp;
		return *this;
	}
	~MobileServis() {
		delete[] d;
	}
	void pecatiCasovi() {
		cout<<"Ime: "<<name<<endl;
		for (int i=0; i<nm; i++) {
			cout<<d[i];
		}
	}
};

int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}

