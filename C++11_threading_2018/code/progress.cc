#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

int main()
{
  vector<int> v(100000000, 1);
  
  const auto thread_count{4};
  const auto size{ v.size() };
  const auto chunk_size{ size/thread_count };
  const auto remainder{ size%thread_count };
  int sum{};
  
  mutex mut{};
  condition_variable c{};
  auto progress{0};

  auto b{ begin(v) };
  for ( unsigned i{}; i < thread_count; ++i)
  {
    auto e{ next(b, chunk_size + (i < remainder)) };
    
    thread t{
      [&mut,&c,&sum,&progress](auto start, auto end, const int steps)
      {
        const auto size{ distance(start, end) };
        const auto chunk{ size / steps };
        const auto remainder{ size % steps };
        int local_sum{};
        
        for ( int i{}; i < steps; ++i)
        {
          auto stop{ next(start, chunk + (i < remainder)) };
          local_sum = accumulate(start, stop, local_sum);
          start = stop;
          
          {
            std::lock_guard<std::mutex> m(mut);
            ++progress;
            sum += local_sum;
            local_sum = 0;
          }
          c.notify_one();
//          this_thread::yield();
        }
      }, b, e, 100 / thread_count};
    t.detach();
    b = e;
  }
  
  {
    std::unique_lock<std::mutex> m(mut);
    while ( progress < 100 )
    {
      cout << "\r" << progress << flush;
      c.wait(m);
    }
  }

  cout << endl << sum << endl;
  
  return 0;
}
