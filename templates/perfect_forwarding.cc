#include <iostream>
#include <utility>
using namespace std;

void foo(string const &) // accepts anything
{
    cout << "const ref" << endl;
}

void foo(string &&) // requires an r-value
{
    cout << "rref" << endl;
}

template <typename T>
void fun(T&& t) 
// T&& is a forwarding reference (or universal reference), not 
// an r-value reference due to reference collapsing
{
    // Will use the "name rule", everything with a name is an l-value
    // foo(t);

    foo(forward<T>(t)); // pass t exactly as it was passed to fun
}

int main()
{
    string s {"hello"};
    fun(s); // call with l-value
    fun(move(s)); // call with r-value
}
