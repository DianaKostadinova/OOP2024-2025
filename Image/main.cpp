#include <complex>
#include <iostream>
#include <cstring>
using namespace std;

class Image {
protected:
    char *pictureName;
    char owner[50];
    int sirina, visina;
public:
    Image(char *name = (char*)"untitled", char *owner = (char*)"unknown", int sirina = 800, int visina = 800) {
        pictureName = new char[strlen(name) + 1];
        strcpy(pictureName, name);
        strcpy(this->owner, owner);
        this->sirina = sirina;
        this->visina = visina;
    }

    Image(const Image &other) {
        pictureName = new char[strlen(other.pictureName) + 1];
        strcpy(pictureName, other.pictureName);
        strcpy(owner, other.owner);
        sirina = other.sirina;
        visina = other.visina;
    }

    Image& operator=(const Image &other) {
        if (this != &other) {
            delete[] pictureName;
            pictureName = new char[strlen(other.pictureName) + 1];
            strcpy(pictureName, other.pictureName);
            strcpy(owner, other.owner);
            sirina = other.sirina;
            visina = other.visina;
        }
        return *this;
    }

    virtual ~Image() {
        delete[] pictureName;
    }

    virtual float fileSize() const {
        return float(visina) * float(sirina) * 3.0;
    }

    friend ostream &operator<<(ostream &os, const Image &i) {
        os << i.pictureName << " " << i.owner << " " << (int)i.fileSize();
        return os;
    }

    bool operator>(const Image &i) const {
        return fileSize() > i.fileSize();
    }

    virtual char *getName() const {
        return pictureName;
    }

    virtual char *getOwner() const {
        return (char*)owner;
    }
};

class TransparentImage : public Image {
    bool poddrzuva;
public:
    TransparentImage(char *name = (char*)"untitled", char *owner = (char*)"unknown", int sirina = 800, int visina = 800, bool poddrzuva = false)
        : Image(name, owner, sirina, visina), poddrzuva(poddrzuva) {}

    float fileSize() const override {
        if (poddrzuva) {
            return float(visina) * float(sirina) * 4.0;
        }
        return float(visina) * float(sirina) + (float(visina) * float(sirina) / 8.0);
    }

    friend ostream &operator<<(ostream &os, const TransparentImage &i) {
        os << i.pictureName << " " << i.owner << " " << (int)i.fileSize();
        return os;
    }

    bool operator>(const Image &i) const {
        return fileSize() > i.fileSize();
    }

    char *getName() const override {
        return pictureName;
    }

    char *getOwner() const override {
        return (char*)owner;
    }
};

class Folder {
    char name[255];
    char owner[50];
    Image *img[100];
    int counter;
public:
    Folder(char *name = (char*)"", char *owner = (char*)"unknown") {
        strcpy(this->name, name);
        strcpy(this->owner, owner);
        counter = 0;
    }

    // Copy constructor
    Folder(const Folder &other) {
        strcpy(this->name, other.name);
        strcpy(this->owner, other.owner);
        this->counter = 0;


        for (int i = 0; i < other.counter; i++) {
            if (dynamic_cast<TransparentImage*>(other.img[i])) {
                TransparentImage* ti = dynamic_cast<TransparentImage*>(other.img[i]);
                img[counter++] = new TransparentImage(*ti);
            } else {
                img[counter++] = new Image(*other.img[i]);
            }
        }
    }


    Folder& operator=(const Folder &other) {
        if (this != &other) {
            // Free existing resources
            for (int i = 0; i < counter; i++) {
                delete img[i];
            }

            strcpy(this->name, other.name);
            strcpy(this->owner, other.owner);
            this->counter = 0;


            for (int i = 0; i < other.counter; i++) {
                if (dynamic_cast<TransparentImage*>(other.img[i])) {
                    TransparentImage* ti = dynamic_cast<TransparentImage*>(other.img[i]);
                    img[counter++] = new TransparentImage(*ti);
                } else {
                    img[counter++] = new Image(*other.img[i]);
                }
            }
        }
        return *this;
    }

    ~Folder() {
        for (int i = 0; i < counter; i++) {
            delete img[i];
        }
    }

    Folder &operator+=(const Image &i) {
        if (counter < 100) {

            const TransparentImage* ti = dynamic_cast<const TransparentImage*>(&i);
            if (ti) {
                img[counter++] = new TransparentImage(*ti);
            } else {
                img[counter++] = new Image(i);
            }
        }
        return *this;
    }

    float folderSize() const {
        float sum = 0;
        for (int i = 0; i < counter; i++) {
            sum += img[i]->fileSize();
        }
        return sum;
    }

    Image *getMaxFile() {
        if (counter == 0) return nullptr;
        Image *temp = img[0];
        for (int i = 1; i < counter; i++) {
            if (*img[i] > *temp) {
                temp = img[i];
            }
        }
        return temp;
    }

    friend ostream &operator<<(ostream &os, const Folder &f) {
        os << f.name << " " << f.owner << endl;
        cout<<"--"<<endl;
        for (int i = 0; i < f.counter; i++) {
            os << f.img[i]->getName() << " " << f.img[i]->getOwner() << " " << (int)f.img[i]->fileSize() << endl;
        }
        if (f.counter > 0) os << "--" << endl;
        os << "Folder size: " << (int)f.folderSize();
        return os;
    }

    Image *operator[](int index) {
        if (index < 0 || index >= counter) return nullptr;
        return img[index];
    }
};

Folder max_folder_size(Folder *f, int br) {
    Folder temp = f[0];
    for (int i = 1; i < br; i++) {
        if (f[i].folderSize() > temp.folderSize()) {
            temp = f[i];
        }
    }
    return temp;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1 << endl;

      Image f2(name);
      cout<< f2 << endl;

      Image f3(name, user_name);
      cout<< f3 << endl;

      Image f4(name, user_name, w, h);
      cout<< f4 << endl;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1 << endl;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4 << endl;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
            delete f;  // Clean up temporary object
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
            delete tf;  // Clean up temporary object
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
            delete f;  // Clean up temporary object
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
            delete tf;  // Clean up temporary object
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
            delete f;  // Clean up temporary object
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
            delete tf;  // Clean up temporary object
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
              delete f;  // Clean up temporary object
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
              delete tf;  // Clean up temporary object
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};