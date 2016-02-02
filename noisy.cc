// Simple class to show copy elision and (N)RVO ($12.8/31)
// also includes some const-problems and friend declarations
// compile with -fno-elide-constructors to remove elision
#include <iostream>
#include <string>
using namespace std;

class Noisy 
{
public:
  Noisy(string const & n) 
    : name{n}, id {++counter}
  {
    print_id();
    cout << "Created \"" << name << '"' << endl;
  }

  Noisy()
    : name {"default"}, id {++counter}
  {
    print_id();
    cout << "Default constructor called" << endl;
  }

  ~Noisy()
  {
    print_id();
    cout << "Destructor for \"" << name << "\" called" << endl;
  }

  Noisy(Noisy const & other)
    : name{ other.name }, id {++counter}
  {
    print_id();
    cout << '"' << name << "\" copied with copy constructor\n";
  }
  
  Noisy(Noisy && other) noexcept
  : name{ std::move(other.name) }, id { ++counter}
  {
    print_id();
    cout << '"' << name << "\" move constructed\n";
  }
  

  Noisy & operator=(Noisy const & rhs) &
  {
    print_id();
    cout << '"' << name << "\" gets value \"" 
	 << rhs.name << '"' << endl;
    name = rhs.name; 
    return *this;
  }
  Noisy & operator=(Noisy && rhs) &
  {
    print_id();
    cout << '"' << name << "\" gets value \"" 
	 << rhs.name << "\" (move)" << endl;
    name.swap(rhs.name); 
    rhs.name = "moved from";
    return *this;
  }

  void write() const
    {
      print_id();
      cout << name << endl;
    }
  
private:
  static int counter;
  std::string name;
  int id;

  void print_id() const
  {
    cout << "(" << id << ") ";
  }

  friend Noisy fun();
  friend class B;
  
};

class B
{
public:
  void fun(Noisy & n) {
    n.id=5;
  }
};
int Noisy::counter {};

Noisy fun()
{
  Noisy res {"tmp"};
  res.print_id();
  // do something to res
  return res;
}

int main()
{
  Noisy n1 {"Hi"};
  Noisy n2 {n1};
  Noisy n3 = std::move(n2);
  n2 = std::move(n1);
  Noisy n4 { fun() }; 
  B b;
  b.fun(n4);
  const Noisy n5 { n4};
  n5.write(); // write is called on a const object, write must be const-qualified
}
