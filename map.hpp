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
		// typedef tree_iter<value_type>						iterator;
		// typedef tree_iter<const value_type>					const_iterator;
		// // typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
		// typedef ft::reverse_iterator<iterator>					reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		// typedef reverse_tree_iter<iterator>					reverse_iterator;
		// typedef reverse_tree_iter<const_iterator>			const_reverse_iterator;

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

		typedef typename __base::iterator							iterator;
		typedef typename __base::const_iterator				const_iterator;
		typedef typename __base::reverse_iterator					reverse_iterator;
		typedef typename __base::const_reverse_iterator			const_reverse_iterator;
		// typedef tree_iter<value_type>							iterator;
		// typedef tree_iter<const value_type>					const_iterator;
		// typedef ft::reverse_iterator<iterator>					reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private:
		node_pointer init_node(const value_type& __vt)
		{
			pointer __p_vt = _alloc.allocate(1);
			_alloc.construct(__p_vt, __vt);
			node_allocator _node_alloc;
			node_pointer __node_ptr = _node_alloc.allocate(1);
			_node_alloc.construct(__node_ptr, __p_vt);
			return __node_ptr;
		}

		void destroy_node(node_pointer _node)
		{
			node_allocator _node_alloc;
			if (_node->value)
			{
				_alloc.destroy(_node->value);
				_alloc.deallocate(_node->value, 1);				
			}
			_node_alloc.destroy(_node);
			_node_alloc.deallocate(_node, 1);
		}

	public:

		template <class Key2, class Value2, class Comp2, class Alloc2>
			friend class map;

//construct/copy/destroy:

		explicit map(const key_compare& __comp = key_compare(), const allocator_type& __a = allocator_type())
			: __tree_(value_compare(__comp)), _key_comp(__comp), _alloc(__a) {}

		template< class InputIter >
		map( InputIter first, InputIter last, const key_compare& __comp = Compare(),const allocator_type& __a = Allocator() )
			: __tree_(value_compare(__comp)), _key_comp(__comp), _alloc(__a)
		{
			// std::cout << "IterConstructor" <<std::endl;
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		map(const map& __m) : __tree_(__m.__tree_), _key_comp(__m._key_comp), _alloc(__m._alloc) {}

		~map()
		{
			// std::cout << "~map()" << std::endl;
		}

		map& operator=(const map& __m)
		{
			if (this != &__m) {
				// __tree_.clear();
				__tree_ = __m.__tree_;
			}
			return *this;
		}

		allocator_type get_allocator() const {return _alloc;}

//iterators
		iterator begin() {return iterator(__tree_.begin());}
		const_iterator begin() const {return const_iterator(__tree_.begin());}
		iterator end() {return iterator(__tree_.end());}
		const_iterator end() const {return const_iterator(__tree_.end());}

		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

//capacity
		bool      empty() const {return __tree_.size() == 0;}
		size_type size() const {return __tree_.size();}
		size_type max_size() const {return __tree_.max_size();}

//element access
		mapped_type& operator[](const key_type& __k) {}

		mapped_type& at(const key_type& __k) {}

		const mapped_type& at(const key_type& __k) const {}

//modifiers

		pair<iterator, bool> insert(const value_type& __v) {
			node_pointer node_ptr = init_node(__v);
			node_pointer rez = __tree_.search(node_ptr);
			// std::cout << "insert" << std::endl;
			pair<iterator, bool> ret;
			if (rez != end())
			{
				ret.first = rez;
				ret.second = false;
				destroy_node(node_ptr);
				return ret;
			}
			ret.first = __tree_.insert(node_ptr);
			ret.second = true;
			return ret;
		}

		iterator insert(iterator __p, const value_type& __v){
			(void)__p;
			pair<iterator, bool> rez = insert(__v);
			return rez.first;
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
			node_pointer _nd = __p.base();
			if (__tree_.is_tree_position(_nd))
				__tree_.erase(_nd);
		}

		size_type erase(const key_type& __k) {
			node_pointer node_ptr = init_node(value_type(__k, mapped_type()));
			node_pointer rez = __tree_.search(node_ptr);
			destroy_node(node_ptr);
			if (rez == end())
				return 0;
			__tree_.erase(rez);
			return 1;		
		}

		void  erase(iterator first, iterator last) {
			node_pointer _nd;
			std::cout << "erase\n";
			while (first != last)
			{
				_nd = first.base();
				if (__tree_.is_tree_position(_nd))
					__tree_.erase(_nd);				
				++first;
			}
		}

		void clear() {__tree_.clear();}

		void swap(map& __m) {
			if (this != &__m)
				__tree_.swap(__m.__tree_);
		}

		void print_root(){__tree_.print_root();}

//observers
		key_compare key_comp() const { return _key_comp; }

		value_compare value_comp() const { return __tree_.value_comp(); }

//lookup
		iterator find(const key_type& __k) {
			node_pointer node_ptr = init_node(value_type(__k, mapped_type()));
			node_pointer _rez = __tree_.search(node_ptr);
			destroy_node(node_ptr);
			return iterator(_rez);
		}

		const_iterator find(const key_type& __k) const {}

		size_type count(const key_type& __k) const {
			node_pointer node_ptr = init_node(value_type(__k, mapped_type()));
			node_pointer _rez = __tree_.search(node_ptr);
			destroy_node(node_ptr);
			if (find(__k) != end())
				return 1;
			return 0;
		}

		// iterator lower_bound(const key_type& __k) {}

		// const_iterator lower_bound(const key_type& __k) const {}

		// iterator upper_bound(const key_type& __k) {}

		// const_iterator upper_bound(const key_type& __k) const {}

		// pair<iterator,iterator> equal_range(const key_type& __k) {}

		// pair<const_iterator,const_iterator> equal_range(const key_type& __k) const {}

		friend inline bool operator==(const map& __x, const map& __y)
		{return (ft::equal(__x.begin(), __x.end(), __y.begin()));}
		// { return __x.__tree_ == __y.__tree_;}

		friend inline bool operator< (const map& __x, const map& __y) 
		{ return __x.__tree_ < __y.__tree_; }

	};

// --ready--

// template <class Key, class T, class Compare, class Allocator>
// inline bool operator==(const map<Key, T, Compare, Allocator>& __x,
//            const map<Key, T, Compare, Allocator>& __y) 
// { return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin()); }

// template <class Key, class T, class Compare, class Allocator>
// inline bool operator< (const map<Key, T, Compare, Allocator>& __x,
//            const map<Key, T, Compare, Allocator>& __y) 
// { return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()); }

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