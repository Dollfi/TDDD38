#include "Array.h"
template <typename T, size_t N>
template<typename ...U>
requires ( std::is_same<T,U>::value && ... ) && sizeof...(U) <= N
Array<T,N>::Array(U... vals)
{
    init(0, vals...);
}
 
template <typename T, size_t N>
T const & Array<T,N>::operator[](size_t i) const
{
    return data[i];
}
template <typename T, size_t N>
T & Array<T,N>::operator[](size_t i)
{
    return data[i];
}

template <typename T, size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::end() const { return data+N; }


template <typename T, size_t N>
typename Array<T,N>::iterator
Array<T,N>::end() { return data+N; }


template <typename T, size_t N>
typename Array<T,N>::const_iterator
Array<T,N>::begin() const { return data; }


template <typename T, size_t N>
typename Array<T,N>::iterator
Array<T,N>::begin() { return data; }

// std::make_index_sequence<N> creates an std::index_sequence with 
// values values {0, ..., N-1} (of type size_t)
template <typename T, size_t N>
template <size_t sz>
void Array<T,N>::fill(size_t idx, T const (&vals)[sz] )
{
    fill(idx, vals, std::make_index_sequence<sz>());
}

template <typename T, size_t N>
template <size_t sz, size_t ...idxs>
void Array<T,N>::fill(size_t idx, T const (&vals)[sz], std::index_sequence<idxs...>)
{
    // for each element in idxs (each value in {0...sz-1}) do the assignment.
    // Fold over the comma-operator => evaluate all expressions, do nothing with
    // the result
    ((data[idx+idxs] = vals[idxs]), ...);
}

template <typename T, size_t N>
template <typename ...U>
void Array<T,N>::init(size_t idx, T first, U... tail)
{
    data[idx] = first;
    // constexpr-if, new in c++17. Will only compile the block if the condition
    // is true. Needed here since there is no overload of init that only accepts
    // the index (tail... expand to nothing)
    // The old way of solving it would be to create an overload taking either
    // zero or one argument.
    if constexpr (sizeof...(tail))
        init(idx+1, tail...);
}

template <typename T, size_t N1, size_t N2>
Array<T, N1+N2>
concat(Array<T,N1> const & a1, Array<T,N2> const & a2)
{
    Array<T,N1+N2> res;
    res.fill(0, a1.data);
    res.fill(N1, a2.data);
    return res;
}
