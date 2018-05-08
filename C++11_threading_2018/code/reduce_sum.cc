#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

using data = vector<int>;
using data_it = data::iterator;

int main()
{
  vector<int> v(100000000, 1);
    
  cout << "Sum: "
       << reduce(execution::par, begin(v), end(v), 0);
       << endl;
  
  return 0;
}
