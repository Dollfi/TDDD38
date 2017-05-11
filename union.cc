// Short example of old union. Here we are creating a class with
// an anonymous union member and keep track of the type of the current
// value.
#include <stdexcept>
#include <iostream>
using namespace std;

class Union
{
public:
    Union()
        : i{}
    {
    }

    ~Union()
    {
        // have to call string destructor if we are storing a string
        if ( type == Type::str )
        {
            s.~string();
        }
    }

    void set(string const & str)
    {
        if ( type != Type::str )
        {
            // use placement-new to call string constructor at the
            // location of s. This gives a valid string object
            new(&s) string;
        }
        s = str;
        type = Type::str;

    }
    void set(int i)
    {
        if ( type == Type::str )
        {
            s.~string();
        }
        this->i = i;
        type = Type::num;
    }

    string & str()
    {
        if ( type  == Type::str )
            return s;
        throw std::runtime_error{"Wrong type"};
    }

    int & num()
    {
        if ( type == Type::num )
            return i;
        throw std::runtime_error{"Wrong type"};
    }



private:

    // scoped enumerator to keep track of current type
    enum class Type 
    {
        str, num
    };


    Type type {Type::num};

    union {
        int i;
        string s;
    };
};

int main()
{
    Union u;
    u.set("hello, this is a long string to get rid of SSO");
    try
    {
        u.num();
    }
    catch (...)
    {
        cout << "Not int!\n";
        cout << u.str();
    }
}
