#include <iostream>
#include <sstream>

#include "complex.h"

using namespace std;

int main()
{
  // We have three complex numbers:
  Complex const u{1, 5}; // 1+5i
  Complex v{2, 4};
  Complex w{3, 3};
  Complex z{}; // 0+0i

  // We want to calculate the expression:
  //  z = u + v + w;
  
  // Which approach is better?
  // Member function or free function?
  // Can we let the compiler mechanically
  // convert "u+v" to:
  //  "(u)+(v)" to "(u).add(v)"?
  // or to
  //  "add(u,v)"?

  // Yes! The compiler tries almost exactly
  // those conversions in this order!
  // But the name the compiler will convert
  // to is "operator+", first the keyword
  // "operator" and then the operator symbol
  // that was mechanically replaced.

  // We implement "operator+" and can write:
  Complex t3 = u + v;
  z = t3 + w;
  // or even:
  z = u + v + w;

  // How do we write a literal complex?
  Complex i{ 1.0_i };
  // We now have a user-defined literal "_i"

  // What if the imaginary part is zero?
  Complex r{ 1.0 }; // 1.0

  // What if we use operator+ with doubles?
  z = 1.0 + i; // Member operator or not?
  z = i + 1.0; // Member operator or not?

  // What if constructor or operator double
  // is explicit/non-explicit in above code?

  // How can we print a complex number to an
  // ostream, for example cout?
  cout << z; // Output operator

  // Remember mechanical conversions to:
  // (1) cout.operator<<(z)
  // (2) operator<<(cout, z)
  // We have:
  // (1) Does not exist, can not be created.
  // (2) We can implement this!

  // What is the result of (cout << z)?
  cout << z << endl;

#if 0
  // Broken up in two lines!
  auto r0 = cout << z;
  auto r1 = r0 << endl;

  // Does not exist!
  // auto r2 = cout.operator<<(z);

  // Can be created by us!
  auto r2 = operator<<(cout, z);

  // Will work if r2 is ostream& !
  auto r3 = r2.operator<<(endl);

  // Not tried, found above first!
  // auto r3 = operator<<(r2, endl);

  // Equivalent code (do not write)!
  operator<<(cout, z).operator<<(endl);
#endif

  // What will happen?
  static_cast<double>(z);
//  static_cast<string>(z);
//  to_string(z);

  // How to transform from string
  // (user input?) to complex?
  string strval{"12+34i"};
  istringstream iss{strval};
  Complex val;
  iss >> val;
  
  ostringstream oss;
  oss << val;

  cout << oss.str() << "=="
       << strval << endl;

  return 0;
}
