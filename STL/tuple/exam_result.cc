// An example on how to use std::tuple to simplify implementation
// of comparison operators for our own class.
//
// Also shows how to implement the tuple interface (get, tuple_size and tuple_element)
// for our class to support structured binding (new feature in C++17). This is implemented
// in both C++17, C++14 and C++98 syntax to show some difference in technique.

#include <algorithm>
#include <sstream>
#include <tuple>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <iomanip>

// ***************  C++98 solution for tuple interface
// Primary template needed for C++98 syntax. We want the return type of get
// to be based on the element/index and have to make that into a template.
//
// In this case, the return type should be string for most cases so we make
// that into the primary template and add a specialization for index 2 (grade)
/*
template <size_t>
struct student_element
{
    typedef std::string type;
};

template <>
struct student_element<2>
{
    using type = char;
};
*/
class Student_Data
{
    // internal private helper function to convert into tuple.
    // make_tuple creates a tuple with copies of the values
    // passed. std::tie requires all arguments to be l-values (i.e. variables)
    // and returns a tuple of references to those objects. 
    auto to_tuple() const
    {
        // we can't use the normal ascii-based sorting for grade since
        // we wanted a specific order
        return std::make_tuple(std::string{"543U"}.find(grade),
                        surname, name, pnr);
    }

public:
    Student_Data(std::string n, std::string sn, std::string pnr, char grade='U', int points=0)
        : name{n}, surname{sn}, pnr{pnr}, grade{grade}, points{points}
    {}
    Student_Data() = default;

    friend std::ostream & operator<<(std::ostream & os, Student_Data const & s)
    {
        using std::setw;
        // always good to reset the state if we modify it with manipulators
        auto flags {os.flags()};
        os << std::left << setw(30) << (s.surname + ", " + s.name)
           << s.pnr
           << std::right << setw(7) << s.grade
           << " (" << setw(2) << s.points << ")";
        os.flags(flags);
        return os;
    }
    
    bool operator<(Student_Data const & rhs) const
    {
        // tuple as lexicographic comparison built-in. Without
        // tuple we would have to solve this with lots of if-statements.
        return to_tuple() < rhs.to_tuple();
    }
    
    // declare get as a friend so that it can access private data
    template <size_t>
        friend auto get(Student_Data const &);

    // C++98 version (no auto return type, but has to be the same for all
    // specializations):
    /*
      template <size_t N>
      friend typename student_element<N>::type get(Student_Data const &);
    */
private:
    std::string name{}, surname{}, pnr{};
    char grade {'U'};
    int points{};
};

std::istream & operator>>(std::istream & is, Student_Data & s)
{
    // we know that each student has a separate line in the file =>
    //  read a line and process it with stringstream
    using std::getline;
    std::string name, surname, pnr;
    int points;
    char grade;
    std::string line;
    getline(is, line);
    std::istringstream iss{line};
    getline(iss>>std::ws, name, ':');
    getline(iss, surname, ':');
    getline(iss, pnr, ':');
    iss >> points;
    iss.ignore();
    grade = iss.get();
    s = Student_Data{name, surname, pnr, grade, points};
    return is;
}

// C++17 supports constexpr-if. Only the true branch will be evaluated
// at compile-time. All others will be removed => only the true branch 
// has to compile. In our case, auto would be faulty since we have different
// types for our return statements.
template <size_t idx>
auto get(Student_Data const & s)
{
    if constexpr (idx == 0)
    {
        return s.name;
    }
    else if constexpr ( idx == 1 )
    {
        return s.surname;
    }
    else if constexpr ( idx == 2 )
    {
        return s.grade;
    }
}

// before constexpr-if was added, you had to create a primary template and
// specialize it for the different cases. C++14 allows us to use auto
// return type
/*
template <size_t N>
auto get(Student_Data const &);

template<>
auto get<0>(Student_Data const & s)
{
    return s.name;
}

template<>
auto get<1>(Student_Data const & s)
{
    return s.surname;
}

template<>
auto get<2>(Student_Data const & s)
{
    return s.grade;
}
*/

// C++98 version: no auto return type
// Please note that ::type is a dependant name (depends on the template argument)
// and could possibly be a non-type. The compiler can't (and isn't allowed to)
// expect it to be a type so we have to tell the compiler that it is a type with
// typename

// Primary template
/*
template <size_t N>
typename student_element<N>::type get(Student_Data const &);

// specializations
template<>
typename student_element<0>::type get<0>(Student_Data const & s)
{
    return s.name;
}

template<>
se_t<1> get<1>(Student_Data const & s)
{
    return s.surname;
}


template<>
se_t<2> get<2>(Student_Data const & s)
{
    return s.grade;
}
*/

namespace std
{
    template <>
    struct tuple_size<Student_Data> : std::integral_constant<size_t, 3> {};

    // C++14 added decltype and declval
    // decltype gives the type of an (unevaluated) expression
    // declval "creates" an object of the given type. It can only
    // be used in an unevaluated context so no actual object is created.
    // declval is a great tool in generic code since it might be hard to
    // create some types (depends on constructors). Here we have a default
    // constructor so decltype(get<idx>(Student_Data{})) would work as well.
    template<size_t idx>
    struct tuple_element<idx, Student_Data>
    {
        using type = decltype(get<idx>(declval<Student_Data>()));
    };
    // C++98 version - just inherit from the corresponding student_element
    /* template<size_t idx>
       struct tuple_element<idx, Student_Data> : student_element<idx> {};
    */
}

using namespace std;

int main()
{
    vector<Student_Data> results {istream_iterator<Student_Data>{cin},
                                  istream_iterator<Student_Data>{}};
    sort(begin(results), end(results));
    copy(begin(results), end(results), ostream_iterator<Student_Data>{cout, "\n"});

    Student_Data s {"Eric", "Elfving", "someDate", '5', 25}; 
    auto [name, surname, grade] = s;
}
