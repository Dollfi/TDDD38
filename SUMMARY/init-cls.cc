#include "headers.h"
using namespace std;
struct Base{
    Base(){
        cout << 3;
    }
    ~Base(){
        cout << 1;
    }
};

struct Derived{
    Derived(){
        cout << 5;
    }
    ~Derived(){
        cout << 8;
    }
};

int main(){
    Derived{};
}
