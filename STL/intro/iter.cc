// Some simple iterator usage
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    // printing values using iterators
    vector<int> v{2,3,4,5};
    for ( auto it { begin(v) }; it != end(v); ++it )
    {
        cout << *it;
    }
    // doing the same with range-based for
    for ( int & i: v )
    {
        cout << i;
    }
 
    // the range-based for will be translated to (something close to) this
    {
        auto start { begin(v) };
        auto stop { end(v) };
        for ( ; start != stop; ++start )
        {
            int & i { *start };
            cout << i;
        }
    }
  
}
