// This is a solution for the problem that the "simple" policy design exmple
// tries to solve. This example solves it using polymorphism.
//
// The compiler will have to generate more code because of the virtual functions
// but this solution makes it possible to decide at runtime (templates are ONLY
// evaluated at compile time).
#include <iostream>
using namespace std;
class Base
{
public:
    void foo()
    {
        do_foo();
    }
    virtual ~Base() = default;
private:
    virtual void do_foo() = 0;
};

class Foo1: public Base
{
private:
    void do_foo() override
    {
        cout << "Foo1\n";
    }
};

class Foo2: public Base
{
private:
    void do_foo() override
    {
        cout << "Foo2\n";
    }
};

int main()
{
    Foo1 f1;
    f1.foo();

    Foo2 f2;
    f2.foo();
}
