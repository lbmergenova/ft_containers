#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;
        
        pair() : first(), second() {}

        pair(const first_type& _x, const second_type& _y) : first(_x), second(_y) {}

        template<class U, class V>
        pair(const pair<U, V> & _p) : first(_p.first), second(_p.second) {}

        pair& operator=(pair const& _p) {
            if (this != &_p)
            {
                first = _p.first;
                second = _p.second;                
            }
            return *this;
    }
    };

    template <class T1, class T2> pair<T1,T2> make_pair(T1 _x, T2 _y){
        return pair<T1, T2>(_x, _y);
    }

    template <class T1, class T2>
    bool operator==(const pair<T1,T2>& _x, const pair<T1,T2>& _y){
        return _x.first == _y.first && _x.second == _y.second;
    }

    template <class T1, class T2>
    bool operator< (const pair<T1,T2>& _x, const pair<T1,T2>& _y){
        return _x.first < _y.first || (!(_y.first < _x.first) && _x.second < _y.second);
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1,T2>& _x, const pair<T1,T2>& _y){
        return !(_x == _y);
    }

    template <class T1, class T2>
    bool operator> (const pair<T1,T2>& _x, const pair<T1,T2>& _y){
        return _y < _x;
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1,T2>& _x, const pair<T1,T2>& _y){
        return !(_x < _y);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1,T2>& _x, const pair<T1,T2>& _y){
        return !(_y < _x);
    }

} // namespace ft


#endif