#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cassert>
#include "utility.hpp"
#include "iterator_traits.hpp"
#include <iostream>

namespace ft
{
    template<class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef base_iter<pointer>				   			iterator;
		typedef base_iter<const_pointer>					const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

    protected:
		allocator_type		_alloc;
		pointer				_begin;
		size_type			_size;
		size_type			_capacity;

//construct/copy/destroy:
	public:
		explicit vector(const Allocator& _a = Allocator()) : _begin(nullptr), _size(0), _capacity(0), _alloc(_a) {}

		explicit vector(size_type n, const T& value = T(), const Allocator& _a= Allocator()) :  _begin(nullptr), _size(n), _capacity(n), _alloc(_a) {
			if (n > _alloc.max_size())
				throw std::length_error("bad size vector");
		_begin = _alloc.allocate(n);
		while (n--)
			_alloc.construct(_begin + n, value);
		}

		template <class InputIter>
		vector(InputIter __first, InputIter __last, const Allocator& _a = Allocator(), 
		       typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type* = 0) : _begin(nullptr), _alloc(_a)
		{
			_size = _capacity = ft::distance(__first, __last);
			if (_size > max_size())
				throw std::length_error("bad size vector");
			_begin = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_begin + i, *__first++);
		}

		vector(const vector<T,Allocator>& x) : _begin(nullptr), _size(x._size), _capacity(x._capacity), _alloc(x.get_allocator()) {
			if (_size > 0)
			{
				_begin = _alloc.allocate(_size);
				size_type n = x._size;
				pointer it = x._begin;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_begin + i, *it++);
			}
		}

		~vector(){
				if (_begin != nullptr)
				{
						clear();
						_alloc.deallocate(_begin, capacity());
						_begin = nullptr;
						_size = _capacity = 0;
				}
		}

		vector<T,Allocator>& operator=(const vector<T,Allocator>& x){
			if (this != &x)
				assign(x._begin, x._end);
			return *this;
		}

		template <class InputIter>
		typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type 
		assign(InputIter first, InputIter last){
			clear();
			size_type n = static_cast<size_type>(ft::distance(first, last));
			if (_capacity < n)
				reserve(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_begin + i, *first++);
		}

		void assign(size_type n, const T& x){
			clear();
			if (capacity() < n)
				reserve(n);
			while (n--)
				_alloc.construct(_begin + n, x);
		}

		allocator_type get_allocator() const { return _alloc; }
		
//iterators
		iterator begin() { return (iterator(_begin)); }
		const_iterator begin() const { return (const_iterator(_begin)); }
		iterator end() { return (iterator(_begin + _size)); }
		const_iterator end() const { return (const_iterator(_begin + _size)); }

		reverse_iterator rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

//capacity
		size_type size() const { return _size; }
		size_type max_size() const {return _alloc.max_size(); }
		size_type capacity() const { return _capacity; }
		bool empty() const { return _size == 0; }
		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("bad size vector");
			else if (n > _capacity)
			{
				pointer new_begin = _alloc.allocate(n);
				size_type i = 0;
				try
				{
					for (i = 0; i < _size; i++)
						_alloc.construct(new_begin + i, *(_begin + i));
				}
				catch(...)
				{
					// for (; i < 0; i++)
					// 	_alloc.destroy(new_begin - i);
					_alloc.deallocate(new_begin, n);
					throw ;
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, capacity());
				_begin = new_begin;
			}
		}

		void resize(size_type n, T c = T()){
			size_type sz = size();
			size_type csz = capacity();
			if (csz < n)
			{
				csz = (csz == 0) ? 1 : 2 * csz;
				csz = (n > csz) ? n : csz;
				reserve(csz);
				pointer new_end = _begin + n;
				pointer _end = _begin + sz;
				while (_end != new_end)
				{
					_alloc.construct(_end++, c);
					_size++;
				}
			}
			else if (sz < n)
			{
				pointer _end = _begin + sz;
				pointer new_end = _begin + n;
				while (_end != new_end)
				{
					_alloc.construct(_end++, c);
					_size++;
				}				
			}
			else
			{
				pointer new_end = _begin + n;
				pointer _end = _begin + _size;
				while (_end != new_end)
				{
					_alloc.destroy(--_end);
					_size--;
				}
			}
		}

