// std::variant stores one value of any of a specific set of types.
// Internally it uses an union as storage and an index to keep track
// of the current type. variant<t1,t2,t3> has index 0 for t1 and 
// index 2 for t3
#include <vector>
#include <variant>
#include <iostream>
using namespace std;

// Some classes to use later
//
// abstract base class. Uses NVI (non-virtual interface)
class Updatable
{
public:
     void update(double dt)
     {
         do_update(dt);
     }
private:
     virtual void do_update(double) = 0;
};

class A : public Updatable
{
void do_update(double) override 
{
    cout << "A::update\n";
}
};

class B: public Updatable
{
    void do_update(double) override {
    cout << "B::update\n";
    }
};

class C
{
    public:
        void do_c_stuff() const {
            cout << "C::do_stuff\n";
        }
};


// used by visit later
struct Vistior
{
    void operator()(Updatable & u)
    {
        u.update(2.2);
    }
    void operator()(C const & c)
    {
        c.do_c_stuff();
    }
};

// another funciton object type used by visit
struct Printer
{
    // default behavior
    template <typename T>
        void operator()(T && t)
        {
            cout << t << endl;
        }
    // specific behavior for double
    void operator()(double d)
    {
        cout << "Double: " << d << endl;
    }
};

int main()
{
    variant<int, char, double, string> v1 {4.4};
    cout << get<double>(v1) << endl;
    if ( auto p = get_if<int>(&v1) )
    {
        cout << "int\n";
    }
    else
    {
        cout << "Not int\n";
    }
    v1 = "hejsan"s;
    v1 = 2.2;
    vector<variant<int, char, double>> vals { 3, 3.3, 'a', 5 };
    for ( auto && v : vals )
    {
        visit(Printer{}, v);
        //visit([](auto const & v){cout << v << endl;},
        //        v);
    }

    vector<variant<A,B,C>> entities { A{}, C{}, A{}, B{} };

    for ( auto && v : entities )
    {
        // Visitor has to have overloads for operator() that can
        // accept all possible types in v. 
        visit(Vistior{}, v);
    }

}
