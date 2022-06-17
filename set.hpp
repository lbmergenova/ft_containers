#ifndef set_HPP
#define set_HPP

#include "pair.hpp"
#include "rb_tree.hpp"
#include "tree_iterator.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>,
			class Allocator = std::allocator<Key> >
	class set
	{

	public:
		// types:
		typedef Key											value_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

	private:

		typedef rb_tree<value_type, key_compare, allocator_type>	__base;
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

		explicit set(const key_compare& __comp = key_compare(), const allocator_type& __a = allocator_type())
			: __tree_(), _key_comp(__comp), _alloc(__a) {}

		template< class InputIter >
		set( InputIter first, InputIter last, const key_compare& __comp = Compare(),const allocator_type& __a = Allocator() )
			: __tree_(), _key_comp(__comp), _alloc(__a)
		{ insert(first, last); }

		set(const set& __m) : __tree_(__m.__tree_), _key_comp(__m._key_comp), _alloc(__m._alloc) {}

		~set() {}

		set& operator=(const set& __m)
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

		size_type erase(const value_type& __v) {
			iterator rez = __tree_.search(__v);
			// std::cout << "erase\n";
			if (rez == end())
				return 0;
			__tree_.erase(rez.base());
			// std::cout << "erase end\n";
			return 1;		
		}

		void  erase(iterator first, iterator last) {
			value_type __v;
			while (first != last)
			{
				__v = *first;
				++first;
				erase(__v);				
			}
		}

		void clear() {__tree_.clear();}

		void swap(set& __m) {
			if (this != &__m)
				__tree_.swap(__m.__tree_);
		}

//observers
		key_compare key_comp() const { return _key_comp; }

//lookup
		iterator find(const value_type& __v) {
			return iterator(__tree_.search(__v));
		}

		const_iterator find(const value_type& __v) const {
			return const_iterator(__tree_.search(__v));
		}

		size_type count(const value_type& __v) const {
			if (const_iterator(__tree_.search(__v)) != end())
				return 1;
			return 0;
		}

		iterator lower_bound(const value_type& __v) {return __tree_.lower_bound(__v);}

		const_iterator lower_bound(const value_type& __v) const {return __tree_.lower_bound(__v);}

		iterator upper_bound(const value_type& __v) {return __tree_.upper_bound(__v);}

		const_iterator upper_bound(const value_type& __v) const {return __tree_.upper_bound(__v);}

		pair<iterator,iterator> equal_range(const value_type& __v) {
			return ft::pair<iterator, iterator>(lower_bound(__v), upper_bound(__v));
		}

		pair<const_iterator,const_iterator> equal_range(const value_type& __v) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(__v), upper_bound(__v));
		}

		friend inline bool operator==(const set& __x, const set& __y)
		{ return __x.__tree_ == __y.__tree_;}

		friend inline bool operator< (const set& __x, const set& __y) 
		{ return __x.__tree_ < __y.__tree_; }

	};

// --ready--

	template <class Key, class Compare, class Allocator>
	inline bool operator!=(const set<Key, Compare, Allocator>& __x,
		   const set<Key, Compare, Allocator>& __y)
	{ return !(__x == __y); }

	template <class Key, class Compare, class Allocator>
	inline bool operator> (const set<Key, Compare, Allocator>& __x,
			   const set<Key, Compare, Allocator>& __y)
	{ return __y < __x; }
	
	template <class Key, class Compare, class Allocator>
	inline bool operator>=(const set<Key, Compare, Allocator>& __x,
			   const set<Key, Compare, Allocator>& __y)
	{ return !(__x < __y); }
	
	template <class Key, class Compare, class Allocator>
	inline bool operator<=(const set<Key, Compare, Allocator>& __x,
			   const set<Key, Compare, Allocator>& __y)
	{ return !(__y < __x); }

} // namespace ft

namespace std
{
	template <class Key, class Compare, class Allocator>
	inline void swap(ft::set<Key, Compare, Allocator>& __x, ft::set<Key, Compare, Allocator>& __y)
	{
		__x.swap(__y);
	}
} // namespace std


#endif