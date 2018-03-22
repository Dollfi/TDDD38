#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

int sum(vector<int> const & vals)
{
    int result {};
    for ( int i: vals )
    {
        result += i;
    }
    return result;

}

vector<int> to_ints(vector<string> const & v)
{
    vector<int> result;
    // for_each accepts an open range of values (given by iterators)
    // and a function to apply to each element in that range.
    // Here we provide a lambda (an anonymous "function" that binds
    // the vector result by reference to be able to modify it. By
    // default (if the []-part "capture block" is left empty), the
    // lambda will only have acces to it's parameters.
    for_each(begin(v), end(v), 
            [&result](string const & s){
                result.push_back(stoi(s));
            });
    
    return result;
}

int main()
{
    vector<string> values {"12", "11", "1", "2", "44"};
    cout << sum(to_ints(values)) << endl;
}
