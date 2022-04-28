#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template< class T, class Container = ft::vector<T> > 
    class stack
    {
    public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

    protected:
        container_type c;

    public:
        explicit stack(const container_type& _c = container_type()) : c(_c) {}
        stack(const stack& x) : c(x.c) {}
        ~stack(){}

        stack& operator=(const stack& q) { c = q.c; return *this; }

        bool empty() const { return c.empty(); }
        size_type size() const {return c.size();}
        reference top() {return c.back();}
        const_reference top() const {return c.back();}

        void push(const value_type& x) {c.push_back(x);}
        void pop() {c.pop_back();}

        friend bool operator==(const stack& x, const stack& y) { return x.c == y.c; }

        friend bool operator< (const stack& x, const stack& y){ return x.c < y.c; }
    };

    template <class T, class Container>
    bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return !(x == y);
    }

    template <class T, class Container>
    bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return y < x;
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return !(x < y);
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return !(y < x);
    }
   
} // namespace ft


#endif