// constexpr lets the compiler call the function at compile-time (for constant
// values). Only some code can be constexpr (can't use dynamic memory for instance)
// You need to use at least one level of optimization (-O) with gcc to get constexpr
// calls at compile time. Without constexpr, the compiler has to call the function
// at runtime

//constexpr 
unsigned Fib(unsigned N)
{
    if (N <= 1)
        return N;
    return Fib(N-1) + Fib(N-2);
}

// Primary template, has member ```value``` with the N'th fibonacci value
template <unsigned N>
struct FIB
{
    static const unsigned value = FIB<N-1>::value + FIB<N-2>::value; 
};

// specialization for N=0 and N=1 (base case for recursion)
template <>
struct FIB<0> { static const unsigned value = 0; };
template <>
struct FIB<1> { static const unsigned value = 1; };

int main()
{
    // return Fib(4);
    return FIB<4>::value;
}
