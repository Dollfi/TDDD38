#include <iostream>
using namespace std;


// add two arguments of (possibly) different types. auto return type requires C++14
template <typename T, typename U>
auto sum(T t, U u)
{
    return t+u;
}

/*
// possible solution in C++11 (using the common_type type trait to find return type)
template <typename T, typename U>
typename common_type<T,U>::type
sum(T t, U u)
{
    return t+u;
}

// another c++11 solution (trailing return type with decltype)
template <typename T, typename U>
auto sum(T t, U u) -> decltype(t+u)
{
    return t+u;
}
*/

// uses variadic templates to sum many arguments (at least one) recursivly.
// Has two overloads to get a base case for the recursion
template <typename T>
T sum_rec(T t)
{
    return t;
}

template <typename First, typename ...Tail>
auto sum_rec(First f, Tail ...tail)
{
    return f + sum_rec(tail...); // recursive call
}


// Variadic sum with C++17 fold expressions
template <typename First, typename ...Args>
auto sum_fold(First f, Args... args)
{
    return (f + ... + args);
}

int main()
{
    cout << sum(2,3) << endl;
    cout << sum(2.2, 3) << endl;

    cout << sum_rec(2,3,4,65,4.4,65) << endl;

    cout << sum_fold(2,3,45.4,3) << endl;
}
