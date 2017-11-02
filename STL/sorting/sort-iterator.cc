/*
 * An implementation of selection sort for iterators spanning a range
 */

#include <vector>
#include <algorithm>

template <typename Iterator>
void sort(Iterator first, Iterator last)
{
    for ( auto current {first}; current != last; ++current )
    {
        auto min = std::min_element(current, last);
        std::iter_swap(current, min);
    }
}
