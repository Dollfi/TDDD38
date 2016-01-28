#include <iostream>
using namespace std;

int main()
{
    int x {};
    int y {3};
    int z {3.2}; 

    short a {y};
    short b {12};

    auto d = 4.3;

    int const *  i_ptr { new int{6} };
    cout << *i_ptr << endl;
    *i_ptr = 5; 		

    delete i_ptr;
    i_ptr = new int{5}; 

    return 0;
}
