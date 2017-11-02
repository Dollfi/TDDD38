/*
 * An implementation of selection sort using STL algorithms
 * Accepts a pair of iterators spanning the range of values to
 * be sorted and a binary predicate function for comparison of 
 * elements, uses operator< (std::less) by default
 */

#include <vector>
#include <algorithm>
#include <functional>
// using the void specialization
template <typename Iterator, typename Comp = std::less<>>
// without void specialization:
//template <typename Iterator,
//          typename Comp = std::less<
//                   typename std::iterator_traits<Iterator>::value_type>>
//Use a value-initialized Comp object as default argument
void sort(Iterator first, Iterator last, Comp comp = {})
{
    for ( auto current {first}; current != last; ++current )
    {
        auto min = std::min_element(current, last, comp);
        std::iter_swap(current, min);
    }
}

