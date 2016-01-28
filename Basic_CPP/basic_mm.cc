#include <iostream>
using namespace std;

int main()
{
    // Declaring a function taking a pointer to function (returning int, taking no arguments) as argument and
    // returning int
    int var (int());
    cout << var << endl;  // Will print 1 (function name decays into function pointer, which converts to bool)
}
