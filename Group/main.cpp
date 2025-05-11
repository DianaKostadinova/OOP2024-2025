#include <iostream>
#include <cstring>
using namespace std;
class User {
    char *name;
    char *company;
    int position;
    void copy(const User& u) {
        this->name=new char[strlen(u.name)+1];
        this->company=new char[strlen(u.company)+1];
        strcpy(this->name,u.name);
        strcpy(this->company,u.company);
        this->position=u.position;
    }
public:
    User(char *name="", char *company="", int position=0) {
        this->name=new char[strlen(name)+1];
        this->company=new char[strlen(company)+1];
        strcpy(this->name,name);
        strcpy(this->company,company);
        this->position=position;
    }
    User(const User& u) {
        copy(u);
    }
    User &operator=(const User &u) {
        if (this!=&u) {
            delete[]name;
            delete[]company;
            copy(u);
        }
        return *this;
    }
    ~User() {
        delete[]name;
        delete[]company;
    }
    friend ostream& operator <<(ostream &os, const User& u) {
      os<<u.name<<" "<<u.company<<" "<<u.position<<endl;
        return os;

    }
    friend istream &operator>>(istream &in, User &user) {
        char tempN[100];
        char tempC[100];
        in>>tempN>>tempC;
        delete[]user.name;
        delete[]user.company;
        user.name=new char[strlen(tempN)+1];
        user.company=new char[strlen(tempC)+1];
        strcpy(user.name,tempN);
        strcpy(user.company,tempC);
        in>>user.position;
        return in;

    }
    char *getUsername() const {
        return name;
    }

    void setUsername(char *username) {
        delete[] name;
        this->name = new char[strlen(username) + 1];
        strcpy(this->name, username);
    }
    int getPositioln() const{
        return position;
    }

};
class Group {
protected:
    User *users;
    int size;
    string name;
public:
    Group(string name="") {
        this->name=name;
        size=0;
        users=new User[0];
    }
    Group(const Group& g) {
        name = g.name;
        size = g.size;

        users = new User[g.size];
        for (int i = 0; i < size; i++) {
            users[i] = g.users[i];
        }
    }
    Group& operator=(const Group& g) {
        if (this != &g) {
            delete[] users;
            name = g.name;
            size = g.size;
            users = new User[size];
            for (int i = 0; i < size; i++) {
                users[i] = g.users[i];
            }
        }
        return *this;
    }
    ~Group(){delete[]users;}
  virtual  void addMember(User& u) {
        for (int i=0; i<size;i++) {
            if (strcmp(users[i].getUsername(), u.getUsername()) == 0){
                return;
            }
        }
        users[size]=u;
        size++;
    }
    double average()const{
        int sum=0;
        for (int i=0; i<size; i++) {
            sum+=users[i].getPositioln();
        }
        return sum/size;
    }
    virtual double rating()const{
        return (10-average())*size/100;
    }
    friend ostream& operator<<(ostream& out, const Group& g) {
        out << "Group: " << g.name << endl;
        out << "Members: " << g.size << endl;
        out << "Rating: " << g.rating() << endl;
        out << "Members list: " << endl;
        if (g.size == 0) {
            out << "EMPTY" << endl;
        } else {
            for (int i = 0; i < g.size; i++) {
                out << i + 1 << ". " << g.users[i] << endl;
            }
        }

        return out;
    }
};
class PrivateGroup:public Group {
    static int capacity;
    static float koeficient;
public:
    PrivateGroup(string name=""):Group(name) {

    }
    PrivateGroup(const PrivateGroup& p):Group(p) {

    }
    PrivateGroup& operator=(const PrivateGroup& p) {
        if (this!=&p) {
            Group::operator=(p);
        }
        return *this;
    }
    void addMember(User &u) {
        if (this->size>=capacity) {
            return;
        }
        Group::addMember(u);
    }
    static void setCapacity(int cap) {
      capacity = cap;
    }

    static int getCapacity() {
        return capacity;
    }
    double rating() {
return (10-Group::average())*(this->size/capacity)*koeficient;
    }
    friend ostream &operator<<(ostream& os, const PrivateGroup& p) {
        os << "Private ";
        Group group(p);
        os << group;
        return os;
    }

};

int PrivateGroup::capacity=10;
float PrivateGroup::koeficient=0.8;



int main() {
    cout << "INTEGRATION TEST" << endl;
    char name[50];
    int nGroups;
    cin >> nGroups;
    Group **groups = new Group *[nGroups];
    for (int i = 0; i < nGroups; i++) {
        int type;
        cin >> type;
        cin >> name;
        if (type == 1) { //normal group
            groups[i] = new Group(name);
        } else { //private group
            groups[i] = new PrivateGroup(name);
        }
        int nUsers;
        cin >> nUsers;
        for (int j = 0; j < nUsers; j++) {
            User u;
            cin >> u;

            groups[i]->addMember(u);

        }
    }

    cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }
    PrivateGroup::setCapacity(15);
    cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }
}