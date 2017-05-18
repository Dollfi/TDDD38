#include "headers.h"
using namespace std;
void fun(int const &){
    cout << 1;
}

void fun(int &){
    cout << 2;
}

void fun(int &&){
    cout << 3;
}

int main(){
    int a;
    int const c {};
    fun(23);
    fun(a);
    fun(c);
}
