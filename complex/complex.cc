#include <iostream>
#include <sstream>

#include "complex.h"

using namespace std;

Complex & Complex::operator++()
{
    // increase abs?
    return *this;
}

Complex Complex::operator++(int)
{
    Complex tmp{*this};
    this->operator++();
    return tmp;
}

bool Complex::operator<(Complex const& rhs)
{
    return abs() < rhs.abs();
}

// User-defined literal
Complex operator "" _i(long double d)
{
  return Complex{0.0, static_cast<double>(d)};
}

double Complex::abs() const
{
    return ::sqrt(r*r + i*i);
}

// Stream output operator
ostream& operator<<(ostream& os, Complex const& rhs)
{
  os << rhs.r;
  if ( rhs.i > 0.0 )
  {
      os << '+';
  }
  if ( rhs.i != 0.0 )
  {
      os << rhs.i << 'i';
  }
  return os;
}

// Stream input operator
istream& operator>>(istream& is, Complex& rhs)
{
  is >> rhs.r >> rhs.i;
  is.ignore(); // i
  return is;
}

Complex operator+(double lhs, Complex const& rhs)
{
  return Complex{lhs} += rhs;
}

Complex operator+(Complex const& lhs, double rhs)
{
  return rhs + lhs;
}


