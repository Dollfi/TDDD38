#include <iostream>
using std::cout;

// can remove argument name to get rid of warnings
void fun(float, int i)
{
    cout << "Running float\n";
}

void fun(double d, int i)
{
    cout << "Running double\n";
}
void fun(short s, int i)
{
    cout << "Running short\n";
}
void fun(int const & i)
{
    cout << "Running int ref\n";
}

void fun(int const * ip)
{
    cout << "Running int ptr\n";
}

enum Color { Red, Green, Blue };

enum class New_Color : int { Red, Green, Blue };

int main()
{
    short s;
    double d;
    float f;
    // scoped enumarations aren't implicitly converted
    int i {static_cast<int>(New_Color::Red)};
    fun(f,i);
    fun(d,2);
    fun(s,i);

    fun(2,3); // Error: ambigous overload resolution

    // no way of giving a short literal
    fun(static_cast<short>(2),2);
    fun(2.f, 2);

    // boolean conversion (§4.12)
    if ( i )
    {
        cout << "i is true!\n";
    }
    
    int * ip;
    int const * cip;
    int const volatile * cvip;

    fun(ip);
    fun(cip);
    fun(nullptr);
    // const cast to remove qualifications (§5.2.11)
    fun(const_cast<int const*>(cvip));

}
