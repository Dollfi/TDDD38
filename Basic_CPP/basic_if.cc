// What will be printed? Why?

#include <iostream>

int main(int argc, char argv[])
{
  int x {2};
  // assignment followed by lvalue-to-rvalue
  // conversion and boolean conversion
  if ( x = 0 )
    std::cout << "x is zero\n";
  else
    std::cout << "Value of x: " << x << "\n";
  return 0;
}
