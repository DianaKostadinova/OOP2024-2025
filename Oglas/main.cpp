#include <iostream>
#include <cstring>
#include <exception>
using namespace std;
class NegativnaVrednost:public invalid_argument{
public:
	NegativnaVrednost():invalid_argument("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"){}
};
class Oglas{
char naslov[50];
	char kategorija[30];
	char opis[100];
	double price;
public:
	Oglas(char *naslov="", char *kategorija="", char *opis="",double price=0) {
		strcpy(this->naslov,naslov);
		strcpy(this->kategorija,kategorija);
		strcpy(this->opis,opis);
		this->price=price;
	}
	bool operator>(const Oglas &o) {
		return price>o.price;
	}
	friend ostream & operator<<(ostream &os, const Oglas& o) {
		os<<o.naslov<<endl;
		os<<o.opis<<endl;
		os<<o.price<<" evra"<<endl;
		return os;

	}
	double getPrice ()const {
		return price;
	}
	char*getKategorija() {
		return kategorija;
	}
};
class Oglasnik {
	char name[20];
	Oglas* og;
	int br;
public:
	Oglasnik(char *name=""):og(nullptr),br(0) {
		strcpy(this->name,name);
	}
	Oglasnik&operator+=( const Oglas& o) {
		try {
			if (o.getPrice() < 0)
				throw NegativnaVrednost();
		} catch (const NegativnaVrednost& e) {
			cout << e.what() << endl;
			return *this;
		}
		Oglas* temp=new Oglas[br+1];
		for (int i=0; i<br; i++) {
			temp[i]=og[i];
		}
		delete[]og;
		temp[br]=o;
		br++;
		og=temp;
		return *this;

	}
	Oglasnik(const Oglasnik& other) : og(nullptr), br(0) {
		strcpy(name, other.name);
		br = other.br;
		og = new Oglas[br];
		for (int i = 0; i < br; i++) {
			og[i] = other.og[i];
		}
	}

	Oglasnik& operator=(const Oglasnik& other) {
		if (this != &other) {
			delete[] og;
			strcpy(name, other.name);
			br = other.br;
			og = new Oglas[br];
			for (int i = 0; i < br; i++) {
				og[i] = other.og[i];
			}
		}
		return *this;
	}
	~Oglasnik(){delete[]og;}
	friend ostream &operator<<(ostream& os, const Oglasnik& ogs) {
		os<<ogs.name<<endl;
		for (int i=0; i<ogs.br;i++) {
			os<<ogs.og[i]<<endl;
		}
		return os;
	}
	void oglasiOdKategorija(const char *k) {
		for (int i=0; i<br; i++) {
			if (strcmp(k,og[i].getKategorija())==0) {
				cout<<og[i]<<endl;
			}
		}
	}
	void najniskaCena() {
		Oglas temp=og[0];
		for (int i=0; i<br; i++) {
			if (temp>og[i])
				temp=og[i];
		}
		cout<<temp<<endl;
	}
};
int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
			ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
