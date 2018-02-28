/* Simple function that prints alot of values to cout.
 * Prints all string-like types with quotes.
 *
 * Displays variadic templates, fold expressions and some simple
 * SFINAE (Substitution Failure Is Not An Error) usage.
 */ 
#include <iostream>
#include <string_view>
#include <iomanip>
using namespace std;

// Overload taking any type that is not convertible to string_view.
// If the type is convertible to string_view, enable_if_t will not compile
// (tries to access member ::type in enable_if that doesn't exists if the
//  boolean expression is false). Usually, having code that doesn't compile
// is a bad thing, but with templates this only means that this overload
// will be removed from overload resolution. This technique is usually
// referred to "the overload is removed by substitution failure" or "it
// was SFINAEd away"
template <typename T>
enable_if_t<!is_constructible_v<string_view, T>>
_log(T t)
{
    cout << t;
}

// string_view can bind to (refer to) a given string (std::string or c-string)
void _log(string_view s)
{
    cout << '"' << s << '"';
}


// call _log on each argument in the list args and fold over the comma operator
// The resulting value of the entire fold expression is the return value
// of the last expression (i.e. void).
template <typename ... Args>
void log(Args ... args)
{
    ( _log(args), ...);
}

int main()
{
    string const s{"hi"};
    log(2,3,4, "hello"s, s, 'a');
}
