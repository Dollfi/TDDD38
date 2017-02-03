#include <iostream>

#include <thread>
#include <mutex>

using namespace std;

void receptionist(mutex& cout_mutex)
{
  cout_mutex.lock();
  cout << "R: Welcome, how can I help you?" << endl;  
  cout_mutex.unlock();
    
  this_thread::yield(); // let some other thread run (request thread switch)

  lock_guard<mutex> lock(cout_mutex); // destructor auto unlock
  cout << "R: Please enter, he's expecting you." << endl;
}

void visitor(mutex& cout_mutex)
{
  cout_mutex.lock();
  cout << "V: Hi, I'm here to meet Mr X" << endl;
  cout_mutex.unlock();
    
  this_thread::yield(); // let other thread run
  
  lock_guard<mutex> lock(cout_mutex); // destructor auto unlock
  cout << "V: Thank you" << endl;
}

int main()
{
  mutex cout_mutex;

  // references parameters have to be specified explicitly, pass a reference_wrapper
  thread r(receptionist, ref(cout_mutex));
  thread v(visitor, ref(cout_mutex));

  r.join();
  v.join();

  cout << "Main done" << endl;
  
  return 0;
}
