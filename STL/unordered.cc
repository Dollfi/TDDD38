#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <map>
#include <unordered_set>
#include <functional>

using namespace std;

struct Foo
{
    Foo(int i): data{i} {}
    int data;
};

bool operator<(Foo const & lhs, Foo const & rhs)
{
    return lhs.data < rhs.data;
}

bool operator==(Foo const & l, Foo const & r)
{
    return l.data == r.data;
}

struct FooLess
{
    bool operator()(Foo const & l, Foo const & r) const
    {
        return l.data < r.data;
    }

};

// Specialize std::hash for Foo
namespace std
{
    template<>
    struct hash<Foo>
    {
        size_t operator()(Foo const &f) const
        {
            return f.data;
        }
    };
}
int main()
{
    unordered_set<Foo> us;
    us.insert(Foo{5});
    //copy(begin(s), end(s), ostream_iterator<int>{cout, " "});
    set<Foo> s; // requires operator< for Foo
    set<Foo, FooLess> sl; // pass our own function object type (good 
                          //  if we don't want an operator< )
    
    // also possible to pass a lambda by specifying a template type 
    // that matches
    auto comp = [](Foo const & l, Foo const & r)
    {
        return l.data < r.data;
    };
    set<Foo, decltype(comp)> sfl(comp);

    set<Foo, function<bool(Foo const &, Foo const &)>> sf(
            [](Foo const & l, Foo const & r){ return l.data < r.data; });
    sf.insert(Foo{3});
}
