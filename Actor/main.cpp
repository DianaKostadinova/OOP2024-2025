#include <iostream>
#include <cstring>
using namespace std;
class MovieActor {
protected:
    char *name;
    char country[40];
    double rating;
    int yearlyFilms;
    double netWorth;
    void copy(const MovieActor& m) {
this->name=new char[strlen(m.name)+1];
        strcpy(this->name,m.name);
        strcpy(country,m.country);
        rating=m.rating;
        yearlyFilms=m.yearlyFilms;
        netWorth=m.netWorth;
    }
public:
    MovieActor(char *name="", char *country="", double rating=0, int yearlyFilms=0, double netWorth=0):rating(rating),yearlyFilms(yearlyFilms),netWorth(netWorth) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->country,country);
    }
    MovieActor(const MovieActor& m) {
        copy(m);
    }
    MovieActor& operator=(const MovieActor& m) {
        if (this!=&m) {
            copy(m);
        }
        return *this;
    }
    double rat() {
        return rating*0.4+yearlyFilms*0.2+netWorth*0.4;
    }
    void print() {
cout<<name<<" "<<country<<endl;
        cout<<"Movies this year: "<<yearlyFilms<<endl;
        cout<<"Total earnings: "<<netWorth<<endl;
        cout<<"Rating"<<rat()<<endl;
    }
    ~MovieActor() {
        delete[]name;
    }
};
class OscarWinner: public MovieActor {
    double avg;
    int movieAfter;
    double zarabotka;
    void copy(const OscarWinner& o) {
        MovieActor::copy(o);
        avg=o.avg;
        movieAfter=o.movieAfter;
        zarabotka=o.zarabotka;
    }
public:
    OscarWinner(char *name="", char *country="", double rating=0, int yearlyFilms=0, double netWorth=0, double avg=0, int movieAfter=0, double zarabotka=0):MovieActor(name,country,rating,yearlyFilms,netWorth), avg(avg),movieAfter(movieAfter),zarabotka(zarabotka){}
    OscarWinner(MovieActor& m, double avg,int movieAfter,double zarabotka):MovieActor(m) {
        this->avg=avg;
        this->movieAfter=movieAfter;
        this->zarabotka=zarabotka;
    }
    OscarWinner(const OscarWinner& o) {
        copy(o);
    }
    OscarWinner& operator=(const OscarWinner& o) {
        if (this!=&o) {
            copy(o);
        }
        return *this;
    }
    ~OscarWinner() {
    }
    double rating() {
        return avg*0.6+movieAfter*0.1+zarabotka*0.3;
    }
    void print() {
        MovieActor::print();
        cout<<"Oscar Rating: "<<rating()<<endl;
        cout<<"New Rating: "<<avg<<endl;
    }
};
int main() {
    char name[100];
    char country[41];
    double avg_rating;
    int num_movies;
    double earnings;
    double post_avg_rating;
    int post_num_movies;
    double post_earnings;

    int n;
    cin >> n;

    if (n == 1) {
        // Test MovieActor basic functionality
        cout << "MOVIE ACTORS:" << endl;
        cout << "=====================================" << endl;
        int numActors;
        cin >> numActors;

        MovieActor* actors = new MovieActor[numActors];

        for (int i = 0; i < numActors; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            actors[i] = MovieActor(name, country, avg_rating, num_movies, earnings);
            actors[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] actors;
    }
    else if (n == 2) {
        // Test MovieActor and create OscarWinner from it
        int numActors;
        cin >> numActors;

        MovieActor* actors = new MovieActor[numActors];
        OscarWinner* oscarWinners = new OscarWinner[numActors];
        for (int i = 0; i < numActors; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            cin >> post_avg_rating >> post_num_movies >> post_earnings;

            actors[i] = MovieActor(name, country, avg_rating, num_movies, earnings);
            oscarWinners[i] = OscarWinner(actors[i], post_avg_rating, post_num_movies, post_earnings);
        }

        cout << "MOVIE ACTORS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numActors; ++i) {
            actors[i].print();
            cout << "-------------------------" << endl;
        }

        cout << "OSCAR WINNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numActors; ++i) {
            oscarWinners[i].print();
            cout << "-------------------------" << endl;
        }

        delete[] actors;
        delete[] oscarWinners;
    }
    else if (n == 3) {
        // Test OscarWinner with all arguments constructor
        int numWinners;
        cin >> numWinners;

        OscarWinner* oscarWinners = new OscarWinner[numWinners];

        for (int i = 0; i < numWinners; ++i) {
            cin >> name >> country >> avg_rating >> num_movies >> earnings;
            cin >> post_avg_rating >> post_num_movies >> post_earnings;

            oscarWinners[i] = OscarWinner(name, country, avg_rating, num_movies, earnings,
                                          post_avg_rating, post_num_movies, post_earnings);
        }

        cout << "OSCAR WINNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < numWinners; ++i) {
            oscarWinners[i].print();
            cout << "-------------------------" << endl;
        }
        delete[] oscarWinners;
    }
    else if (n == 4) {
        // Test copy constructor and operator= for MovieActor
        MovieActor actor1;
        cin >> name >> country >> avg_rating >> num_movies >> earnings;
        actor1 = MovieActor(name, country, avg_rating, num_movies, earnings);

        MovieActor actor2(actor1); // Using copy constructor
        MovieActor actor3;
        actor3 = actor1;           // Using operator=

        cout << "ORIGINAL:" << endl;
        actor1.print();
        cout << "-------------------------" << endl;

        cout << "COPY CONSTRUCTOR:" << endl;
        actor2.print();
        cout << "-------------------------" << endl;

        cout << "OPERATOR=:" << endl;
        actor3.print();
        cout << "-------------------------" << endl;
    }
    else if (n == 5) {
        // Test copy constructor and operator= for OscarWinner
        OscarWinner winner1;
        cin >> name >> country >> avg_rating >> num_movies >> earnings;
        cin >> post_avg_rating >> post_num_movies >> post_earnings;

        winner1 = OscarWinner(name, country, avg_rating, num_movies, earnings,
                              post_avg_rating, post_num_movies, post_earnings);

        OscarWinner winner2(winner1); // Using copy constructor
        OscarWinner winner3;
        winner3 = winner1;            // Using operator=

        cout << "ORIGINAL:" << endl;
        winner1.print();
        cout << "-------------------------" << endl;

        cout << "COPY CONSTRUCTOR:" << endl;
        winner2.print();
        cout << "-------------------------" << endl;

        cout << "OPERATOR=:" << endl;
        winner3.print();
        cout << "-------------------------" << endl;
    }

    return 0;
}