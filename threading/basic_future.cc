#include <iostream>

#include <thread>
#include <future>
#include <chrono>
using namespace std;

void receptionist(promise<void> say_welcome, future<string> errand, promise<void> done)
{
  done.set_value_at_thread_exit();
  cout << "R: Welcome, how can I help you?" << endl;
  say_welcome.set_value();
  
  string name = errand.get();
  cout << "R: Please enter, " << name << " is expecting you." << endl;
}

void visitor(future<void> get_welcome, promise<string> errand, future<void> wait)
{
  string name{"Mr X"};
  get_welcome.wait();
  cout << "V: Hi, I'm here to meet " << name << endl;
  errand.set_value(name);
  wait.wait();
  cout << "V: Thank you" << endl;
}

int main()
{
  promise<void> say_welcome;
  promise<string> say_errand;
  promise<void> wait_for_done;
  // You have to get the futures before you move the promise
  future<void> get_welcome = say_welcome.get_future();
  future<string> get_errand = say_errand.get_future();
  future<void> waiter = wait_for_done.get_future();
  // You have to move promises and futures into the threads
  thread r(receptionist, move(say_welcome), move(get_errand), move(wait_for_done));
  thread v(visitor, move(get_welcome), move(say_errand), move(waiter));

  // Wait for both threads to finish before continuing
  r.join();
  v.join();

  cout << "Main done" << endl;
  
  return 0;
}
