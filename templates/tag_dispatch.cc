// Tag dispatching - using an empty class type to use as a
// tag so that we are able to select the correct implementation
// at compile time. See the algorithms taking different types of
// iterators for a more concrete example (such as std::distance)

#include <iostream>
using namespace std;

struct tag1{};
struct tag2{};

struct A
{
    using tag_type = tag1;
};

struct B
{
    using tag_type = tag2;
};

// an anonymous namespace hides the content so that the declarations
// are only available in this file
namespace {
    template <typename T>
    void do_impl(T & t, tag1)
        {
            cout << "Tag1\n";
        }

    template <typename T>
    void do_impl(T & t, tag2)
        {
            cout << "Tag<F2>\n";
        }
}
template <typename T>
void do_stuff(T & t)
{
    using tag_type = typename T::tag_type;
    // pass an object of the tag type to select the correct overload
    do_impl(t, tag_type{});
}


int main()
{
    A a;
    B b;
    do_stuff(a);
    do_stuff(b);
}
