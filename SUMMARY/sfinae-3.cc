#include "headers.h"
using namespace std;
template <typename T>
enable_if_t<is_integral<decay_t<T>>::value>
foo(T &&) {
    cout << 1;
}

int main()
{
    int i{};
    foo(i);
}
