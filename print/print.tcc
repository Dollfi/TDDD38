#include <iostream>
#include <string>

void print()
{
}

template <typename ...Args>
void print_common(Args...);

template <typename Container, typename ...Args>
auto print(Container const & c, Args... tail)
    -> decltype(begin(c), c.size(), void()) // uses the standard comma-operator 
                                            // (it's not several arguments to decltype)
{

    auto is_vector =
        std::is_same<std::vector<typename Container::value_type,
                                 typename Container::allocator_type>,
                     Container>::value;


    if ( is_vector )
        std::cout << '[';
    else
        std::cout << '{';
    auto sz = c.size()-1;
    auto i = decltype(sz){0};
    decltype(sz) i{}; 
   for ( auto const & elem : c )
    {
        print(elem);
        if (i++ < sz)
            std::cout << ", ";
    }
    if ( is_vector )
        std::cout << ']';
    else
        std::cout << '}';
    print_common(tail...);
}

template <typename ...Args>
void print(char const * s, Args... tail)
{
    std::cout << '"' << s << '"';
    print_common(tail...);
}

template <typename ...Args>
void print(std::string const & s, Args... tail)
{
    print(s.c_str(), tail...);
}

template <typename ...Args>
void print(char first, Args... tail)
{
    std::cout << "'" << first << "'";
    print_common(tail...);
}

template <typename T, typename ...Args>
auto print( T const & first, Args... tail)
    -> decltype(std::cout << first, void())
{
    std::cout << first;
    print_common(tail...);
}

template <typename ...Args>
void print_common(Args... args)
{
    if (sizeof...(args) != 0) std::cout << ", ";
    print(args...);
}
