#include <iostream>

#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::chrono_literals;

mutex cout_mutex;

void worker(mt19937& die,
            int& done,
            mutex& m,
            condition_variable& change)
{
  uniform_int_distribution<int> roll(1,6);

  // just pretend to do some work...
  for ( int i{}; i < 100; ++i )
  {
    int n{roll(die)};
    for (int j{}; j < n; ++j)
      this_thread::sleep_for(1ms);
    
    lock_guard<mutex> lock(cout_mutex);
    cout << this_thread::get_id()
         << " iteration " << i
         << " slept for " << n << endl;
  }
  // message main thread that this thread is done
  unique_lock<mutex> done_mutex{m};
  --done;
  change.notify_one();
}

int main()
{
  const int N{10};
  int done{N};
  random_device rdev;
  mt19937 die(rdev());

  mutex base_mutex{};
  condition_variable cond_change{};

  for (int i{}; i < N; ++i)
  {
    // if we do not need to keep track of threads we
    // can create and detach threads immediately
    thread(worker,
           ref(die),
           ref(done),
           ref(base_mutex),
           ref(cond_change)).detach();
  }

  // conditions require a std::unique_lock
  unique_lock<mutex> done_mutex{base_mutex};
  while ( done > 0 )
  {
    cout_mutex.lock();
    cout << "Main: still threads running!" << endl;
    cout_mutex.unlock();
    
    // we are holding the done_mutex and need to wait for another
    // thread to update the variable, but that thread can not lock the
    // done_mutex while we're holding it... condition_variables solve
    // this problem efficiently
    cond_change.wait(done_mutex);    
  }
  done_mutex.unlock();

  // an option that would achieve the same as the loop above is to
  // keep track of all started threads in a vector and join them
  
  cout << "Main done" << endl;
  
  return 0;
}
