#include <iostream>
#include <cstring>
#include <array>
using namespace std;


// The 5 is not needed, the compiler just sees int*
void print(int arr[5], int size)
{
    for ( ; size ; --size )
    {
        // using C pointer arithmitics...
        cout << *arr++ << ' ';
    }
}

// By using std::array, we keep track of the size! (and get a compiler error if mismatch)
void print(array<int, 5> const & arr)
{
    for ( auto i : arr )
    {
        cout << i << ' ';
    }
}


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
    
    int arr[5] {1,2,3};
    // oops, calling with wrong size...
    print(arr, 10); 
    cout << endl;

    array<int, 5> arr2 {1, 2, 3};    
    print(arr2);
}
