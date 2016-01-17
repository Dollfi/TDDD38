#include <iostream>
using namespace std;
int main()
{
  int x {};
  int y {3};
  int z {3.2};  // Narrowing conversion (error §8.5.4/3)

  short a {y}; // Narrowing
  short b {12}; // Ok?

  auto d = 4.3;
  
  int const *  i_ptr { new int{6} };
  cout << *i_ptr << endl;  // OK
  *i_ptr = 5; 		   // ERROR
  
  delete i_ptr;
  i_ptr = new int{5}; 

  // memory leak!
  return 0;
}
