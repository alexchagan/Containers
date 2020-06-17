//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_FILTERFALSE_HPP
#define ITERTOOLS_CFAR_A_FILTERFALSE_HPP

#include <sys/types.h> //uint

namespace itertools {
    template< typename functor, typename Iter>
    class filterfalse {
        functor _functor;
        Iter & _iter;
        decltype((_iter.begin())) _beg;//decltype uses to deduce runtime type of an object
        decltype((_iter.end())) _end_iter;

    public:
        filterfalse(functor func, Iter && iter): _functor(func), _iter(iter), _beg(_iter.begin()), _end_iter(iter.end()){}
        filterfalse(functor func, Iter & iter): _functor(func), _iter(iter), _beg(_iter.begin()), _end_iter(iter.end()){}

        class iterator
        {
            functor _filter;
            decltype((_iter.begin())) & _inner_iter;
            Iter & _it;
            void normalize()
            {
                for(; _inner_iter != _it.end() && _filter(*_inner_iter); ++_inner_iter);//skip who ever not matching the filter
            }

        public:

            /**
             * explict keyword uses for prevent the compiler from using implicit conversation for constructors who
             * accepts 1 primitive type. The compiler as default behavior tries to do implicit conversation of that
             * type to a members exists within the class, hiding a bug.
             */
            iterator(functor operation, decltype((_iter.begin())) & inner_iter, Iter & it) : _filter(operation), _inner_iter(inner_iter), _it(it)
            {
                normalize();//We have to check the first element inside the ctor
            }

            //Iterator class must provide overloading of operators *, ++, !=
            int operator*() const { return *_inner_iter; }
            bool operator==(const iterator& other) const {return _inner_iter == other._inner_iter;}
            bool operator!=(const iterator& other) const { return !(*this == other); }

            iterator& operator++(){
                ++_inner_iter;
                normalize();
                return *this;
            } //prefix ++
        };

        iterator begin() { return iterator(_functor, _beg, _iter); }
        iterator end()   { return iterator(_functor, _end_iter, _iter); }
    };
}

#endif //ITERTOOLS_CFAR_A_FILTERFALSE_HPP
