#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>

class Complex
{
public:
  Complex(double r, double i) : r{r}, i{i} {};
  Complex() : Complex{0.0, 0.0} {}                  // delegating
  Complex(std::string const&) : Complex{0.0, 0.0} {}
  Complex(Complex const&) = default;                // copy and "default"
  explicit Complex(double r) : Complex{r, 0.0} {};  // why explicit?

  double abs() const;                               // distance from origo
  double real() const { return r; }
  double imag() const { return i; }

  Complex& operator=(Complex const& rhs) = default; // default

  Complex& operator+=(Complex const& rhs)
  {
    r += rhs.r;        // Complex z = *this + rhs;
    i += rhs.i;        // *this = z;
    return *this;
  }

  Complex operator+(Complex const& rhs) const
  {
    Complex z{*this};  // Recursion danger!
    z += rhs;
    return z; // return value optimization! (copy elision)
  }

  // What's the difference and why would you not implement either?
  Complex& operator++();
  Complex operator++(int);

  // Member or non-member? Why friend?
  Complex& operator+=(double rhs);
  // Type conversion
  explicit operator double() { return abs(); }

  bool operator<(Complex const& rhs);

  friend std::ostream& operator<<(std::ostream& os, Complex const& rhs);
  friend std::istream& operator>>(std::istream& is, Complex& rhs);

private:
  double r;
  double i;
};

// User-defined literal, makes 3.4_i into Complex{0, 3.4}
Complex operator "" _i(long double d);

Complex operator+(double lhs, Complex const& rhs);
Complex operator+(Complex const& lhs, double rhs);

#endif
