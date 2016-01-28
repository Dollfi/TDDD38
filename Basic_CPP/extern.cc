#include <iostream>
#include "definition.cc"
int main()
{
    // has to be the same type as in definition.cc, cannot remove const!
    extern int const var;
    std::cout << var;
}
