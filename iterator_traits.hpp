#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include "utility.hpp"


namespace ft
{
//iterator_traits
	template <class Iterator> 
	struct iterator_traits{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer		   		pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T> 
	struct iterator_traits<T*>{
		typedef typename std::ptrdiff_t					 	difference_type;
		typedef T									 		value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class T> 
	struct iterator_traits<const T*>{
		typedef typename std::ptrdiff_t					 	difference_type;
		typedef T								  			value_type;
		typedef const T*						   			pointer;
		typedef const T&						   			reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

//iterator
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T		value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

// reverse_iterator
	template <class Iter>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference>
	{
		protected:
			Iter _iter;
		public:
			typedef Iter											iterator_type;
			typedef typename iterator_traits<Iter>::value_type	  	value_type;
			typedef typename iterator_traits<Iter>::difference_type	difference_type;
			typedef typename iterator_traits<Iter>::reference	   	reference;
			typedef typename iterator_traits<Iter>::pointer		 	pointer;

			
			reverse_iterator() : _iter() {}
			
			explicit reverse_iterator(Iter _x) : _iter(_x) {}

			template <class U>	
			reverse_iterator(const reverse_iterator<U>& __u) : _iter(__u.base()) {}

			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U>& __u)
					{ _iter = __u.base(); return *this; }
			
			Iter base() const {return _iter;}
			
			reference operator*() const {Iter tmp = _iter; return *--tmp;}
			
			pointer  operator->() const {return &(operator*());} // ?????
			
			reverse_iterator& operator++() {--_iter; return *this;}
			
			reverse_iterator  operator++(int) {reverse_iterator tmp(*this); --_iter; return tmp;}
			
			reverse_iterator& operator--() {++_iter; return *this;}
			
			reverse_iterator  operator--(int) {reverse_iterator tmp(*this); ++_iter; return tmp;}
			
			reverse_iterator  operator+ (difference_type n) const {return reverse_iterator(_iter - n);}
			
			reverse_iterator& operator+=(difference_type n) {_iter -= n; return *this;}
			
			reverse_iterator  operator- (difference_type n) const {return reverse_iterator(_iter + n);}
			
			reverse_iterator& operator-=(difference_type n) {_iter += n; return *this;}
			
			reference		 operator[](difference_type n) const {return *(*this + n);}
	};

	template <class Iter1, class Iter2>
	inline bool operator==(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __x.base() == __y.base();
	}

	template <class Iter1, class Iter2>
	inline bool operator<(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __x.base() > __y.base();
	}

	template <class Iter1, class Iter2>
	inline bool operator!=(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __x.base() != __y.base();
	}

	template <class Iter1, class Iter2>
	inline bool operator>(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __x.base() < __y.base();
	}

	template <class Iter1, class Iter2>
	inline bool operator>=(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __x.base() <= __y.base();
	}

	template <class Iter1, class Iter2>
	inline bool operator<=(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __x.base() >= __y.base();
	}

	template <class Iter1, class Iter2>
	inline 
	typename reverse_iterator<Iter1>::difference_type
	operator-(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y)
	{
		return __y.base() - __x.base();
	}

	template <class Iter>
	inline 
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type __n, const reverse_iterator<Iter>& __x)
	{
		return reverse_iterator<Iter>(__x.base() - __n);
	}

// base_iter
//________________________________________________________________________________________________________
//________________________________________________________________________________________________________
	template <class _Iter>
	class base_iter
	{
	public:
		typedef _Iter														iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		iterator_type __i;

	public:
		base_iter(){}
		base_iter(pointer __x) : __i(__x) {}
		// template <class _Up>
		// base_iter(const base_iter<_Up>& __u, typename ft::enable_if<!ft::is_integral<_Up>::value, void>::type* = 0): __i(__u.base()){}
		template <class _Up>
		base_iter(const base_iter<_Up>& __u): __i(__u.base()){}

		reference operator*() const { return *__i; }
		pointer  operator->() const { return __i; }
		base_iter& operator++(){ ++__i; return *this; }
		base_iter  operator++(int) { base_iter __tmp = *this; ++(*this); return __tmp; }
		base_iter& operator--() { --__i; return *this; }
		base_iter  operator--(int) { base_iter __tmp = *this; --(*this); return __tmp; }
		base_iter  operator+ (difference_type __n) const { base_iter __w(*this); __w += __n; return __w; }
		base_iter& operator+=(difference_type __n) { __i += __n; return *this; }
		base_iter  operator- (difference_type __n) const { return *this + (-__n); }
		base_iter& operator-=(difference_type __n) {*this += -__n; return *this;}
		reference operator[](difference_type __n) const { return __i[__n]; }
		pointer base() const {return __i;}
	};

	template <class _Iter1, class _Iter2>
	inline bool operator==(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return __x.base() == __y.base(); }
	
	template <class _Iter1, class _Iter2>
	inline bool operator<(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return __x.base() < __y.base(); }

	template <class _Iter1, class _Iter2>
	inline bool operator!=(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return !(__x == __y); }

	template <class _Iter1, class _Iter2>
	inline bool operator>(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return __y < __x; }

	template <class _Iter1, class _Iter2>
	inline bool operator>=(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return !(__x < __y); }

	template <class _Iter1, class _Iter2>
	inline bool operator<=(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return !(__y < __x); }

	template <class _Iter1>
	inline bool operator!=(const base_iter<_Iter1>& __x, const base_iter<_Iter1>& __y) { return !(__x == __y); }

	template <class _Iter1>
	inline bool operator>(const base_iter<_Iter1>& __x, const base_iter<_Iter1>& __y) { return __y < __x; }

	template <class _Iter1>
	inline bool operator>=(const base_iter<_Iter1>& __x, const base_iter<_Iter1>& __y) { return !(__x < __y); }

	template <class _Iter1>
	inline bool operator<=(const base_iter<_Iter1>& __x, const base_iter<_Iter1>& __y) { return !(__y < __x); }

	template <class _Iter1, class _Iter2>
	inline typename base_iter<_Iter1>::difference_type operator-(const base_iter<_Iter1>& __x, const base_iter<_Iter2>& __y) { return __x.base() - __y.base(); }

	template <class _Iter>
	inline base_iter<_Iter> operator+(typename base_iter<_Iter>::difference_type __n, base_iter<_Iter> __x) { __x += __n; return __x; }


} // namespace ft

#endif


