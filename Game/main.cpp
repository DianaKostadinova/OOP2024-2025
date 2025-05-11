
#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame: public exception {
    string mes;
public:
    ExistingGame() {
        mes = "The game is already in the collection";
    }
    void message() const {
        cout << mes << endl;
    }
    const char* what() const noexcept override {
        return mes.c_str();
    }
};

class Game {
protected:
    char name[100];
    double price;
    bool kupena;
public:
    Game(char *name = (char*)"", double price = 0, bool kupena = false) {
        strcpy(this->name, name);
        this->price = price;
        this->kupena = kupena;
    }
    Game(const Game &g) {
        strcpy(this->name, g.name);
        this->price = g.price;
        this->kupena = g.kupena;
    }
    virtual ~Game() {}

    friend ostream& operator<<(ostream& os, const Game& g) {
        os << "Game: " << g.name << ", regular price: $" << g.price;
        if (g.kupena) {
            os << ", bought on sale";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Game& g) {
        is >> g.name >> g.price >> g.kupena;
        return is;
    }

    bool operator==(const Game& g) const {
        return strcmp(this->name, g.name) == 0;
    }

    virtual double getPrice() const {
        return kupena ? price * 0.7 : price;
    }

    virtual Game* clone() const {
        return new Game(*this);
    }
};

class SubscriptionGame : public Game {
    double monthly;
    int month;
    int year;
public:
    SubscriptionGame(char *name = (char*)"", double price = 0, bool kupena = false, double monthly = 0, int month = 0, int year = 0)
        : Game(name, price, kupena), monthly(monthly), month(month), year(year) {}

    SubscriptionGame(const SubscriptionGame& sg)
        : Game(sg), monthly(sg.monthly), month(sg.month), year(sg.year) {}

    friend ostream& operator<<(ostream& os, const SubscriptionGame& sg) {
        os << static_cast<const Game&>(sg);
        os << ", monthly fee: $" << sg.monthly << ", purchased: " << sg.month << "-" << sg.year;
        return os;
    }

    friend istream& operator>>(istream& is, SubscriptionGame& sg) {
        is >> sg.name >> sg.price >> sg.kupena >> sg.monthly >> sg.month >> sg.year;
        return is;
    }

    int monthsPassed() const {
        return (2018 - year) * 12 + (5 - month);
    }

    double getMonthly() const {
        return monthly;
    }

    double getPrice() const override {
        return Game::getPrice() + monthsPassed() * monthly;
    }

    Game* clone() const override {
        return new SubscriptionGame(*this);
    }
};

class User {
    char username[100];
    Game **g;
    int counter;

    void copy(const User &u) {
        strcpy(username, u.username);
        counter = u.counter;
        g = new Game*[counter];
        for (int i = 0; i < counter; i++) {
            g[i] = u.g[i]->clone();
        }
    }

public:
    User(char *username = (char*)"") {
        strcpy(this->username, username);
        counter = 0;
        g = nullptr;
    }

    User(const User &u) {
        copy(u);
    }

    User& operator=(const User &u) {
        if (this != &u) {
            for (int i = 0; i < counter; i++) delete g[i];
            delete[] g;
            copy(u);
        }
        return *this;
    }

    ~User() {
        for (int i = 0; i < counter; i++) delete g[i];
        delete[] g;
    }

    User& operator+=(const Game& game) {
        for (int i = 0; i < counter; i++) {
            if (*g[i] == game) throw ExistingGame();
            cout<<endl;
        }

        Game **tmp = new Game*[counter + 1];
        for (int i = 0; i < counter; i++) tmp[i] = g[i];
        tmp[counter] = game.clone();
        delete[] g;
        g = tmp;
        counter++;
        return *this;
    }

    double total_spent() const {
        double sum = 0;
        for (int i = 0; i < counter; i++) {
            sum += g[i]->getPrice();
        }
        return sum;
    }

    friend ostream& operator<<(ostream& os, const User& u) {
        os << "User: " << u.username << endl;
        for (int i = 0; i < u.counter; i++) {
            os << "- " << *u.g[i] << endl;
        }
        return os;
    }
};


int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}