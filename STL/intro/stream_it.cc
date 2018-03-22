// Some stream iterators
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    // print all values in v separated by comma to cout
    vector<int> v { 1,2,3,4,6};
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});

    // use constructor that takes iterator to initialize. Read
    // from cin
    vector<int> vals { istream_iterator<int>{cin},
                       istream_iterator<int>{} };

    // read from cin and print to cout...
    copy(istream_iterator<int>{cin},
            istream_iterator<int>{},
            ostream_iterator<int>{cout, "\n"});
}

