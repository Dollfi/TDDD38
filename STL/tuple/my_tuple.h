#ifndef TESTING_MY_TUPLE_H
#define TESTING_MY_TUPLE_H

// a tuple-like class (inspired by the gcc implementation of std::tuple)

#include <cstddef>
#include <type_traits>
#include <string>
#include <utility>

namespace My_Tuple
{

    template<typename ...Args>
    struct tuple;


    template<size_t idx, typename Head>
    struct TupleBase
    {
        constexpr TupleBase(Head const &d)
                : data{d}
        {
        }

        constexpr TupleBase() = default;

        static Head &&_head(TupleBase &&t)
        {
            return std::move(t.data);
        }

        static Head &_head(TupleBase &t)
        {
            return t.data;
        }

        static Head const &_head(TupleBase const &t)
        {
            return t.data;
        }

        Head data;
    };

    template<size_t idx, typename ...Elems>
    struct TupleImpl;

    template<size_t TupleIndex, typename Head, typename ...Tail>
    struct TupleImpl<TupleIndex, Head, Tail...> :
            public TupleImpl<TupleIndex + 1, Tail...>,
            public TupleBase<TupleIndex, Head>
    {


        using HeadType = TupleBase<TupleIndex, Head>;
        using TailType = TupleImpl<TupleIndex + 1, Tail...>;

        constexpr TupleImpl(HeadType const &h, const Tail &... t) 
            : TailType{t...}, HeadType{h}
        {
        }

        constexpr TupleImpl() : TailType{}, HeadType{}
        {
        }

        static constexpr Head &_head(TupleImpl &t)
        {
            return HeadType::_head(t);
        }

        static constexpr TailType &_tail(TupleImpl &t)
        {
            return t;
        }

        static constexpr Head &&_head(TupleImpl &&t)
        {
            return HeadType::_head(std::move(t));
        }

        static constexpr TailType _tail(TupleImpl &&t)
        {
            return t;
        }

        static constexpr Head const &_head(TupleImpl const &t)
        {
            return HeadType::_head(t);
        }

        static constexpr TailType const &_tail(TupleImpl const &t)
        {
            return t;
        }

        TupleImpl &operator=(TupleImpl const &t)
        {
            _head(*this) = _head(t);
            _tail(*this) = _tail(t);
            return *this;
        }

        TupleImpl &operator=(TupleImpl &&t)
        {
            _head(*this) = std::move(_head(t));
            _tail(*this) = std::move(_tail(t));
            return *this;
        }
    };

    template<size_t TupleIndex, typename Head>
    struct TupleImpl<TupleIndex, Head> : public TupleBase<TupleIndex, Head>
    {
        using HeadType = TupleBase<TupleIndex, Head>;

        constexpr TupleImpl(Head const &h) : HeadType{h}
        {
        }

        constexpr TupleImpl() : HeadType{}
        {
        }
    };

    template<size_t idx, typename Head, typename ...Tail>
    constexpr Head &
    get_by_index(TupleImpl<idx, Head, Tail...> &ti)
    {
        return TupleImpl<idx, Head, Tail...>::_head(ti);
    }

    template<size_t idx, typename Head, typename ...Tail>
    constexpr Head const &
    get_by_index(TupleImpl<idx, Head, Tail...> const &ti)
    {
        return TupleImpl<idx, Head, Tail...>::_head(ti);
    }

    template<size_t idx, typename Head, typename ...Tail>
    constexpr Head &&
    get_by_index(TupleImpl<idx, Head, Tail...> &&ti)
    {
        return TupleImpl<idx, Head, Tail...>::_head(std::move(ti));
    }

    template <typename Head, size_t idx, typename ...Tail>
    constexpr Head &
    get_by_type(TupleImpl<idx, Head, Tail...> &ti)
    {
        return TupleImpl<idx,Head,Tail...>::_head(ti);
    }

    template <typename Head, size_t idx, typename ...Tail>
    constexpr Head const &
    get_by_type(TupleImpl<idx, Head, Tail...> const &ti)
    {
        return TupleImpl<idx,Head,Tail...>::_head(ti);
    }

    template <typename Head, size_t idx, typename ...Tail>
    constexpr Head &&
    get_by_type(TupleImpl<idx, Head, Tail...> &&ti)
    {
        return TupleImpl<idx,Head,Tail...>::_head(std::move(ti));
    }

    template<size_t idx, typename ...Elems>
    constexpr std::tuple_element_t<idx, My_Tuple::tuple<Elems...>> &
    get(tuple<Elems...> &tp)
    {
        return My_Tuple::get_by_index<idx>(tp);
    }

    template<size_t idx, typename ...Elems>
    constexpr std::tuple_element_t<idx, My_Tuple::tuple<Elems...>> const &
    get(tuple<Elems...> const &tp)
    {
        return My_Tuple::get_by_index<idx>(tp);
    }

    template<size_t idx, typename ...Elems>
    constexpr std::tuple_element_t<idx, My_Tuple::tuple<Elems...>> &&
    get(tuple<Elems...> &&tp)
    {
        return My_Tuple::get_by_index<idx>(std::move(tp));
    }

    template<typename T, typename ...Elems>
    constexpr T &
    get(tuple<Elems...> &t)
    {
        return My_Tuple::get_by_type<T>(t);
    }

    template<typename T, typename ...Elems>
    constexpr T const &
    get(tuple<Elems...> const &t)
    {
        return My_Tuple::get_by_type<T>(t);
    }

    template<typename T, typename ...Elems>
    constexpr T &&
    get(tuple<Elems...> &&t)
    {
        return My_Tuple::get_by_type<T>(std::move(t));
    }

   template<typename ...Elements>
    struct tuple : TupleImpl<0, Elements...>
    {
        using impl = TupleImpl<0, Elements...>;

        tuple(Elements const &...e) : impl(e...)
        {
        }

        tuple &operator=(tuple const &t)
        {
            static_cast<impl &>(*this) = t;
            return *this;
        }

        tuple &operator=(tuple &&r)
        {
            static_cast<impl &>(*this) = std::move(r);
            return *this;
        }

        tuple(tuple const &) = default;
    };

 
    template<>
    struct tuple<>
    {
        tuple() = default;
    };

   template<typename ...E>
    tuple<E &...> tie(E &... es)
    {
        return {es...};
    }
}

namespace std
{
    // tuple_size is an integral_constant with value=number of elements
    template<typename ...Elems>
    struct tuple_size<My_Tuple::tuple<Elems...>>
        : public std::integral_constant<size_t, sizeof...(Elems)>
    {
    };
    
    // tuple_element is a recursive definition with a specialization
    // for index 0 which is the one used.
    template<size_t idx, typename Head, typename ...Tail>
    struct tuple_element<idx, My_Tuple::tuple<Head, Tail...>>
            : tuple_element<idx - 1, My_Tuple::tuple<Tail...>>
    {
    };

    template<typename Head, typename ...Tail>
    struct tuple_element<0, My_Tuple::tuple<Head, Tail...>>
    {
        using type = Head;
    };

    // specialization to catch faulty usage - non-zero index (zero is caught with
    // the specialization above) with an empty tuple.
    template<size_t idx>
    struct tuple_element<idx, My_Tuple::tuple<>>
    {
        static_assert(idx < tuple_size<My_Tuple::tuple<>>::value, "tuple: Index too large");
    };

}
#endif //TESTING_MY_TUPLE_H

