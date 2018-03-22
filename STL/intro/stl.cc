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
    for ( string const & s: v )
    {
        result.push_back(stoi(s));
    }
    return result;
}

int main()
{
    vector<string> values {"12", "11", "1", "2", "44"};
    cout << sum(to_ints(values)) << endl;
}
