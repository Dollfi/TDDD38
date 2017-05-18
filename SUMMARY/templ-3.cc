#include "headers.h"
using namespace std;
template <typename T>
void foo(T &&) {
    cout << __PRETTY_FUNCTION__ <<'\n';
}

void foo(int const &) {
    cout << 2;
}

int main() {
    int a;
    int const b{};
    foo(a);
    foo(3);
    foo(b);
}
