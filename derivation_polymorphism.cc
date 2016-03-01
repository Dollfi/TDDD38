// An example of inheritance and polymorphism 
// created after seminar 3, spring 2016.

// If you are using g++, remember to use the compiler flag -Weffc++ for
// extra warnings regarding inheritance (and some other stuff, check
// the man-pages)

// Remember: to get polymorphic behavior in C++, we need 
// a) A virtual function in base class
// b) A pointer or reference to base class
#include <memory>
#include <iostream>
#include <vector>

using namespace std;

/*  A (very nice ASCII-art) class diagram for this example
                B
                ^
                |
          -------------
          |           |
          D1          D2
          ^           ^ 
          |           |
          E1          E2
*/

class B
{
public:
    // a pure virtual function makes this class abstract. No object of this
    // type can be created (unless as a subpart of a derived class). A 
    // derived class has to override this function to be a concrete type
    virtual void foo() const  = 0;

    // A virtual destructor is VERY IMPORTANT! without it, a pointer to
    // B will ONLY call the destructor for B, no destructor for derived 
    // classes will be executed
    virtual ~B() = default;    
protected:
    B(int v) : value {v} {}
    B() = default;
private:
    int value {};
};

// We can implent the pure virtual function out of class scope. The 
// class will still be abstract
void B::foo() const
{
    cout << "B::foo " << value << endl;
}

class D1 : public B
{
public:
    // This will create constructors with the same signature
    // as the ones in B (that are not default constructors or copy/move)
    // They will have the same access as the base class constructor
    // according to 12.9/4
    using B::B;
    // We will have a constructor that works like this:
    // protected: D(int v): B{v} {} 

    D1() = default;
    // The defaulted version will call the default constructor in B

    // virtual is not needed here. The override keyword is not needed,
    // but the compiler will emit errors if the signature is wrong.
    // final will make it illegal to override this function in subclasses
    void foo() const final override
    {
        // calling the function in the base class
        B::foo();
        cout << "D1" << endl;
    }

    // a new virtual function
    virtual void bar() const 
    {
        cout << "D1::bar" << endl;
    }

private:
    int val {5};
};

// final keyword forbids derivation from this class
class E1 final : public D1
{
public:
    E1(int v): D1{v} {}

    // Will not do anything, we already have a constructor taking int
    // and the default constructor isn't inherited
    using D1::D1;
    
    // gives error: overriding final function ‘virtual void D1::foo() const’
    /*
    void foo() const override
    {
        cout << "E1" << endl;
    }
    */
    void bar() const override
    {
        cout << "E1::bar" << endl;
    }
};

class D2 : public B
{
protected:
    string val{"No value!"};
};

class E2: public D2
{
public:
    void foo() const override
    {
        cout << "E2 " << val << endl;
    }
};


class A 
{
public:
    void fun(int) {}
    void fun(char) {}
    void fun(double) {}
protected:
    void fun(string) {}
};

class A_D: public A
{
public:
    void fun(B const & b) 
    {
        b.foo();
    }
    // This using-declaration will make all names matching A::fun available
    // in this scope (i.e. public part of A_D)
    using A::fun;
    // remove the inherited overload for double
    void fun(double) = delete;


};

void fun(B const &  b)
{
    b.foo();
}

int main()
{
    A_D a;
    // calls the string overload from A
    a.fun("hi");
    // calls the overload for "B const &" in A_D
    a.fun(E1{6});

    // unique_ptr is a wrapper for a pointer for unique ownership, i.e.
    // the resource is only used in one place. Use shared_ptr if you
    // want to share a resource. The smart pointer will automatically
    // take care of that resource (i.e. delete the pointer) when we're done
    // with it. There are special versions that can take a user-defined
    // cleanup function instead of doing delete -> you can handle other
    // resources as well!
    vector<unique_ptr<B>> vec;

    // emplace_back takes the arguments needed to create
    // an object of the stored type (arguments are forwarded to the
    // constructor
    vec.emplace_back(new D1);
    vec.emplace_back(new E1{5});
    // Error, no default constructor in E1
    //vec.emplace_back(new E1);
    vec.emplace_back(new E2);
    vec.emplace_back(new E2);

    for ( auto && ptr : vec )
    {
        ptr->foo();

        // unique_ptr::get() returns a regular pointer to the owned object
        // The static type of ptr.get() is B* so we can't call bar on that
        // pointer. We know that all classes that derives from D1 has a bar
        // member so we cast the pointer into D1* using dynamic_cast.
        // dynamic_cast return a valid pointer if the dynamic type is D1 (or
        // derived from D1) and nullptr otherwise.
        // is one type of RTTI, RunTime Type Information
        auto p = dynamic_cast<D1*>(ptr.get());
        if ( p != nullptr )
            p->bar();


        // an intresting alternative that probably breaks your coding style
        // guide, but won't clutter your namespace with extra pointers
        /*
        if ( auto p = dynamic_cast<D1*>(ptr.get()) )
            p->bar();
        */
    }
    B* pb = new E1{34};
    delete pb;
}
