#include <iostream>
#include <tuple>
using namespace std;


int main()
{
    std::tuple<int, double, char> tup { 1, 4.4, 'a'};
    // c++17 can use 
    // tuple tup {1, 4.4, 'a'};
    // due to changed rules on class template type deductions (P0091)
    
    // get can be uesd both with index (always possible) and with
    // type (if it is unique, get<int>(tuple{1,2,3}) wouldn't work)
    get<int>(tup);
    cout << get<int>(tup) << get<2>(tup);
    tuple<int, int> t {2,3};
    int a{},b;
    // tie creates a tuple of references to l-values.
    auto tp = tie(a,b);
    get<0>(tp) = 5; // modify a
    cout << a;
    auto [c,d] = tp; // structured binding. c and d are declared as new variables
                     // of the same type as corresponding element in tp. In this
                     // case c becomes a reference to a.
    cout << c;
    c = 6;
    cout << endl;
    cout << c;
    cout << a;
}
