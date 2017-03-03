// shows different ways of defining a function that concatinates 
// the string representation of all arguments passed (using to_string)
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

// Different ways of adding to_string for all types that are
// convertible to string (using a string constructor)

// Adding a template argument that will give substitution failure
// for types that can't be used as constructor argument
template <typename StringType,
          typename = enable_if_t<
                        is_constructible<string, 
                                         decay_t<StringType>>::value
                                >
         >
auto to_string(StringType && s)
{
    string t{forward<StringType>(s)};
    return t;
}

/*
 // using enable_if to get the return type, also depends on SFINAE
template <typename StringType>
enable_if_t<
        is_constructible<string, StringType>::value,
        string>
 to_string(StringType && s)
{
    return string{forward<StringType>(s)};
}

// use auto + decltype instead
template <typename ST>
auto to_string(ST && s)
-> decltype(string{s})

{
    return string{forward<ST>(s)};
}

// use a type_trait as a concept 
//  (requires gcc >=6.1 and compile with -fconcepts)
template <typename T>
requires is_constructible<string, T>::value 
auto to_string(T && s)
{
    return string{forward<T>(s)};
}
*/

// use fold expressions. forward each argument to to_string.
template <typename ...Args>
string concat(Args &&...args)
{
    return ( to_string(forward<Args>(args)) + ... );
}
int main()
{
    string s{"hello"};
    cout << concat(2, s, "hi",3, "hi"s,5,.4, 5) << endl;
}
