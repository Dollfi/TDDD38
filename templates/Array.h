/* 
 * Array class declaration file. A simplification of std::array
 * Created 2017-10-10 by Eric Elfving
 */
#pragma once

#include <utility>
#include <type_traits>

template <typename T, size_t N>
class Array
{
public:
    // Some public member type declarations
    using iterator = T*;
    using const_iterator = T const *;
    using value_type = T;

    Array() = default;
    
    static size_t size() const;

    // Constructor taking values of type T and initializes the
    // internal array
    template <typename ...U>
        requires ( std::is_same<T,U>::value && ... ) && sizeof...(U) <= N
    Array(U...);

    // Access operator
    T const & operator[](size_t) const;
    T       & operator[](size_t);

    // copies elements in range [0, min(N-idx, Sz)) from given array
    template <size_t Sz>
    void fill(size_t, T const (&)[Sz]);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end()   const;
private:

    template <typename U, size_t N1, size_t N2>
    friend Array<U, N1+N2> concat(Array<U, N1> const &, Array<U, N2> const&);
 
    // Initializes the internal array with given values starting at index idx
    template <typename ...U>
    void init(size_t idx, T first, U... tail);
    
    // helper for fill
    template <size_t sz,size_t...idxs>
    void fill(size_t idx, T const (&vals)[sz], 
              std::index_sequence<idxs...>);

   T data[N] {};
};

// Deduction guide. Checks that the arguments are valid (only values of same type)
// and helps the compiler create the correct type (deduce values for T and N)
template <typename T, typename ...Rest>
Array(T, Rest...) 
    -> Array<std::enable_if_t<(std::is_same_v<T, Rest> && ... ),
                              T>,
             sizeof...(Rest)+1>;

#include "Array.tcc"
   
