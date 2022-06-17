#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "rb_tree.hpp"
#include "tree_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{

	public:
		// types:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c) {}
		public:
			bool operator()(const value_type& __x, const value_type& __y) const
				{return comp(__x.first, __y.first);}
		};

	private:

		typedef rb_tree<value_type, value_compare, allocator_type>	__base;
		typedef typename __base::node_allocator						node_allocator;
		typedef typename __base::node_pointer						node_pointer;
		typedef typename __base::node_const_pointer					node_const_pointer;

		__base			__tree_;
		key_compare		_key_comp;
		allocator_type	_alloc;

	public:
		typedef typename __base::iterator				 	iterator;
		typedef typename __base::const_iterator			 	const_iterator;
		typedef typename __base::reverse_iterator		 	reverse_iterator;
		typedef typename __base::const_reverse_iterator	 	const_reverse_iterator;

//construct/copy/destroy:

		explicit map(const key_compare& __comp = key_compare(), const allocator_type& __a = allocator_type())
			: __tree_(value_compare(__comp)), _key_comp(__comp), _alloc(__a) {}

		template< class InputIter >
		map( InputIter first, InputIter last, const key_compare& __comp = Compare(),const allocator_type& __a = Allocator() )
			: __tree_(value_compare(__comp)), _key_comp(__comp), _alloc(__a)
		{ insert(first, last); }

		map(const map& __m) : __tree_(__m.__tree_), _key_comp(__m._key_comp), _alloc(__m._alloc) {}

		~map() {}

		map& operator=(const map& __m)
		{
			if (this != &__m)
			{
				__tree_ = __m.__tree_;
				_key_comp = __m._key_comp;
				_alloc = __m._alloc;
			}
			return *this;
		}

		allocator_type get_allocator() const {return _alloc;}

//iterators
		iterator begin() {return __tree_.begin();}
		const_iterator begin() const {return __tree_.begin();}
		iterator end() {return __tree_.end();}
		const_iterator end() const {return __tree_.end();}

		reverse_iterator rbegin() {return __tree_.rbegin();}
		const_reverse_iterator rbegin() const {return __tree_.rbegin();}
		reverse_iterator rend() {return __tree_.rend();}
		const_reverse_iterator rend() const {return __tree_.rend();}

//capacity
		bool empty() const {return __tree_.size() == 0;}
		size_type size() const {return __tree_.size();}
		size_type max_size() const {return __tree_.max_size();}

//element access

		mapped_type& operator[](const key_type& __k)
		{
			iterator it = find(__k);
			if (it == end())
				return insert(value_type(__k, mapped_type())).first->second;
			return it->second;
		}

		mapped_type& at(const key_type& __k){
			iterator it = find(__k);
			if (it == end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;
		}

		const mapped_type& at(const key_type& __k) const{
			iterator it = find(__k);
			if (it == end())
				throw std::out_of_range("map::at:  key not found");
			return it->second;		
		}

//modifiers

		pair<iterator, bool> insert(const value_type& __v) {
			return __tree_.insert(__v);
		}

		iterator insert(iterator __p, const value_type& __v){
			(void) __p;
			return insert(__v).first;;
		}

		template <class InputIter>
		void insert(InputIter first, InputIter last){
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase(iterator __p) {
			__tree_.erase(__p.base());
		}

		size_type erase(const key_type& __k) {
			iterator rez = __tree_.search(value_type(__k, mapped_type()));
			if (rez == end())
				return 0;
			__tree_.erase(rez.base());
			return 1;		
		}

		void  erase(iterator first, iterator last) {
			key_type __k;
			while (first != last)
			{
				__k = first->first;
				++first;
				erase(__k);				
			}
		}

		void clear() {__tree_.clear();}

		void swap(map& __m) {
			if (this != &__m)
				__tree_.swap(__m.__tree_);
		}

//observers
		key_compare key_comp() const { return _key_comp; }

		value_compare value_comp() const { return value_compare(_key_comp); }

//lookup
		iterator find(const key_type& __k) {
			return iterator(__tree_.search(value_type(__k, mapped_type())));
		}

		const_iterator find(const key_type& __k) const {
			return const_iterator(__tree_.search(value_type(__k, mapped_type())));
		}

		size_type count(const key_type& __k) const {
			if (const_iterator(__tree_.search(value_type(__k, mapped_type()))) != end())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type& __k) {return __tree_.lower_bound(value_type(__k, mapped_type()));}

		const_iterator lower_bound(const key_type& __k) const {return __tree_.lower_bound(value_type(__k, mapped_type()));}

		iterator upper_bound(const key_type& __k) {return __tree_.upper_bound(value_type(__k, mapped_type()));}

		const_iterator upper_bound(const key_type& __k) const {return __tree_.upper_bound(value_type(__k, mapped_type()));}

		pair<iterator,iterator> equal_range(const key_type& __k) {
			return ft::pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
		}

		pair<const_iterator,const_iterator> equal_range(const key_type& __k) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
		}

		friend inline bool operator==(const map& __x, const map& __y)
		{ return __x.__tree_ == __y.__tree_;}

		friend inline bool operator< (const map& __x, const map& __y) 
		{ return __x.__tree_ < __y.__tree_; }

	};

// --ready--

	template <class Key, class T, class Compare, class Allocator>
	inline bool operator!=(const map<Key, T, Compare, Allocator>& __x,
		   const map<Key, T, Compare, Allocator>& __y)
	{ return !(__x == __y); }

	template <class Key, class T, class Compare, class Allocator>
	inline bool operator> (const map<Key, T, Compare, Allocator>& __x,
			   const map<Key, T, Compare, Allocator>& __y)
	{ return __y < __x; }
	
	template <class Key, class T, class Compare, class Allocator>
	inline bool operator>=(const map<Key, T, Compare, Allocator>& __x,
			   const map<Key, T, Compare, Allocator>& __y)
	{ return !(__x < __y); }
	
	template <class Key, class T, class Compare, class Allocator>
	inline bool operator<=(const map<Key, T, Compare, Allocator>& __x,
			   const map<Key, T, Compare, Allocator>& __y)
	{ return !(__y < __x); }

} // namespace ft

namespace std
{
	template <class Key, class T, class Compare, class Allocator>
	inline void swap(ft::map<Key, T, Compare, Allocator>& __x, ft::map<Key, T, Compare, Allocator>& __y)
	{
		__x.swap(__y);
	}
} // namespace std


#endif