//element access
		reference       operator[](size_type n){
			assert(n < size() && "vector[] index out of bounds");
			return this->_begin[n]; // *(_begin + n); 	
		}
		const_reference operator[](size_type n) const{
			assert(n < size() && "vector[] index out of bounds");
			return this->_begin[n]; // *(_begin + n); 			
		}
		reference       at(size_type n){
			if (n >= size())
				throw std::out_of_range("vector");
			return this->_begin[n]; // *(_begin + n); 	
		}
		const_reference at(size_type n) const{
			if (n >= size())
				throw std::out_of_range("vector");
			return this->_begin[n]; // *(_begin + n); 	
		}
		reference       front() { return *_begin; }
		const_reference front() const { return *_begin; }
		reference       back() { return *(_begin + _size - 1); }
		const_reference back() const { return *(_begin + _size - 1); }

//Modifiers
		void push_back(const value_type& x){
			size_type csz = capacity();
			if (csz == 0)
				reserve(1);
			else if (_size == _capacity)
				reserve(2 * csz);
			_alloc.construct(_begin + _size, x);
		}

		void pop_back(){
			assert(!empty() && "vector::pop_back called for empty vector");
			_size--;
			_alloc.destroy(_begin + _size);
		}

		iterator insert(const_iterator position, const value_type& x){
			size_type csz = capacity();
			difference_type diff_pos = position - begin();
			pointer __pos = _begin + diff_pos;
			pointer _end = _begin + _size;
			if (_size == _capacity)
			{
				csz = (csz == 0) ? 1 : 2 * csz;
				if (csz > max_size())
					throw std::length_error("bad size vector");
				pointer new_begin, new_end;		
				new_begin = new_end = _alloc.allocate(csz);
				pointer it = _begin;
				try
				{
					while (it != __pos)
						_alloc.construct(new_end++, *it++);
					_alloc.construct(new_end++, x);
					while (it != _end)
						_alloc.construct(new_end++, *it++);
				}
				catch(...)
				{
					_alloc.deallocate(new_begin, csz);
					throw ;
				}
				it = _begin;
				while (it != _end)
					_alloc.destroy(it++);
				_alloc.deallocate(_begin, capacity());
				_begin = new_begin;
				_capacity = csz;
				_size = new_end - new_begin;
				__pos = _begin + diff_pos;
			}
			else
			{
				pointer it = _end;
				_end++;
				while (--it != __pos)
					_alloc.construct(it + 1, *it);
				_alloc.construct(__pos, x);
			}
			return iterator(__pos);
		}

		void insert(const_iterator position, size_type n, const value_type& x){
			size_type csz = capacity();
			size_type n_sz = size() + n;
			difference_type diff_pos = position - begin();
			pointer __pos = _begin + diff_pos;
			pointer _end = _begin + _size;
			pointer _end_cap = _begin + _capacity;
			if (_end == _end_cap || n_sz > csz)
			{
				csz = (csz == 0) ? 1 : 2 * csz;
				csz = (n_sz > csz) ? n_sz : csz;
				if (csz > max_size())
					throw std::length_error("bad size vector");
				pointer new_begin, new_end;		
				new_begin = new_end = _alloc.allocate(csz);
				pointer it = _begin;
				try
				{
					while (it != __pos)
						_alloc.construct(new_end++, *it++);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(new_end++, x);
					while (it != _end)
						_alloc.construct(new_end++, *it++);
				}
				catch(...)
				{
					_alloc.deallocate(new_begin, csz);
					throw ;
				}
				it = _begin;
				while (it != _end)
					_alloc.destroy(it++);
				_alloc.deallocate(_begin, capacity());
				_begin = new_begin;
				_size = new_end - new_begin;
				_capacity = csz;
			}
			else
			{
				pointer it = _end;
				_end += n;
				while (it-- != __pos)
					_alloc.construct(it + n, *it);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(__pos + i, x);
			}
		}

		template <class InputIter>
		// typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type
		void insert(const_iterator position, InputIter first, InputIter last, typename enable_if<!is_integral<InputIter>::value>::type* = 0) {
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector.insert(iterator pos, InputIt first, InputIt last)");
			size_type csz = capacity();
			size_type n = last - first;
			size_type n_sz = size() + n;
			difference_type diff_pos = position - begin();
			pointer __pos = _begin + diff_pos;
			pointer _end = _begin + _size;
			pointer _end_cap = _begin + _capacity;
			if (_end == _end_cap || n_sz > csz)
			{
				csz = (csz == 0) ? 1 : 2 * csz;
				csz = (n_sz > csz) ? n_sz : csz;
				if (csz > max_size())
					throw std::length_error("bad size vector");
				pointer new_begin, new_end;		
				new_begin = new_end = _alloc.allocate(csz);
				pointer it = _begin;
				try
				{
					while (it != __pos)
						_alloc.construct(new_end++, *it++);
					while(first != last)
					{
						_alloc.construct(new_end++, *first);
						*first++;
					}
					while (it != _end)
						_alloc.construct(new_end++, *it++);
				}
				catch(...)
				{
					it = new_begin;
					while (it != new_end)
						_alloc.destroy(it++);
					_alloc.deallocate(new_begin, csz);
					throw ;
				}
				it = _begin;
				while (it != _end)
					_alloc.destroy(it++);
				_alloc.deallocate(_begin, capacity());
				_begin = new_begin;
				_end = new_end;
				_end_cap = _begin + csz;
				__pos = _begin + diff_pos;
			}
			else
			{
				pointer it = _end;
				_end += n;
				while (it-- != __pos)
					_alloc.construct(it + n, *it);
				size_type i = 0;
				while(first != last)
				{
					_alloc.construct(__pos + i, *first);
					*first++;
					i++;
				}	
			}	
		}

		iterator erase(iterator position){
			assert(position != end() &&"vector::erase(iterator) called with a non-dereferenceable iterator");
			difference_type diff_pos = position - begin();
			pointer __pos = _begin + diff_pos;
			pointer it = __pos;
			pointer _end = _begin + _size;
			while (it++ != _end)
				_alloc.construct(it - 1, *it);
			_size--;
			_alloc.destroy(_end);
			return iterator(__pos);			
		}

		iterator erase(iterator first, iterator last){
			difference_type diff_pos = first - begin();
			pointer f_pos = _begin + diff_pos;
			diff_pos = last - begin();
			pointer l_pos = _begin + diff_pos;
			pointer it = l_pos;
			pointer _end = _begin + _size;
			while (it != _end)
				_alloc.construct(f_pos++ , *it++);
			while (first != last--)
				_alloc.destroy(_end--);
			return first;			
		}

		void clear(){
			pointer it = _begin + _size;
			while (_begin != it)
				_alloc.destroy(--it);
			_size = 0;
		}
		
		//?????
		void swap(vector& other){
			if (this != &other)
			{
				std::swap(_begin, other._begin);
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_alloc, other._alloc);
			}
		}
    };

    template <class T, class Allocator> 
	inline bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		const typename vector<T,Allocator>::size_type sz = x.size();
		return sz == y.size() && ft::equal(x.begin(),x.end(), y.begin());
	}
    template <class T, class Allocator>
	inline bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
    template <class T, class Allocator>
	inline bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) { return !(x == y); }
    template <class T, class Allocator>
	inline bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>&y) { return y < x; }
    template <class T, class Allocator>
	inline bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) { return !(x < y); }
    template <class T, class Allocator>
	inline bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) { return !(y < x); }
} // namespace ft

#endif
