#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <thread>
#include <iterator>
#include <future>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

using iter = vector<int>::iterator;

mutex cout_mutex;

class Wait_For_N
{
public:
  Wait_For_N(int n) : n{n}, count{0}, m{}, cv{} {}

  void wait()
  {
    unique_lock<mutex> lock(m);
    while ( count < n )
      cv.wait(lock);
    // lock auto released
  }

  void signal()
  {
    lock_guard<mutex> lock(m);
    ++count;
    cv.notify_one();
    // lock auto released
  }
  
private:
  const int n;
  int count;
  mutex m;
  condition_variable cv;
};

// thread function
void find_max(int chunk, iter s, iter e, pair<int,int>& max,
              mutex& m, // lock for shared max output param
              future<pair<int,int>> f, // wait for future even
              promise<pair<int,int>> p, // signal event
              Wait_For_N& wfn) // done count
{
  cout_mutex.lock();
  cout << chunk << ": ";
  copy(s, e, ostream_iterator<int>(cout, " "));
  cout << endl;
  cout_mutex.unlock();
  
  int chunk_max = *max_element(s,e); // bug!?

  m.lock();
  if ( chunk_max >= max.second )
  {
    this_thread::sleep_for(1ns);
    max = make_pair(chunk, chunk_max);
  }
  m.unlock();

  wfn.signal();
  
  auto r = f.get(); // get() only once!
  if ( chunk_max >= r.second )
    p.set_value(make_pair(chunk, chunk_max));
  else
    p.set_value(r);
}

int chunk_size(int i, int total, int count)
{
  return (total / count) + (total % count > i);
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    cerr << "Usage: " << argv[0] << " N THREAD_COUNT" << endl;
    return 1;
  }
  const int N = stoi(argv[1]);
  const int THREAD_COUNT = stoi(argv[2]);

  
  cout << thread::hardware_concurrency()
       << "hardware threads available." << endl;

  random_device rdev;
  mt19937 rnd(rdev());
  uniform_int_distribution<int> dist(1, N*THREAD_COUNT);

  /// create data vector
  vector<int> v( N*THREAD_COUNT );
//  iota(begin(v), end(v), 1);
  generate(begin(v), end(v), bind(dist,rnd));
  shuffle(begin(v), end(v), rnd);

  /// set up synchronization variables
  vector< promise< pair<int,int> > > pv( THREAD_COUNT + 1 );
  pair<int,int> max{-1,-1};
  mutex max_mutex;
  Wait_For_N all_done(THREAD_COUNT);

  /// message passing setup
  auto f = pv.at(0).get_future(); // get_future() must happen before move!!

  /// split work and start threads
  vector<thread> tv{};
  auto from = begin(v);
  for (int i{1}; i <= THREAD_COUNT; ++i)
  {
    auto to = from + N;    
    tv.push_back( thread( find_max, i, from, to, ref(max), // arguments
                          // synchronization variants (one is enough...)
                          ref(max_mutex), // lock for max
                          move( pv.at(i).get_future() ), // wait for next
                          move( pv.at(i-1) ), // signal previous
                          ref(all_done)
                    )
      );
    from = to;
  }

  /// Shared variable summary
  all_done.wait();  
  cout << "Global: Max value was " << max.second
       << " in chunk " << max.first << endl;

  /// Message passing summary
  pv.back().set_value(make_pair(-1, -1)); // signal thread N
  auto p = f.get();
  
  cout << "Message: Max value was " << p.second
       << " in chunk " << p.first << endl;


  
  // wait for threads to complete
  for ( thread& t : tv )
  {
    t.join();
  }
  
  return 0;
}
