#include "headers.h"
using namespace std;
int main()
{
    vector<int> vals {2,1,4,1};
    unique(begin(vals), end(vals));
    copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "});
}
