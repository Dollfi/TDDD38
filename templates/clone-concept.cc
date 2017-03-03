#include <type_traits>
class Return_Const
{
public:
    Return_Const const* clone() const;
};

class Correct
{
public:
    Correct* clone() const;
};

class Not_Const
{
public:
    Not_Const* clone();
};

class Wrong_Return
{
public:
    void * clone() const;
};

class No_Clone {};

// template class that requires T to have a const member 
// function, clone that returns T*
template <typename T>
requires
requires (T const & t) {
    { t.clone() } -> T*;
}
class tmpl
{
private:
/*    static_assert(std::is_same<decltype(std::declval<T const>().clone()),
                               T*>::value,
                  "Must return T*");
*/    // declval "creates" an object of type "T const". On that object we try
    // to call clone(). We then check if the return type is T*
    
    // All is done at compile-time in an unevaluated context (the expression in
    // decltype is always unevaluated). We're not actually creating an object of
    // type "T const". This is a generic way of calling members even if it's
    // impossible to create an object of type T. T could be an abstract class or
    // missing matching constructors.
    // We then use is_same that will, depending on if the first parameter has  
    // the same type as the second one, inherit from either true_type or
    // false_type. Both have a member "value" of type bool that has value true
    // or false respectively.
    // static_assert checks it's first argument at compile time and if it's true,
    // a compiler error is emmited and the string literal is printed. Otherwise,
    // the entire call is removed from the binary (it's only a compile-time 
    // check).
};


int main()
{
    tmpl<Correct> {};
    tmpl<Not_Const> {};
    tmpl<Wrong_Return> {};
    tmpl<No_Clone> {};
    tmpl<Return_Const> {};
}
