#include <iostream>
#include <vector>
#include <numeric>
#include <future>

#include "divider.h"

using namespace std;

using data = vector<int>;
using data_it = data::iterator;

int main()
{
  const auto thread_count{9};
  
  vector<int> v(100000000, 1);
  Divider<vector<int>> d{v, thread_count};
  
  vector<future<int>> partial_results;
  for ( unsigned i{}; i < thread_count; ++i)
  {
    promise<int> p;
    
    // get a handle to out future result
    partial_results.emplace_back( p.get_future() );
    
    // execute our function in it's own thread
    thread{
      // wrap our function in a future-aware lamda
      [](promise<int> p, data_it b, data_it e, int s)
      {
        auto r{ accumulate(b, e, s) };
        p.set_value(r);
      },
        // specify thread argumenta
        move(p), d.begin(i), d.end(i), 0
    }.detach();
  }
  
  cout << "Sum: "
       << accumulate(begin(partial_results), end(partial_results), 0,
                     [](int sum, future<int>& fut){ return sum + fut.get(); })
       << endl;
  
  return 0;
}
