/*
 * Example program using the Array class, a simplification of std::array
 * Created 2017-10-10 by Eric Elfving
 */
#include "Array.h"

int main()
{
    {
        // Creates an array of five int values with initialization
        Array<int, 5> a1 {1,2,3,4,5};
        // Creates an array of five int values, the first three are initialized,
        // the rest are value-initialized
        Array<int, 5> a2 {1,2,3};
    }
    // Compiler figures out that we want an Array<int,3> by using deduction guide
    Array a{3,2,5};
    int sum{};
    // concat creates an Array<int, 5> by joining a and the temporary Array<int, 2> 
    for ( auto && val: concat(a, Array{5,6}) )
    {
        sum += val;
    }
    return sum;
}
