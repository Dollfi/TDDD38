/*
 * An implementation of selection sort for vector<int> using the STL
 */

#include <vector>
#include <algorithm>

void sort(std::vector<int> & v)
{
    for ( auto current {begin(v)}; current != end(v); ++current )
    {
        auto min = std::min_element(current, end(v));
        std::iter_swap(current, min);
    }
}
