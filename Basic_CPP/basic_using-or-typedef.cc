#include <type_traits>

// trying to declare an alias for an array of ten ints

using arr_t = int[10];
typedef int arr2_t[10];

// Will not compile:
// typedef int[10] arr2_t;

int main()
{
    // is_same::value is true if the two types are the same
    return !std::is_same<arr_t, arr2_t>::value;
}
