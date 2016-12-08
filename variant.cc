#include <variant>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Func
{
    void operator()(int i) const {
        cout << i;
    }
    void operator()(double d) const {
        cout << d;
    }

    void operator()(long l) const {
        cout << l;
    }

};

int main()
{
    variant<int, long, double, string> v;
    v = "hello";
    cout << v.index() << '\n';
    cout << get<string>(v) << '\n';
    // throws std::bad_variant_access
    // cout << get<int>(v) << '\n';
    v = 54;
    if ( auto val = get_if<int>(&v) )
    {
        cout << " int " << *val << endl;
    } 

    vector<variant<int, long, double>> vals {2,3,5l,3.4,2.3,34l};

    for ( auto && val : vals )
    {
        visit([](auto && v){cout << v;}, val);
        cout << endl;
        visit(Func{}, val);
    }
}

