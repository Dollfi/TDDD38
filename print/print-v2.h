// A sample to show variadic templates,
// template metaprogramming and expression SFINAE
#pragma once

template <typename ...Args>
void print(Args...);

void print();

#include "print-v2.tcc"
