#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono_literals;

int async_work()
{
  this_thread::sleep_for(2s);
  return 4711;
}

int main()
{
  {
    packaged_task<int()> task{async_work};
    
    future<int> result = task.get_future();
    
    thread th{move(task)};
    th.detach();
    cout << "Just after task() call." << endl;
    
    cout << result.get() << endl;
  }
  
  {
    future<int> result{ async(launch::deferred, async_work) };
    
    cout << "Just after task() call." << endl;
    
    cout << result.get() << endl;
  }
  
  return 0;
}
