/*
 * A simple implementation of selection sort for 
 *  some given container (that supports ForwardIterator)
 */

#include <vector>
#include <algorithm>

template <typename Container>
void sort(Container & v)
{
    for ( auto current {begin(v)}; current != end(v); ++current )
    {
        auto min = std::min_element(current, end(v));
        std::iter_swap(current, min);
    }
}
