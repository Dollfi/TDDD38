// Short example of std::optional. Use it to allow the user to not pass a value (or to make it possible to return "nothing").
#include <optional>
#include <iostream>
using namespace std;

// nullopt is a value of type nullopt_t which is used to
// represent a not set optional object.
void fun(optional<int> val = nullopt)
{
    // optional is contextually convertible (has operator bool)
    if ( val )
    {
        // use value() to access the value, throws if not set.
        cout << val.value() << '\n';
    }
    else
        cout << "No value\n";

}

optional<int> foo(bool b)
{
    if ( b )
        return 4;
    else
        return nullopt; // has to return a value, nullopt is a good choise
}


int main()
{
    fun(4);
    fun();
    // value_or gives the value stored or the provided value if unset.
    cout << foo(false).value_or(2);
}
