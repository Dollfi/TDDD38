#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;
int main()
{
    vector<string> values {"12", "11", "1", "2", "44"};
    // accumulate can take a function to use instead of normal
    // operator +. The first argument is the total sum until the
    // current element and the second is the current element.
    // The return value should be the new sum.
    cout << accumulate(begin(values), end(values), 0,
            [](int v, string const & s)
            {
                return v + stoi(s);
            });
    cout << endl;
}
