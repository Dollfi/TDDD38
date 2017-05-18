#include "headers.h"
using namespace std;
struct Base
{
    virtual void fun() {
        cout << "Base::fun";
    }
};

struct Derived: Base
{
    virtual void fun() const {
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
