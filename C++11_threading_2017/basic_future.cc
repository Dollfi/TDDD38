#include <iostream>

#include <thread>
#include <future>

using namespace std;

void receptionist(promise<void> say_welcome,
                  future<string> errand,
                  promise<void> reply)
{
  cout << "R: Welcome, how can I help you?" << endl;
  say_welcome.set_value();
  
  string name = errand.get();
  cout << "R: Please enter, " << name << " is expecting you." << endl;
  reply.set_value();
}

void visitor(future<void> get_welcome,
             promise<string> tell_errand,
             future<void> get_reply)
{
  string name{"Mr X"};
  get_welcome.wait();
  cout << "V: Hi, I'm here to meet " << name << endl;
  tell_errand.set_value(name);
  get_reply.wait();
  cout << "V: Thank you" << endl;
}

int main()
{
  promise<void> say_welcome;
  promise<string> say_errand;
  promise<void> reply;

  // You have to get the futures before you move the promise
  future<void> get_welcome = say_welcome.get_future();
  future<string> get_errand = say_errand.get_future();
  future<void> get_reply = reply.get_future();

  // You have to move promises and futures into the threads
  thread r(receptionist, move(say_welcome), move(get_errand), move(reply));
  thread v(visitor, move(get_welcome), move(say_errand), move(get_reply));

  // Wait for both threads to finish before continuing
  r.join();
  v.join();

  cout << "Main done" << endl;
  
  return 0;
}
