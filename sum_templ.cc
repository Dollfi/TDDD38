#include <iostream>
using namespace std;

template <typename T>
auto sum_range(T end, T start=T{})
// -> T   // trailing return type needed in C++11
{
    T res{};
    for ( ; start <= end; ++start )
    {
        res += start;
    }
    return res;
}


// variadic template to sum values
// base case, takes a single value
template<typename T>
auto sum(T const & t)
{
    return t;
}

// all other. Takes at least one argument
// Can be any types as long as operator+ is overloaded
template <typename First, typename ...Rest>
auto sum(First const & f, Rest ...r) 
{
    return f + sum(r...);
}

int main()
{
    cout << sum_range(5) << endl;
    cout << sum_range(5,4) << endl;
    cout << sum_range<double>(5.5,3.5) << endl;
    cout << sum(1,3,2,5.6,7,7) << endl;
    // Why do the following calls differ?
    // suffix s is a C++14 user-defined literal to 
    // create a std::string-literal instead of c-string
    cout << sum("Hi", ' ', "all"s) << endl;
    cout << sum("Hi"s, ' ', "all") << endl;        
}
