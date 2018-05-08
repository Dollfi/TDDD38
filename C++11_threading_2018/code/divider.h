#pragma once

template <typename Cont>
class Divider
{
public:
  Divider(Cont& c, int parts)
    : c{c}, parts{parts}, base{size(c)/parts}, rem{size(c)%parts} {}

  typename Cont::iterator begin() { return std::begin(c); }
  typename Cont::iterator end() { return std::end(c); }
  
  typename Cont::iterator begin(typename Cont::size_type i)
  {
    return next(std::begin(c), i * base + (i < rem ? i : rem) );
  }
  
  typename Cont::iterator end(typename Cont::size_type i)
  {
    return begin(i+1);
  }
  
private:
  Cont& c;
  int parts;
  typename Cont::size_type base;
  typename Cont::size_type rem;
};
