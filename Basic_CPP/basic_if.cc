// What will be printed? Why?

#include <iostream>
using std::cout;

int main()
{
    int x {2};
    if ( x == 0 )
        cout << "x is zero\n";
    else
        cout << "Value of x: " << x << std::endl;
    return 0;
}
