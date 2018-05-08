#include <iostream>
#include <mutex>
#include <vector>
#include <utility>
#include <memory>

using namespace std;

class Foo
{
public:
  void foo() { cerr << "Foo" << endl; }
  void bar() { cerr << "Bar" << endl; }
};

template <typename Obj>
class Synchronized
{
private:
  class Locker
  {
  public:
    Locker(Obj* o, std::mutex& m) : m{m}, o{o}
    {
      m.lock();
      cerr << "Lock" << endl;
    }
    
    ~Locker()
    {
      cerr << "UnLock" << endl;
      m.unlock();
    }

    Locker(Locker const&) = default;
    Locker& operator=(Locker const&) = delete;

    Obj* operator->() { return o; }
    
  private:
    std::mutex& m;
    Obj* o;
  };
  
public:
  template <typename ... Args>
  Synchronized(Args && ... args) : m{}, o{ make_unique<Obj>(std::forward<Args>(args)...) } {}

  Synchronized(Synchronized const&) = delete;
  Synchronized& operator=(Synchronized const&) = delete;
  Synchronized(Synchronized &&) = delete;
  Synchronized& operator=(Synchronized &&) = delete;
  
  Locker operator->()
  {
    return Locker{o.get(), m};
  };
  
private:
  std::mutex m;
  unique_ptr<Obj> o;
};

int main()
{
  Synchronized<Foo> s{};
  
  s->foo(); // will ~Locker() always run *after* foo() completes? Yes. pp 252 4
  s->bar();

  Synchronized<std::vector<int>> v(10,1);

  cout << v->size() << endl;
  return 0;
}
