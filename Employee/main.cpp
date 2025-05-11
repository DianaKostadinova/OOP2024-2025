#include <iostream>
#include <cstring>
using namespace std;
class Employee {
protected:
    string name;
    int years;
public:
    Employee(string name="",int years=0):name(name),years(years){}
    virtual double bonus()const{}
    virtual double pay(){}
    bool operator==(Employee &e)
    {
        return bonus() == e.bonus();
    }
    virtual ~Employee(){}
};
class SalaryEmployee:public Employee {
    double plata;
public:
    SalaryEmployee(string name="",int years=0, double plata=0):Employee(name,years),plata(plata){}
    double bonus() {
        return plata*years/100;
    }
    double pay() {
        return plata+bonus();
    }
};
class HourlyEmployee: public Employee {
    int hours;
    double hourlyPay;
public:
    HourlyEmployee(string name="",int years=0, int hours=0, double hourlyPay=0):Employee(name,years), hours(hours), hourlyPay(hourlyPay) {}
    double bonus() {
         double vkupno=0;
        if (hours <=320) {
          vkupno=0;
        }
        else {
            int kolku=hours-320;
            for (int i=0; i<kolku;i++) {
                vkupno+=hourlyPay/2;
            }
        }
return vkupno;
    }
    double pay() {
return hours*hourlyPay+bonus();
    }
};
class Freelancer: public Employee {
    int projects;
    double *sums;
public:
    Freelancer(string name="",int years=0,int projects=0, double *sums=0):Employee(name, years),projects(projects) {
        for (int i=0; i<projects; i++) {
            this->sums[i]=sums[i];
        }
    }
    double bonus() {
        int vkupno=0;
        if (projects>5) {
            for (int i=0; i<projects-5; i++) {
                vkupno+=1000;
            }
        }
        return vkupno;
    }
    double pay() {
        int vkupno=0;
        for (int i=0; i<projects; i++) {
            vkupno+=sums[i];
        }
        return vkupno+bonus();
    }
    ~Freelancer(){delete[]sums;}
};
class Company {
    string name;
    int vraboteni;
    Employee** e;
public:
    Company(string name=""):name(name){}
    Company &operator+=(Employee *emp)
    {
        Employee **temp = new Employee *[vraboteni+ 1];

        for (int i = 0; i < vraboteni; i++)
            temp[i] = e[i];
        temp[vraboteni] = emp;

        delete[] e;
        e = temp;
        vraboteni++;

        return *this;
    }
double vkupnaPlata() {
        double vkupno=0;
        for (int i=0; i<vraboteni; i++) {
           vkupno+= e[i]->pay();
        }
        return vkupno;
    }
    double filtriranaPlata(Employee* emp) {
        double s = 0;

        for (int i = 0; i < vraboteni; i++)
            if (*e[i] == *emp)
                s += e[i]->pay();

        return s;
    }

    void pecatiRabotnici()
    {
        int s = 0, h = 0, f = 0;

        for (int i = 0; i < vraboteni; i++)
        {
            SalaryEmployee *salary = dynamic_cast<SalaryEmployee *>(e[i]);
            HourlyEmployee *hourly = dynamic_cast<HourlyEmployee *>(e[i]);
            Freelancer *free = dynamic_cast<Freelancer *>(e[i]);

            if (dynamic_cast<SalaryEmployee *>(e[i]))
                s++;
            else if (dynamic_cast<HourlyEmployee *>(e[i]))
                h++;
            else if (dynamic_cast<Freelancer *>(e[i]))
                f++;
        }

        cout << "Vo kompanijata " << name << " rabotat: " << endl;
        cout << "Salary employees: " << s << endl;
        cout << "Hourly employees: " << h << endl;
        cout << "Freelancers: " << f << endl;
    }
~Company(){delete[]e;}
};

int main()
{

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];

    int experience;
    int type;

    for (int i = 0; i < n; ++i)
    {
        cin >> type;
        cin >> employeeName >> experience;

        if (type == 1)
        {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName,  experience, basicSalary);
        }

        else if (type == 2)
        {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, experience, hoursWorked, hourlyPay);
        }

        else
        {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i = 0; i < numProjects; ++i)
            {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee *emp = new HourlyEmployee("Petre_Petrov",  6, 340, 80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
    return 0;
}