//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_ACCUMULATE_HPP
#define ITERTOOLS_CFAR_A_ACCUMULATE_HPP

#include <functional>

/**
 * Lambda expression:
 * [](int x, int y){return x*y;}
 */

namespace itertools {

    //Default function is plus two parameters
    template<typename Iter, typename lambada = std::plus<>>
    class accumulate {
        Iter & _iter; //We don't want to duplicate the container.
        decltype((_iter.begin())) _beg;//decltype uses to deduce runtime type of an object
        decltype((_iter.begin())) _end_iter;
        lambada _func;

    public:
        /**
         * explict keyword uses for prevent the compiler from using implicit conversation for constructors who
         * accepts 1 primitive type. The compiler as default behavior tries to do implicit conversation of that
         * type to a members exists within the class, hiding a bug.
         */
        explicit accumulate(Iter & iter): _iter(iter), _beg(_iter.begin()), _end_iter(iter.end()) {}

        //We need a reference to reference ctor in order to support passing reference of rvalue(for range())
        explicit accumulate(Iter && iter): _iter(iter), _beg(_iter.begin()), _end_iter(iter.end()) {}

        //Support both rvalue and lvalue
        accumulate(Iter & iter, lambada func): _iter(iter), _func(func), _beg(_iter.begin()), _end_iter(iter.end()){}
        accumulate(Iter && iter, lambada func): _iter(iter), _func(func), _beg(_iter.begin()), _end_iter(iter.end()){}

        template <typename U>
        class iterator{
            decltype((_iter.begin())) & _inner_iter;
            lambada _func;
            U _sum;
        public:

            iterator(decltype((_iter.begin())) & inner_iter, lambada func): _inner_iter(inner_iter), _func(func), _sum(*inner_iter){}

            //Iterator class must provide overloading of operators *, ++, !=
            U operator*() const { return _sum; }
            bool operator==(const iterator& other) const { return _inner_iter == other._inner_iter; }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            iterator& operator++(){
                ++_inner_iter;
                _sum = _func(_sum, *_inner_iter);//Perform the function.
                return *this;
            } //prefix ++
        };

        auto begin(){ return iterator<decltype(*(_iter.begin()))>(_beg, _func);}
        auto end(){ return iterator<decltype(*(_iter.begin()))>(_end_iter, _func);}

    };
}

#endif //ITERTOOLS_CFAR_A_ACCUMULATE_HPP