#include "headers.h"
using namespace std;
struct Base
{
    virtual void fun() const {
        cout << "Base::fun";
    }
};

struct Derived: Base
{
    void fun() const override {
        cout << "Derived::fun";
    }
};

void foo(Base const & b) {
    b.fun();
}

int main() {
    Derived d;
    foo(d);
}
