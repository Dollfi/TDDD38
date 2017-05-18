#include "headers.h"
using namespace std;
struct Data{
    Data(){
        cout << 3;
    }
    ~Data(){
        cout << 1;
    }
};

struct My_Class{
    My_Class(){
        cout << 5;
    }
    ~My_Class(){
        cout << 8;
    }
    Data a;
};

int main(){
    My_Class{};
}
