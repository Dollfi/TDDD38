// An example on using (and defining) concepts according to the concept TS that will be available in the future (probably 2020). It is possible to use in gcc (version>=6.1) with flag -fconcepts
// https://github.com/mmha/bibi has an implementation of many good concepts that you can use

#include <iterator>
#include <set>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

// old way of handling this
namespace {
    template <typename Container, typename ValT = typename Container::value_type>
    auto order_impl(Container & c, std::random_access_iterator_tag)
      -> decltype(declval<ValT>() < declval<ValT>(), void())
    {
        sort(begin(c), end(c));
    }

    template <typename Container>
    void order_impl(Container & c, std::forward_iterator_tag)
    {
        c.sort();
    }
}

template <typename Container, typename It = typename Container::iterator>
void order(Container & c)
{
    order_impl(c, typename iterator_traits<It>::iterator_category {});
}

// A simple concept that checks if there is a less-than operator for type T and that the result of the operation is (convertible to) bool
template <typename T>
concept bool LessThanComparable=
requires(T const & a, T const & b)
{
    { a < b } -> bool;
};

// Some of the requirements on random-access iterators
template <typename RandomIt>
concept bool RandomAccessIterator=
requires(RandomIt  & it, RandomIt const & it2)
{
    { *it };               // possible to dereference
    { ++it } -> RandomIt;  // step returns a RandomIt
    { it + 2 } -> RandomIt;// can add
    { it < it2 } -> bool;  // can compare two iterators of type RandomIt
};

// A container that can be sorted with std::sort needs random-access iterators (begin(c) returns a value that fulfill RandomAccessIterator) and a value of the inner type value_type is LessThanComparable
template <typename Container>
concept bool SortableContainer =
requires(Container const & a)
{
    { begin(a) } -> RandomAccessIterator;
    { typename Container::value_type {} } -> LessThanComparable;
    // or
    //{ *begin(a) } -> LessThanComparable;
};

// used if the container has a member function sort
template <typename Container>
concept bool ContainerWithMemberSort =
requires(Container & c)
{
    { c.sort() };
    { *begin(c) } -> LessThanComparable;
};

// Three ways of using concepts:
// 1: add a requires-clause to the template
/* template <typename Container>
requires SortableContainer<Container>
void sort(Container & c){...}
*/
// 2: change typename to name of concept
/*template <SortableContainer Container>
void sort(Container & c) {...}
*/
// 3: Just use the concept as a type:
void sort(SortableContainer & c)
{
    sort(begin(c), end(c));
}

void sort(ContainerWithMemberSort & c)
{
    c.sort();
}

struct A
{};

int main()
{
    vector<int> v {2,3,5,7,8,4,7};
    sort(v);

    list<int> l{3,4,5,7,8};
    sort(l);
    // Faulty, no random-access iterators
    //set<int> s {3,4,5,78,8};
    //sort(s);
    // Faulty, A not LessThanComparable
    //vector<A> va (20);
    //sort(va);
}
