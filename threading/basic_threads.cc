#include <iostream>
#include <thread>
#include <chrono> // time constants

using namespace std;

void receptionist()
{
  cout << "R: Welcome, how can I help you?\n" << endl;
  cout << "R: Please enter, he's expecting you." << endl;
}

void visitor()
{
  cout << "V: Hi, I'm here to meet Mr X" << endl;
  cout << "V: Thank you" << endl;
}

int main()
{
  thread r(receptionist);
  thread v(visitor);

  // You have to call either 'detach' or 'join' on all threads
  r.detach();
  v.join();

  cout << "Main sleep" << endl;
  
  this_thread::sleep_for(2s); // pause main thread for 2 seconds
  
  cout << "Main done" << endl;
  
  return 0;
}
