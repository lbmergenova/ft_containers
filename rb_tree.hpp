#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "utility.hpp"
#include "iterator_traits.hpp"
#include "tree_iterator.hpp"
#include <memory>

namespace ft
{
	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class rb_tree
	{
	public:
		// types:
		typedef T											value_type;
		typedef Compare										value_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		
		typedef typename allocator_type::template
		rebind<Node<value_type> >::other					node_allocator;
		typedef	typename node_allocator::pointer			node_pointer;
		typedef typename node_allocator::const_pointer		node_const_pointer;
		typedef typename node_allocator::reference			node_reference;
		typedef typename node_allocator::const_reference	node_const_reference;


	private:
		node_allocator													_node_alloc;
		value_compare 													_compare;
		node_pointer													_begin_node;
		node_pointer													_end_node;
		node_pointer													_root;
		size_type														_size;

	public:

//construct/copy/destroy:
	rb_tree() : {} //???
    rb_tree(const rb_tree& __t);
	rb_tree& operator=(const rb_tree& __m)
		{
			if (this != &__m) {
				__tree_.clear();
				__tree_.value_comp() = __m.__tree_.value_comp();
				__tree_.__copy_assign_alloc(__m.__tree_);
				insert(__m.begin(), __m.end());
			}
			return *this;
		}

	~tree(){} //???
// ___________________________________

    __iter_pointer                                     __begin_node_;
    __compressed_pair<__end_node_t, __node_allocator>  __pair1_;
    __compressed_pair<size_type, value_compare>        __pair3_;

public:
    _LIBCPP_INLINE_VISIBILITY
    __iter_pointer __end_node() _NOEXCEPT
    {
        return static_cast<__iter_pointer>(
                pointer_traits<__end_node_ptr>::pointer_to(__pair1_.first())
        );
    }
    _LIBCPP_INLINE_VISIBILITY
    __iter_pointer __end_node() const _NOEXCEPT
    {
        return static_cast<__iter_pointer>(
            pointer_traits<__end_node_ptr>::pointer_to(
                const_cast<__end_node_t&>(__pair1_.first())
            )
        );
    }
    _LIBCPP_INLINE_VISIBILITY
          __node_allocator& __node_alloc() _NOEXCEPT {return __pair1_.second();}
private:
    _LIBCPP_INLINE_VISIBILITY
    const __node_allocator& __node_alloc() const _NOEXCEPT
        {return __pair1_.second();}
    _LIBCPP_INLINE_VISIBILITY
          __iter_pointer& __begin_node() _NOEXCEPT {return __begin_node_;}
    _LIBCPP_INLINE_VISIBILITY
    const __iter_pointer& __begin_node() const _NOEXCEPT {return __begin_node_;}




template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const value_compare& __comp)
        _NOEXCEPT_(
            is_nothrow_default_constructible<__node_allocator>::value &&
            is_nothrow_copy_constructible<value_compare>::value)
    : __pair3_(0, __comp)
{
    __begin_node() = __end_node();
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const allocator_type& __a)
    : __begin_node_(__iter_pointer()),
      __pair1_(__second_tag(), __node_allocator(__a)),
      __pair3_(0)
{
    __begin_node() = __end_node();
}

template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::__tree(const value_compare& __comp,
                                           const allocator_type& __a)
    : __begin_node_(__iter_pointer()),
      __pair1_(__second_tag(), __node_allocator(__a)),
      __pair3_(0, __comp)
{
    __begin_node() = __end_node();
}



__tree<_Tp, _Compare, _Allocator>::~__tree()
{
    static_assert((is_copy_constructible<value_compare>::value),
                 "Comparator must be copy-constructible.");
  destroy(__root());
}

template <class _Tp, class _Compare, class _Allocator>
void
__tree<_Tp, _Compare, _Allocator>::destroy(__node_pointer __nd) _NOEXCEPT
{
    if (__nd != nullptr)
    {
        destroy(static_cast<__node_pointer>(__nd->__left_));
        destroy(static_cast<__node_pointer>(__nd->__right_));
        __node_allocator& __na = __node_alloc();
        __node_traits::destroy(__na, _NodeTypes::__get_ptr(__nd->__value_));
        __node_traits::deallocate(__na, __nd, 1);
    }
}

// ___________________________________


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

		void swap(rb_tree& __m) {__tree_.swap(__m.__tree_);}

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

	};
   
} // namespace ft

#endif