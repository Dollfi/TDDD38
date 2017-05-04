#include <iostream>

#include <thread>
#include <chrono> // time constants

using namespace std;
using namespace std::chrono_literals; // time constants

void receptionist()
{
  cout << "R: Welcome, how can I help you?" << endl;  
  cout << "R: Please enter, he's expecting you." << endl;
}

class Visitor
{
public:
  void operator()() const
  {
    cout << "V: Hi, I'm here to meet Mr X" << endl;
    cout << "V: Thank you" << endl;
  }
};


int main()
{
  thread r(receptionist);
  thread v(Visitor{});
  thread f([](){ cout << "F: Hi!" << endl; });

  v.join();   // will wait for thread v to complete
  r.detach(); // makes you responsible ...
//  f.detach(); // terminate due to f not join'ed or detach'ed

  cout << "Main sleep" << endl;

  this_thread::sleep_for(2s); // pause main thread for 2 seconds  

  cout << "Main done" << endl;
  
  return 0;
}
