//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_COMPRESS_HPP
#define ITERTOOLS_CFAR_A_COMPRESS_HPP

#include <vector>
#include <iostream>
using namespace std;

namespace itertools {
    template<typename Iter>
    class compress {
        Iter & _iter; //We don't want to duplicate the container.
        vector<bool> _filter;
        decltype((_iter.begin())) beg;//decltype uses to deduce runtime type of an object
        decltype((_iter.begin())) end_iter;

    public:
        /**
         * explict keyword uses for prevent the compiler from using implicit conversation for constructors who
         * accepts 1 primitive type. The compiler as default behavior tries to do implicit conversation of that
         * type to members exists within the class, hiding a bug.
         */

        //We need a reference to reference ctor in order to support passing reference of rvalue(for range())
        compress(Iter && iter, vector<bool> filter): _iter(iter), _filter(filter), beg(_iter.begin()), end_iter(iter.end())
        {
        }

        template <typename U>
        class iterator{
            decltype((_iter.begin())) & _inner_iter;
            compress & _compress;
            int _indexer;
        public:

            iterator(decltype((_iter.begin())) & inner_iter, compress & compress): _inner_iter(inner_iter), _compress(compress), _indexer(0){}

            //Iterator class must provide overloading of operators *, ++, !=
            U operator*() const { return *_inner_iter; }
            bool operator==(const iterator& other) const { return _inner_iter == other._inner_iter; }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            iterator& operator++(){
                ++_inner_iter;
                ++_indexer;
                for(; _inner_iter != _compress.end_iter && !_compress._filter[_indexer]; ++_inner_iter, ++_indexer);//skip who ever not matching the filter
                return *this;
            } //prefix ++
        };

        auto begin(){ return iterator<decltype(*(_iter.begin()))>(beg, *this);}
        auto end(){ return iterator<decltype(*(_iter.begin()))>(end_iter, *this);}
    };
}


#endif //ITERTOOLS_CFAR_A_COMPRESS_HPP
