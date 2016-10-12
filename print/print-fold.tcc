#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
// an inline namespace hides the declarations so that they are only available in this translation unit
namespace {
    template <typename ...Args>
    void print_common(Args...);

    template <typename Container>
    auto print_impl(Container const & c)
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
        //auto i = decltype(sz){0};
        //auto i = sz - sz;
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
    }

    template <typename T>
    auto print_impl( T const & t)
    -> decltype(std::cout << t, void())
    {
        std::cout << t;
    }

    void print_impl(char const * s)
    {
        std::cout << '"' << s << '"';
    }

    void print_impl(char first)
    {
        std::cout << "'" << first << "'";
    }

    void print_impl(std::string const & s)
    {
        print_impl(s.c_str());
    }


    template <typename T>
    void print_common(T && t)
    {
        std::cout << ", ";
        print_impl(std::forward<T>(t));
    }
}

void print()
{}

template <typename T, typename ...Args>
void print(T && t, Args ...args)
{
    ( print_impl(t) , ... , print_common(args) );
}

