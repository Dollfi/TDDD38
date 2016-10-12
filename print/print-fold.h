#pragma once

void print();

template <typename T, typename ...Args>
void print(T && t, Args ...args);

#include "print-fold.tcc"
