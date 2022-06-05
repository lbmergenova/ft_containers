#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cassert>
#include "utility.hpp"
#include "iterator_traits.hpp"

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
		pointer				_end;
		pointer				_end_cap;

//construct/copy/destroy:
	public:
		explicit vector(const Allocator& _a = Allocator()) : _alloc(_a), _begin(nullptr), _end(nullptr), _end_cap(nullptr) {}

		explicit vector(size_type n, const T& value = T(), const Allocator& _a= Allocator()) : _alloc(_a), _begin(nullptr), _end(nullptr), _end_cap(nullptr){
			if (n > _alloc.max_size())
				throw std::length_error("bad size vector");
			else if (n > 0)
			{
				_begin = _end = _alloc.allocate(n);
				while (n--)
					_alloc.construct(_end++, value);
				_end_cap = _end;
			}
		}

		template <class InputIter>
		vector(InputIter __first, InputIter __last, const Allocator& _a = Allocator(), 
		       typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type* = 0) //?????
			   : _begin(nullptr), _end(nullptr), _end_cap(nullptr), _alloc(_a)
		{
			size_type n = __last - __first;
			if (n > max_size())
				throw std::length_error("bad size vector");
			_begin = _end = _alloc.allocate(n);
			while (n--)
				_alloc.construct(_end++, *__first++);
			_end_cap = _end;
		}

		vector(const vector<T,Allocator>& x) : _alloc(x.get_allocator()), _begin(nullptr), _end(nullptr), _end_cap(nullptr){
			size_type n = x.size();
			pointer it = x._begin;
			if (n > 0)
			{
				_begin = _end = _alloc.allocate(n);
				while (it != x._end)
					_alloc.construct(_end++, *it++);
				_end_cap = _end;
			}
		}

		~vector(){
				if (_begin != nullptr)
				{
						clear();
						_alloc.deallocate(_begin, capacity());
						_begin = _end = _end_cap = nullptr;
				}
		}

		vector<T,Allocator>& operator=(const vector<T,Allocator>& x){
			if (this != &x)
			{
				size_type new_csz = x.capacity();
				size_type new_sz = x.size();
				if (capacity() != 0)
				{
					clear();
					_alloc.deallocate(_begin, capacity());
				}
				if (new_csz > 0)
					_begin = _end = _alloc.allocate(new_csz);
				_end_cap = _begin + new_csz;
				pointer it = x._begin;
				while (new_sz--)
					_alloc.construct(_end++, *it++);
			}
				return (*this);
		}

		template <class InputIter>
		typename ft::enable_if<!ft::is_integral<InputIter>::value, void>::type 
		assign(InputIter first, InputIter last){
			clear();
			size_type n = last - first;
			if (capacity() < n)
				reserve(n);
			while (first != last)
				_alloc.construct(_end++, *first++);
		}

		void assign(size_type n, const T& x){
			clear();
			if (capacity() < n)
				reserve(n);
			while (n--)
				_alloc.construct(_end++, x);
		}

		allocator_type get_allocator() const { return _alloc; }
		
//iterators
		iterator begin() { return (iterator(_begin)); }
		const_iterator begin() const { return (const_iterator(_begin)); }
		iterator end() { return (iterator(_end)); }
		const_iterator end() const { return (const_iterator(_end)); }

		reverse_iterator rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

