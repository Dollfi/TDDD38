/* LatexBeginAsyncSetup */
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
  
/* LatexBeginAsyncWork */
  vector<future<int>> partial_results;
  for ( unsigned i{}; i < thread_count; ++i)
  {
    partial_results.emplace_back(
      // execute our function in it's own thread an get a handle to the future result
      // Note: always specify launch::async to avoid launch::deferred execution
      async<int(data_it, data_it, int)>(launch::async,
                                        accumulate, d.begin(i), d.end(i), 0)
      );
  }
  
/* LatexBeginAsyncSum */
  cout << "Sum: "
       << accumulate(begin(partial_results), end(partial_results), 0,
                     [](int sum, future<int>& fut){ return sum + fut.get(); })
       << endl;
  
  return 0;
}
/* LatexEndAsync */
