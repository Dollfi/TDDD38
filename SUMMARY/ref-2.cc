#include "headers.h"
using namespace std;
struct T{};
void fun(T const &){
    cout << 1;
}

void fun(T &&){
    cout << 3;
}

int main(){
    T a;
    T const c {};
    fun(T{});
    fun(a);
    fun(c);
}
