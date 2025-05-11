#include <iostream>
#include <cstring>
using namespace std;
class SMS {
protected:
	double price;
	char number[13];
public:
	SMS(char* number="",double price=0 ) {
		this->price=price;
		strcpy(this->number,number);
	}
	virtual double SMS_cena() {
		price*=1.18;
		return price;
	}
friend ostream& operator<<(ostream & os, SMS& s) {
		os<<"Tel: "<<s.number<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
		return os;
	}

};
class RegularSMS: public SMS {
	bool roaming;
	char msg[1000];
static int procentR;
public:
	RegularSMS(char* number="",double price=0, char *msg="", bool roaming=false ):SMS(number,price),roaming(roaming) {
		strcpy(this->msg,msg);
	}
	double SMS_cena() {
		int brPoraki=(strlen(msg)/160)+1;

		if (roaming) {
			price*=3*brPoraki;
		}
		else {
			price*=1.18*brPoraki;
		}

		return price;
	}
static void set_rProcent(int amount) {
		procentR=amount;
	}

};
class SpecialSMS: public SMS{
	bool isHuman;
	static int procentS;

public:
	SpecialSMS(char* number="",double price=0,  bool isHuman=false ):SMS(number,price),isHuman(isHuman) {

	}
	double SMS_cena() {
		if (!isHuman) {
			price*=1.5;
		}

		return price;
	}
	static void set_sProcent(int amount) {
		procentS=amount;
	}

};
int RegularSMS::procentR=300;
int SpecialSMS::procentS=150;
void vkupno_SMS(SMS** poraka, int n) {
	float regularTotal = 0.0f;
	float specialTotal = 0.0f;
	int regularCount = 0;
	int specialCount = 0;

	for (int i = 0; i < n; i++) {
		SMS* current = poraka[i];
		
		if (dynamic_cast<RegularSMS*>(current)) {
			regularTotal += current->SMS_cena();
			regularCount++;
		}
		else if (dynamic_cast<SpecialSMS*>(current)) {
			specialTotal += current->SMS_cena();
			specialCount++;
		}
	}
	cout << "Vkupno ima " << regularCount << " regularni SMS poraki i nivnata cena e: " << regularTotal << endl;
	cout << "Vkupno ima " << specialCount << " specijalni SMS poraki i nivnata cena e: " << specialTotal << endl;
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

    	delete sms1; delete sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

    	delete sms1; delete sms2;
	}

	return 0;
}