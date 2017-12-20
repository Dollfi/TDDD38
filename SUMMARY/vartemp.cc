#include "headers.h"
UNS
int foo(int, char)
{
    return 4;
}

template <typename Ret, typename Fun, typename ...Args>
Ret call(Fun f, Args... args)
{
    return f(args...);
}

int main()
{
    int a;
    char c;
    cout << call(foo, a, c);
}

