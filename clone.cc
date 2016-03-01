#include <type_traits>

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

template <typename T>
class tmpl
{
private:

  static_assert(std::is_same<decltype(std::declval<T const>().clone()), T*>{}, "Must return T*");

};


int main()
{
  tmpl<Correct> {};
  tmpl<Not_Const> {};
  tmpl<Wrong_Return> {};
  tmpl<No_Clone> {};
}
