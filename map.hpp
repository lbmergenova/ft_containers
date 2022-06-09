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
		typedef tree_iter<value_type>						iterator;
		// typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
		// typedef ft::reverse_iterator<iterator>				reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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

		typedef rb_tree<value_type, value_compare, allocator_type>   __base;
		// typedef typename __base::node_pointer						node_poiner;

		__base			__tree_;
		key_compare		_key_comp;
		allocator_type	_alloc;

	public:

		// typedef typename __base::iterator					iterator;
		// typedef tree_iter<typename __base::node_pointer>		iterator;

		template <class Key2, class Value2, class Comp2, class Alloc2>
			friend class map;
//construct/copy/destroy:
		// map() : __tree_(), _key_comp(), _alloc() {}

		explicit map(const key_compare& __comp = key_compare(), const allocator_type& __a = allocator_type())
			: __tree_(value_compare(__comp)), _key_comp(__comp), _alloc(__a) {}

		template< class InputIter >
		map( InputIter first, InputIter last, const key_compare& __comp = Compare(),const allocator_type& __a = Allocator() )
			: __tree_(value_compare(__comp)), _key_comp(__comp), _alloc(__a)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		// map(const map& __m) : __tree_(__m.__tree_), _key_comp(__m._key_comp), _alloc(__m._alloc)
		// {
		// 	insert(__m.begin(), __m.end());
		// }

		map& operator=(const map& __m)
		{
			if (this != &__m) {
				__tree_.clear();
				insert(__m.begin(), __m.end());
			}
			return *this;
		}

		allocator_type get_allocator() const {return _alloc;}

//iterators
		iterator begin() {return iterator(__tree_.begin(), __tree_.get_root());}
		// const_iterator begin() const {return __tree_.begin();}
		iterator end() {return iterator(__tree_.end(), __tree_.get_root());}
		// const_iterator end() const {return __tree_.end();}

		// reverse_iterator rbegin() {return reverse_iterator(end());}
		// const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		// reverse_iterator rend() {return reverse_iterator(begin());}
		// const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

//capacity
		bool      empty() const {return __tree_.size() == 0;}
		size_type size() const {return __tree_.size();}
		size_type max_size() const {return __tree_.max_size();}

//element access
		mapped_type& operator[](const key_type& __k)
		{
			value_type _vt(__k, T());
			node_pointer node_ptr = init_node(_vt);
			node_pointer __find = __tree_.find(node_ptr);
			if (__find == nullptr)
			{
				pair<node_pointer, bool> rez = __tree_.insert(node_ptr);
				return rez.first->value->second;
			}
			else
			{
				destroy_node(node_ptr);
				return __find->value->second; 
			}
		}

		mapped_type& at(const key_type& __k){
			value_type _vt(__k, T());
			node_pointer node_ptr = init_node(_vt);
			node_pointer __find = __tree_.find(node_ptr);
			if (__find == nullptr)
				throw std::out_of_range("map::at:  key not found");
			destroy_node(node_ptr);
			return __find->value->second;
		}

		const mapped_type& at(const key_type& __k) const{
			value_type _vt(__k, T());
			node_pointer node_ptr = init_node(_vt);
			node_pointer __find = __tree_.find(node_ptr);
			if (__find == nullptr)
				throw std::out_of_range("map::at:  key not found");
			destroy_node(node_ptr);
			return __find->value->second;			
		}

//modifiers


		key_compare    key_comp()      const {return _key_comp;}

		// value_compare  value_comp()    const {return value_compare(__tree_.value_comp().key_comp());}

		pair<iterator, bool> insert(const value_type& __v) {
		// void insert(const value_type& __v) { 
			node_pointer node_ptr = init_node(__v);
			pair<node_pointer, bool> ret = __tree_.insert(node_ptr);
			if (!ret.second)
				destroy_node(node_ptr);
			// std::cout << "insert map" << std::endl;
			pair<iterator, bool> rez(iterator(ret.first, __tree_.get_root()), ret.second);
			return rez;
		}

		void tree_print(void)
		{
			__tree_.tree_print();
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

		// iterator erase(const_iterator __p) {return __tree_.erase(__p.__i_);}

		// iterator erase(iterator __p)       {return __tree_.erase(__p.__i_);}

		size_type erase(const key_type& __k)
		{
			// if (size() == 0)
			// 	return 0;
			value_type _vt(__k, T());
			node_pointer node_ptr = init_node(_vt);
			node_pointer _find = __tree_.find(node_ptr);
			destroy_node(node_ptr);
			if (_find == nullptr)
			{
				return 0;
			}
			__tree_.erase(_find);
			// destroy_node(_find);
			return 1;
		}

		// iterator  erase(const_iterator __f, const_iterator __l)
		// 	{return __tree_.erase(__f.__i_, __l.__i_);}

		void clear() {__tree_.clear();}

		void swap(map& __m) {__tree_.swap(__m.__tree_);}
		

//lookup
		iterator find(const key_type& __k){
			value_type _vt(__k, T());
			node_pointer node_ptr = init_node(_vt);
			node_pointer ret = __tree_.find(node_ptr);
			destroy_node(node_ptr);
			return iterator(ret, __tree_.get_root());
		}

		// const_iterator find(const key_type& __k) const {return __tree_.find(__k);}

		size_type count(const key_type& __k) const
			{return __tree_.__count_unique(__k);}

		iterator lower_bound(const key_type& __k)
			{return __tree_.lower_bound(__k);}

		// const_iterator lower_bound(const key_type& __k) const
		// 	{return __tree_.lower_bound(__k);}

		iterator upper_bound(const key_type& __k)
			{return __tree_.upper_bound(__k);}

		// const_iterator upper_bound(const key_type& __k) const
		// 	{return __tree_.upper_bound(__k);}

		pair<iterator,iterator> equal_range(const key_type& __k)
			{return __tree_.__equal_range_unique(__k);}

		// pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
		// 	{return __tree_.__equal_range_unique(__k);}

	private:
		typedef typename __base::node_allocator			 	__node_allocator;
		typedef typename __base::node_type				 	__node_type;
		typedef typename __base::node_pointer			 	node_pointer;


		node_pointer init_node(const value_type& __vt)
		{
			pointer __p_vt = _alloc.allocate(1);
			_alloc.construct(__p_vt, __vt);
			__node_allocator _node_alloc;
			node_pointer __node_ptr = _node_alloc.allocate(1);
			_node_alloc.construct(__node_ptr, __p_vt);
			return __node_ptr;
		}

		void destroy_node(node_pointer _node)
		{
			__node_allocator _node_alloc;
			_node_alloc.destroy(_node);
			_node_alloc.deallocate(_node, 1);
		}
	// 	typedef typename __base::__node_allocator		  __node_allocator;
	// 	typedef typename __base::__node_pointer		    __node_pointer;
	// 	typedef typename __base::__node_base_pointer       __node_base_pointer;
	// 	typedef typename __base::__parent_pointer		  __parent_pointer;

	// 	typedef __map_node_destructor<__node_allocator> _Dp;
	// 	typedef unique_ptr<__node, _Dp> __node_holder;

	};

// --ready--

template <class Key, class T, class Compare, class Allocator>
inline bool operator==(const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y) 
{ return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin()); }

template <class Key, class T, class Compare, class Allocator>
inline bool operator< (const map<Key, T, Compare, Allocator>& __x,
           const map<Key, T, Compare, Allocator>& __y) 
{ return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()); }

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