#include <iostream>
#include <iomanip>

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <array>

#include <random>
#include <chrono>

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <new>

using namespace std;
using namespace std::chrono;
using arr_t = array<int,1000>;
const int N = 100000;
const int R = 1000;

void rw_sync(int i, arr_t& a, shared_mutex& shm, array<mutex,12>& m)
{
  random_device rdev;
  mt19937 rnd(rdev());

  for ( int n{}; n < N; ++n )
  {
    if ( rnd() % R == 0 ) // write
    {
      shm.lock();
      fill(begin(a),end(a),rnd());
      shm.unlock();
    }
    else // check
    {
      shm.lock();
      if ( ! all_of(begin(a),end(a),[&a](int i){return i == a.at(0);}) )
        cerr << "INCONSISTENCYT" << endl;
      else
        cout << "COOL" << endl;
      shm.unlock();
    }
  }
}

void rw_shared_lock(int i, arr_t& a, shared_mutex& shm, array<mutex,12>& m)
{
  random_device rdev;
  mt19937 rnd(rdev());

  for ( int n{}; n < N; ++n )
  {
    if ( rnd() % R == 0 ) // write
    {
      shm.lock();
      fill(begin(a),end(a),rnd());
      shm.unlock();
    }
    else // check
    {
      shm.lock_shared();
      if ( ! all_of(begin(a),end(a),[&a](int i){return i == a.at(0);}) )
        cerr << "INCONSISTENCYT" << endl;
      else
        cout << "COOL" << endl;
      shm.unlock_shared();
    }
  }
}

void rw_per_thread(int i, arr_t& a, shared_mutex& shm, array<mutex,12>& m)
{
  random_device rdev;
  mt19937 rnd(rdev());

  for ( int n{}; n < N; ++n )
  {
    if ( rnd() % R == 0 ) // write
    {
      for ( unsigned k{}; k < m.size(); k+=1 )
        m.at(k).lock();
      
      fill(begin(a),end(a),rnd());
      
//      for ( auto& l : m )
//        l.unlock();
      for ( unsigned k{}; k < m.size(); k+=1 )
        m.at(k).unlock();
    }
    else // check
    {
      m.at(i).lock();
      if ( ! all_of(begin(a),end(a),[&a](int j){return j == a.at(0);}) )
        cerr << "INCONSISTENCYT" << endl;
      else
        cout << "COOL" << endl;
      m.at(i).unlock();
    }
  }
}

int main()
{
  /*alignas(std::hardware_destructive_interference_size)*/ array<mutex,12> m;
  arr_t a;
  shared_mutex shm;
 
  fill(begin(a),end(a),0);

  {
    array<thread,12> t;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    
    int i{0};
    for ( auto& th : t )
    {
      th = thread(rw_sync, i++, ref(a), ref(shm), ref(m));
    }
  
    for ( auto& th : t )
      th.join();
    
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    
    cerr << "Execution time full sync "
         << duration_cast<milliseconds>(stop - start).count()
         << " ms" << endl;
  }

  {
    array<thread,12> t;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    
    int i{0};
    for ( auto& th : t ) 
      th = thread(rw_shared_lock, i++, ref(a), ref(shm), ref(m));
  
    for ( auto& th : t )
      th.join();
    
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    
    cerr << "Execution time shared "
         << duration_cast<milliseconds>(stop - start).count()
         << " ms" << endl;
  }

  {
    array<thread,12> t;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    
    int i{0};
    for ( auto& th : t ) 
      th = thread(rw_per_thread, i++, ref(a), ref(shm), ref(m));
  
    for ( auto& th : t )
      th.join();
    
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    
    cerr << "Execution time local "
         << duration_cast<milliseconds>(stop - start).count()
         << " ms" << endl;
  }
  
  return 0;
}
