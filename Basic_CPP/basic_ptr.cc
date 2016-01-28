#include <iostream>
#include <cstring>
#include <array>
using namespace std;


int main()
{
    int a {4};
    int * ip { &a };
    cout << "a:    " << a << endl;
    cout << "ip:   " << ip << endl;
    cout << "*ip:  " <<*ip << endl;
    
    cout << endl;
    char const *str { "Anna" };
    cout << "str:  " << str << endl;
    cout << "*str: " <<*str << endl;
    cout << endl;
    
}
