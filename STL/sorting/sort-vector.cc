/*
 * A simple implementation of selection sort for vector<int>
 */

#include <vector>

void sort(std::vector<int> & v)
{
    using sz = std::vector<int>::size_type;
    for ( sz current {}; current < v.size(); ++current )
    {
        sz min_index = current;
        for ( sz idx {current}; idx < v.size(); ++idx )
        {
            if ( v[idx] < v[min_index] )
            {
                min_index = idx;
            }
        }
        std::swap( v[current], v[min_index] );
    }
}
