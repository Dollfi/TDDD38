/* LatexBeginSetup */
#include <iostream>
#include <vector>
#include <chrono>

#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono_literals;

int main()
{
  vector<string> v
  {
      "This line is not written in gibberish",
      "We want every line to be perfectly readable",
      "The quick brown fox jumps over lazy dog",
      "Lorem ipsum dolor sit amet"
  };
  mutex cout_mutex;
/* LatexEndSetup */
  
/* LatexBeginPrinter */
  auto printer = [&](int i)
    {
      string const& str = v.at(i);
      
      for (int j{}; j < 100; ++j)
      {
//        lock_guard<mutex> lock(cout_mutex);
        for (unsigned l{}; l < str.size(); ++l)
        {
          cout << str.at(l);
          this_thread::sleep_for(1us);
        }
        cout << endl;
      }
    };
/* LatexEndPrinter */

/* LatexBeginPool */
  vector<thread> pool;
  for ( unsigned i{}; i < v.size(); ++i )
  {
    pool.emplace_back(printer, i);
  }

  for ( auto && t : pool )
  {
    t.join();
  }
  cout << "Main done" << endl;

  return 0;
}
/* LatexEndPool */
