// A sample to show variadic templates,
// template metaprogramming and expression SFINAE
#pragma once
#include <iostream>
#include <string>
#include <vector>

void print();

template <typename ...Args>
void print(char, Args...);

template <typename ...Args>
void print(std::string const &, Args...);

template <typename ...Args>
void print(char const *, Args...);

template <typename Container, typename ...Args>
auto print(Container const & c, Args...)
  -> decltype(begin(c), c.size(), void());

template <typename T, typename ...Args>
auto print(T const & first, Args...)
  -> decltype(std::cout << first, void());

#include "print.tcc"
