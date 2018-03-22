#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

int sum(vector<int> const & vals)
{

    return accumulate(begin(vals), end(vals), 0);
}

vector<int> to_ints(vector<string> const & v)
{
    vector<int> result;
    result.resize(v.size());
    // transform takes a range of values (input range) and an
    // output range specified with it's first position. The
    // given function is called for each element in the input
    // range and the result of each call is put into the output
    // range.
    // transform (or any other algorithm) will not (and can not)
    // modify the size of the container. The output range has to
    // be at least as large as the input range.
    transform(begin(v), end(v), begin(result),
              [](string const & s){return stoi(s);});
    return result;
}

int main()
{
    vector<string> values {"12", "11", "1", "2", "44"};
    cout << sum(to_ints(values)) << endl;
}
