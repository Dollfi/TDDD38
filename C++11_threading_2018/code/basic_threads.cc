/* LatexBeginInclude */
#include <iostream>
#include <thread>
#include <chrono> // time constants

using namespace std;
using namespace std::chrono_literals; // time constants
/* LatexEndInclude */

/* LatexBeginFunc */
void receptionist(string name)
{
  cout << name << ": Welcome, how can I help you?" << endl;  
  cout << name << ": Please enter, he's expecting you." << endl;
}
/* LatexEndFunc */

/* LatexBeginClass */
class Visitor
{
public:
  Visitor(string const& n) : name{n} {}
  void operator()() const
  {
    cout << name << ": Hi, I'm here to meet Mr X" << endl;
    cout << name << ": Thank you" << endl;
  }
private:
  string name;
};
/* LatexEndClass */

/* LatexBeginMain */
int main()
{
  thread r{receptionist, "R"s};
  thread v{Visitor{"V"s}};
  thread f{[](){ cout << "F: Hi!" << endl; }};

  v.join();   // will wait for thread v to complete
  r.detach(); // makes you responsible ...
//  f.detach(); // terminate due to f not join'ed or detach'ed

  cout << "Main sleep" << endl;
  this_thread::sleep_for(2s); // pause main thread for 2 seconds  
  cout << "Main done" << endl;
}
/* LatexEndMain */
