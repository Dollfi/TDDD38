#include "headers.h"
using namespace std;
struct Base
{
    void fun() {
        cout << "Base::fun";
    }
};

struct Derived: Base
{
    void fun() {
        cout << "Derived::fun";
    }
};

void foo(Base & b) {
    b.fun();
}

int main() {
    Derived d;
    foo(d);
}
