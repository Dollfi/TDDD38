// The following example shows usage of policies. You abstract your code by letting
// the user provide the actual implementation by specifying a policy class.

// The same task could be solved using a polymorhic base class and dynamic dispatch
// to a (possibly pure) virtual function. The difference is that this solution selects
// the correct overload at compile time which reduces overhead and helps the optimizer

// simple version (policy without state and no arguments)

#include <iostream>
using namespace std;

template <typename FooPolicy>
class  Base
{
public:
    void foo()
    {
        FooPolicy::do_foo();
    }
};

struct FooPolicy1
{
    static void do_foo()
    {
        cout << "Foo according to policy 1\n";
    }
};
struct FooPolicy2
{
    static void do_foo()
    {
        cout << "Foo according to policy 2\n";
    }
};

int main()
{
    Base<FooPolicy1> fp1;
    fp1.foo();

    Base<FooPolicy2> fp2;
    fp2.foo();
}
