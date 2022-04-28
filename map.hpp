#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "RBTree.hpp"

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
		typedef __map_iterator<typename __base::iterator>		     iterator;
		typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		class value_compare : public binary_function<value_type, value_type, bool>
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

		typedef _VSTD::__value_type<key_type, mapped_type>		     __value_type;
		typedef __map_value_compare<key_type, __value_type, key_compare> __vc;
		typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>, __value_type>::type __allocator_type;
		typedef __tree<__value_type, __vc, __allocator_type>   __base;

		__base __tree_;

	public:

		template <class Key2, class Value2, class Comp2, class Alloc2>
			friend class map;
//construct/copy/destroy:
		map() : __tree_(__vc(key_compare())) {}

		explicit map(const key_compare& __comp, const allocator_type& __a = Allocator())
			: __tree_(__vc(__comp), typename __base::allocator_type(__a)) {}

		template< class InputIter >
		map( InputIter first, InputIter last,
			const key_compare& __comp = Compare(),
			const allocator_type& __a = Allocator() )
			: __tree_(__vc(__comp), typename __base::allocator_type(__a))
			{
				insert(__f, __l);
			}

		map(const map& __m)
			: __tree_(__m.__tree_)
			{
				insert(__m.begin(), __m.end());
			}

		map& operator=(const map& __m)
			{
				if (this != &__m) {
					__tree_.clear();
					__tree_.value_comp() = __m.__tree_.value_comp();
					__tree_.__copy_assign_alloc(__m.__tree_);
					insert(__m.begin(), __m.end());
				}
				return *this;
			}

		allocator_type get_allocator() const {return allocator_type(__tree_.__alloc());}

//iterators
		iterator begin() {return __tree_.begin();}
		const_iterator begin() const {return __tree_.begin();}
		iterator end() {return __tree_.end();}
		const_iterator end() const {return __tree_.end();}

		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

//capacity
		bool      empty() const {return __tree_.size() == 0;}
		size_type size() const {return __tree_.size();}
		size_type max_size() const {return __tree_.max_size();}

//element access
		mapped_type& operator[](const key_type& __k);

		mapped_type& at(const key_type& __k);
		const mapped_type& at(const key_type& __k) const;

//modifiers


		key_compare    key_comp()      const {return __tree_.value_comp().key_comp();}

		value_compare  value_comp()    const {return value_compare(__tree_.value_comp().key_comp());}

		pair<iterator, bool> insert(const value_type& __v)
			{return __tree_.__insert_unique(__v);}

		iterator insert(const_iterator __p, const value_type& __v)
			{return __tree_.__insert_unique(__p.__i_, __v);}

		template <class InputIter>
		void insert(InputIter __f, InputIter __l)
		{
			for (const_iterator __e = cend(); __f != __l; ++__f)
				insert(__e.__i_, *__f);
		}

		iterator erase(const_iterator __p) {return __tree_.erase(__p.__i_);}

		iterator erase(iterator __p)       {return __tree_.erase(__p.__i_);}

		size_type erase(const key_type& __k)
			{return __tree_.__erase_unique(__k);}

		iterator  erase(const_iterator __f, const_iterator __l)
			{return __tree_.erase(__f.__i_, __l.__i_);}

		void clear() {__tree_.clear();}

		void swap(map& __m) {__tree_.swap(__m.__tree_);}

//lookup
		iterator find(const key_type& __k)		     {return __tree_.find(__k);}

		const_iterator find(const key_type& __k) const {return __tree_.find(__k);}

		size_type count(const key_type& __k) const
			{return __tree_.__count_unique(__k);}

		iterator lower_bound(const key_type& __k)
			{return __tree_.lower_bound(__k);}

		const_iterator lower_bound(const key_type& __k) const
			{return __tree_.lower_bound(__k);}

		iterator upper_bound(const key_type& __k)
			{return __tree_.upper_bound(__k);}

		const_iterator upper_bound(const key_type& __k) const
			{return __tree_.upper_bound(__k);}

		pair<iterator,iterator> equal_range(const key_type& __k)
			{return __tree_.__equal_range_unique(__k);}

		pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
			{return __tree_.__equal_range_unique(__k);}

	private:
		typedef typename __base::__node				    __node;
		typedef typename __base::__node_allocator		  __node_allocator;
		typedef typename __base::__node_pointer		    __node_pointer;
		typedef typename __base::__node_base_pointer       __node_base_pointer;
		typedef typename __base::__parent_pointer		  __parent_pointer;

		typedef __map_node_destructor<__node_allocator> _Dp;
		typedef unique_ptr<__node, _Dp> __node_holder;

	};

template <class Key, class T, class Compare, class Allocator>
inline bool
operator==(const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y)
{
    return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
}

template <class Key, class T, class Compare, class Allocator>
inline bool
operator< (const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y)
{
    return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class Key, class T, class Compare, class Allocator>
inline bool
operator!=(const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y)
{
    return !(__x == __y);
}

template <class Key, class T, class Compare, class Allocator>
inline bool
operator> (const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y)
{
    return __y < __x;
}

template <class Key, class T, class Compare, class Allocator>
inline bool
operator>=(const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y)
{
    return !(__x < __y);
}

template <class Key, class T, class Compare, class Allocator>
inline bool
operator<=(const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y)
{
    return !(__y < __x);
}

} // namespace ft

namespace std
{
	template <class Key, class T, class Compare, class Allocator>
	inline void
	swap(map<Key, T, Compare, Allocator>& __x, map<Key, T, Compare, Allocator>& __y)
	{
		__x.swap(__y);
	}
} // namespace std


#endif