//capacity
		size_type size() const { return static_cast<size_type>(_end - _begin); }
		size_type max_size() const {return _alloc.max_size(); }
		size_type capacity() const { return (_end_cap - _begin); }
		bool empty() const { return _begin == _end; }
		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("bad size vector");
			else if (n > capacity())
			{
				pointer new_begin, new_end;		
				new_begin = new_end = _alloc.allocate(n);
				pointer it = _begin;
				try
				{
					while (it != _end)
						_alloc.construct(new_end++, *it++);
				}
				catch(...)
				{
					_alloc.deallocate(new_begin, n);
					throw ;
				}
				it = _begin;
				while (it != _end)
					_alloc.destroy(it++);
				_alloc.deallocate(_begin, capacity());
				_begin = new_begin;
				_end = new_end;
				_end_cap = _begin + n;
			}
		}

		void resize(size_type n, T c = T()){
			size_type sz = size();
			size_type csz = capacity();
			if (n < sz)
			{
				while (sz-- > n)
					_alloc.destroy(--_end);
			}
			else if (n > sz)
			{
				if (csz < n)
					reserve(2 * csz > n ? 2 * csz : n);
				while (sz++ < n)
					_alloc.construct(_end++, c);				
			}
		}

//element access
		reference       operator[](size_type n){
			assert(n < size() && "vector[] index out of bounds");
			return _begin[n]; // *(_begin + n); 	
		}
		const_reference operator[](size_type n) const{
			assert(n < size() && "vector[] index out of bounds");
			return _begin[n]; // *(_begin + n); 			
		}
		reference       at(size_type n){
			if (n >= size())
				throw std::out_of_range("vector");
			return _begin[n]; // *(_begin + n); 	
		}
		const_reference at(size_type n) const{
			if (n >= size())
				throw std::out_of_range("vector");
			return _begin[n]; // *(_begin + n); 	
		}
		reference       front() { return *_begin; }
		const_reference front() const { return *_begin; }
		reference       back() { return *(_end - 1); }
		const_reference back() const { return *(_end - 1); }

//modifiers
		void push_back(const value_type& x){
			size_type csz = capacity();
			if (csz == 0)
				reserve(1);
			else if (_end == _end_cap)
				reserve(2 * csz);
			_alloc.construct(_end++, x);
		}

		void pop_back(){
			assert(!empty() && "vector::pop_back called for empty vector");
			_alloc.destroy(--_end);
		}

		iterator insert(const_iterator position, const value_type& x){
			size_type csz = capacity();
			difference_type diff_pos = position - begin();
			pointer __pos = _begin + diff_pos;
			if (_end == _end_cap)
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
				_end = new_end;
				_end_cap = _begin + csz;
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
				_end = new_end;
				_end_cap = _begin + csz;
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
		void insert(const_iterator position, InputIter first, InputIter last, typename enable_if<!is_integral<InputIter>::value>::type* = 0) {
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector.insert(iterator pos, InputIt first, InputIt last)");
			size_type csz = capacity();
			size_type n = last - first;
			size_type n_sz = size() + n;
			difference_type diff_pos = position - begin();
			pointer __pos = _begin + diff_pos;
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
			while (it++ != _end)
				_alloc.construct(it - 1, *it);
			_end--;
			_alloc.destroy(_end);
			return iterator(__pos);			
		}

		// iterator erase (iterator position)
        // {
        //     size_t i_pos = position - begin();
		// 	size_t _size = _end - _begin;

        //     for(size_t i = i_pos; i < _size; ++i)
        //         _begin[i] = _begin[i+1];
        //     _alloc.destroy(_begin + _size - 1);
        //     _end--;
        //     return iterator(_begin + i_pos);
        // }

		iterator erase(iterator first, iterator last){
			difference_type diff_pos = first - begin();
			pointer f_pos = _begin + diff_pos;
			diff_pos = last - begin();
			pointer l_pos = _begin + diff_pos;
			pointer it = l_pos;
			while (it != _end)
				_alloc.construct(f_pos++ , *it++);
			while (first != last--)
				_alloc.destroy(_end--);
			return first;			
		}

		void clear(){
			while (_begin != _end)
				_alloc.destroy(--_end);
		}
		
		void swap(vector& other){
			if (this != &other)
			{
				std::swap(_begin, other._begin);
				std::swap(_end, other._end);
				std::swap(_end_cap, other._end_cap);
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

namespace std
{
	template<class T, class Alloc>
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
