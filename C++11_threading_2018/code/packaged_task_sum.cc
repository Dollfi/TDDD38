/* LatexBeginPackagedTaskSetup */
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
  
/* LatexBeginPackagedTaskWork */
  vector<future<int>> partial_results;
  for ( unsigned i{}; i < thread_count; ++i)
  {
    // wrap our function in a future-aware object
    packaged_task<int(data_it, data_it, int)> worker(accumulate<data_it,int>);

    // get a handle to out future result
    partial_results.emplace_back( worker.get_future() );

    // execute our function in it's own thread
    thread{ move(worker), d.begin(i), d.end(i), 0 }.detach();
  }
  
/* LatexBeginPackagedTaskSum */
  cout << "Sum: "
       << accumulate(begin(partial_results), end(partial_results), 0,
                     [](int sum, future<int>& fut){ return sum + fut.get(); })
       << endl;
  
  return 0;
}
/* LatexEndPackagedTask */
