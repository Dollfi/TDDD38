// The following example shows usage of policies. You abstract your code by letting
// the user provide the actual implementation by specifying a policy class.

// The same task could be solved using a polymorhic base class and dynamic dispatch
// to a (possibly pure) virtual function. The difference is that this solution selects
// the correct overload at compile time which reduces overhead and helps the optimizer

// policy with state and argument forwarding. 

#include <iostream>
using namespace std;

template <typename FooPolicy>
class  Base
{
public:
    // Here I want to forward the argument given to foo to FooPolicy::do_foo
    // accept a variadic template list as forwarding references
    template <typename ...Args>
    void foo(Args && ...args)
    {
        // forward each argument in args ( apply std::forward on each argument)
        foo_state.do_foo(forward<Args>(args)...);
    }
private:
    FooPolicy foo_state {};
};

struct FooPolicy1
{
    void do_foo(int &)
    {
        cout << ++call_count << "Foo according to policy 1\n";
    }
private:
    int call_count {};
};
struct FooPolicy2
{
    static void do_foo(string &&)
    {
        cout << "Foo according to policy 2\n";
    }
};

int main()
{
    Base<FooPolicy1> fp1;
    int a;
    fp1.foo(a);

    Base<FooPolicy2> fp2;
    fp2.foo("hello"s);
}
