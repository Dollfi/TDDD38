#include "headers.h"
using namespace std;
template <typename T>
enable_if_t<is_integral<T>::value>
foo(T &&) {
    cout << 1;
}

int main()
{
    foo(2);
}
