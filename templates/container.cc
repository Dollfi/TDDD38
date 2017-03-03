// simple display of templates for printing data from
// a given container.
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// No output operator for pair available in the STL
template <typename T, typename U>
ostream & operator<<(ostream & os, pair<T,U> p)
{
    return os << p.first << "=> " << p.second;
}

template <typename Container>
void print_container(Container const & c)
{
    for ( auto && e : c )
    {
        cout << e << endl;
    }
}

int main()
{
    vector<int> v {2, 3, 4, 6, 8};
    string s {"hello"};
    // map is an assiciative container that gives
    // a key-value pair for each element.
    map<string, int> m{
                      {"a",  5},
                      {"c", 76}
                    };
    print_container(v);
    print_container(s);
    print_container(m);
}
