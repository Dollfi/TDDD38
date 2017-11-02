/*
 * An implementation of selection sort using STL algorithms
 * Accepts a pair of iterators spanning the range of values to
 * be sorted.
 * Has one overload taking a binary predicate function and one
 * that uses operator<
 */

#include <vector>
#include <algorithm>
#include <functional>

template <typename Iterator, typename Comp>
void sort(Iterator first, Iterator last, Comp comp)
{
    for ( auto current {first}; current != last; ++current )
    {
        auto min = std::min_element(current, last, comp);
        std::iter_swap(current, min);
    }
}

template <typename Iterator>
void sort(Iterator first, Iterator last)
{
    // std::less{} gives an object of type std::less<void>, which
    // has a templated function call operator (deferres type deduction
    // to the call site)
    ::sort(first, last, std::less{});
    // Could also ask the iterator for the value type of the
    // data structure using iterator_traits
    // ::sort(first, last, 
    //          std::less<typename std::iterator_traits<Iterator>::value_type>{});
}
