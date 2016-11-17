#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

vector<pair<char,int>> count_chars(istream & is )
{
    vector<pair<char, int>> res;
    for ( char c; is.get(c); )
    {
        auto it = lower_bound(begin(res), end(res), c, 
                [](pair<char,int> p, char c){return p.first < c;});
        if ( it != res.end() && it->first == c )
        {
            it->second++;
        }
        else
        {
            res.insert(it, {c,1});
        }
    }
    return res;
}

auto count_chars2(istream & is)
{
    map<char,int> res;
    for ( char c; is.get(c); )
    {
        res[c]++;
    }
    // returns sorted by char
    // return res;

    // sort by count (by using vector)
    vector<pair<char,int>> values(begin(res), end(res));
    // already sorted by key, stable_sort retains order between equal values
    stable_sort(begin(values), end(values),
                [](auto l,auto r){return r.second < l.second;});

    return values;
}

int main(int argc, char * argv[])
{
    if ( argc != 2 )
    {
        cerr << "No file provided!\n";
        return 1;
    }
    ifstream ifs {argv[1]};
    if (!ifs)
    {
        cerr << "File \"" << argv[1] << "\" could not be opened\n";
        return 2;
    }

    for ( auto p: count_chars2(ifs) )
    {
        cout << "'" << p.first << "': " << p.second << '\n';
    }
}
