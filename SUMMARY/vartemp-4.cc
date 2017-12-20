#include "headers.h"
UNS
int foo(int &&, char &)
{
    return 4;
}

template <typename Ret, typename Fun, typename ...Args>
Ret call(Fun f, Args... &&args)
{
    return f(forward<Args>(args)...);
}

int main()
{
    int a;
    char c;
    cout << call<int>(foo, 4, c);
}

