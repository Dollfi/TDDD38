#include <iostream>

#include <thread>
#include <mutex>

using namespace std;

void deadlock(mutex& x, mutex& y)
{
  auto id = this_thread::get_id();
  
  lock_guard<mutex> lgx{x};
  cout << id << ": Have lock " << &x << endl;
  
  this_thread::yield(); // try to get bad luck here
  
  lock_guard<mutex> lgy{y};
  cout << id << ": Have lock " << &y << endl;

  cout << id << ": Doing stuff requiring both locks" << endl;
}

void no_deadlock(mutex& x, mutex& y)
{
  auto id = this_thread::get_id();

  // C++11, take locks
  lock(x, y);
  // And arrange for automatic unlocking
  lock_guard<mutex> lgx{x, adopt_lock};
  lock_guard<mutex> lgy{y, adopt_lock};

  // C++17
  // scoped_lock lock{x, y};
  cout << id << ": Have lock " << &x << " and " << &y << endl;
  
  cout << id << ": Doing stuff requiring both locks" << endl;
}

int main()
{
  mutex A;
  mutex B;

  // references parameters have to be specified explicitly
  thread AB{deadlock, ref(A), ref(B)};
  thread BA{deadlock, ref(B), ref(A)};

  AB.join();
  BA.join();

  cout << "Main done" << endl;
  
  return 0;
}
