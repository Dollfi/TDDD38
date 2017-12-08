/* LatexBeginSetup */
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>  // <<-- iota
#include <algorithm>
#include <thread>
//#include <execution> // <<-- execution policies

using namespace std;

int main()
{
  vector<int> v(70);
  iota(begin(v), end(v), 1);
/* LatexEndSetup */
  
/* LatexBeginSeq */
  for_each(/*execution::seq,*/ begin(v), end(v), [](int i) {
      cout << setw(i) << 's' << endl;
    });
/* LatexEndSeq */
  
/* LatexBeginThread */
  const auto thread_count{4};
  const auto size = v.size();
  const auto chunk_size{ size/thread_count };
  const auto remainder{ size%thread_count };

  vector<thread> t;
  auto b{ begin(v) };
  for ( unsigned i{}; i < thread_count; ++i)
  {
    auto e{ next(b, chunk_size + (i < remainder)) };
    t.emplace_back([](auto start, auto end){
        for (auto i{start}; i < end; ++i)
          cout << setw(*i) << '\\' << endl;
      }, b, e);
    b = e;
  }

  for ( auto && i : t )
    i.join();
/* LatexEndThread */

/* LatexBeginPar */
  for_each(/*execution::par,*/ begin(v), end(v), [](int i) {
      cout << setw(i) << 'p' << endl;
    });
/* LatexEndPar */

  return 0;
}
