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
		typedef typename node_allocator::size_type			node_size_type;
		typedef typename tree_iteraor<node_pointer>			iterator;
		typedef typename tree_iteraor<node_const_pointer>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


	private:
		node_allocator													_node_alloc;
		value_compare 													_compare;
		node_pointer													_begin_node;
		node_pointer													_end_node;
		node_pointer													_root;
		node_size_type													_size;

	public:

	//construct/copy/destroy:
		rb_tree() : {} //???
		// rb_tree(const rb_tree& __t);  // **** need to write
		rb_tree& operator=(const rb_tree& __m)
			{
				if (this != &__m) {
					clear();
					_compare = __m._compare;
					// __tree_.__copy_assign_alloc(__m.__tree_);
					// insert(__m.begin(), __m.end());
				}
				return *this;
			}

		~tree(){
			destroy(_root);  // **** need to write
		} //???

	//iterators
			iterator begin() {return _begin_node;}
			const_iterator begin() const {return _begin_node;}
			iterator end() {return _end_node;}
			const_iterator end() const {return _end_node;}

			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

	//capacity
			bool      empty() const {return _size == 0;}
			size_type size() const {return _size;}
			size_type max_size() const {return _node_alloc.max_size();}


	// //rotates

		void rotate_left(node_pointer __x)
		{
			node_pointer __y = __x->right;
			__x->right = __y->left;
			if (__y->left != nullptr)
				__y->left->parent = __x;
			__y->parent = __x->parent;
			if (__x->parent == nullptr)
				_root = __y;
			else if (__x == __x->parent->left)
				__x->parent->left = __y;
			else
				__x->parent->right = __y;
			__y->left = __x;
			__x->parent = __y;
		}

		void rotate_right(node_pointer __x)
		{
			node_pointer __y = __x->left;
			__x->left = __y->right;
			if (__y->right != nullptr)
				__y->right->parent = __x;
			__y->parent = __x->parent;
			if (__x->parent == nullptr)
				_root = __y;
			else if (__x == __x->parent->left)
				__x->parent->left = __y;
			else
				__x->parent->right = __y;
			__y->right = __x;
			__x->parent = __y;
		}

		void insert(node_pointer z)
		{
			node_pointer y = nullptr;
			node_pointer x = _root;
			while (x != nullptr)
			{
				y = x;
				if (_compare(*z, *x))
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == nullptr)
				_root = z;
			else if _compare(*z, *y)
				y->left = z;
			else
				y->right = z;
			z->left = nullptr;
			z->red = true;
			insert_fixup(node_pointer z);
		}

		void insert_fixup(node_pointer z)
		{
			node_pointer y = nullptr;
			while (z != _root && z->parent->red == true)
			{
				if (z->parent == z->parent->parent->left)
				{
					y = z->patent->parent->right;
					if (y->red == true)
					{
						z->parent->red = false;
						y->red = false;
						z->parent->parent->red = true;
						z = z->parent->parent;
					}
					else if (z == z->parent->right)
					{
						z = z->parent;
						rotate_left(z->parent->parent);
					}
					else
					{
						z->parent->red = false;
						z->parent->parent->red = true;
						rotate_right(z->parent->parent);
					}
				}
				else
				{
					y = z->patent->parent->left;
					if (y->red == true)
					{
						z->parent->red = false;
						y->red = false;
						z->parent->parent->red = true;
						z = z->parent->parent;
					}
					else if (z == z->parent->left)
					{
						z = z->parent;
						rotate_right(z->parent->parent);
					}
					else
					{
						z->parent->red = false;
						z->parent->parent->red = true;
						rotate_left(z->parent->parent);
					}
				}
			}
			_root->red = false;
		}

		void transplant(node_pointer x, node_pointer y)
		{
			if (x->parent == nullptr)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->parent = x->parent;
		}

		inline pointer min(pointer x){
			while (x->left != nullptr)
				x = x->left;
			return x;
		}

		inline pointer max(pointer x){
			while (x->right != nullptr)
				x = x->right;
			return x;
		}

		void erase(node_pointer z)
		{
			node_pointer x;
			node_pointer y = z;
			bool y_is_red = y->red;
			if (z->left == nullptr)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == nullptr)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else 
			{
				y = min(z->right);
				y_is_red = y->red;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else 
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				y->left = z->left;
				y->left->parent = y;
				y->red = z->red;
			}
			if (y_is_red == false)
				erase_fixup(x);
		}

		void erase_fixup(node_pointer x)
		{
			node_pointer w;
			while (x != _root && x->red == false)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->red == true)
					{
						w->red = false;
						x->parent->red = true;
						rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->red == false && w->right->red == false)
					{
						w->red = true;
						x = x->parent;
					}
					else if (w->right->red == false)
					{
						w->left->red = false;
						w->red = true;
						rotate_right(w);
						w = x->parent->right;
					}
					else
					{
						w->red = x->parent->red;
						x->parent->red = false;
						w->right->red = false;
						rotate_left(x->parent)
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->red == true)
					{
						w->red = false;
						x->parent->red = true;
						rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->left->red == false && w->right->red == false)
					{
						w->red = true;
						x = x->parent;
					}
					else if (w->left->red == false)
					{
						w->right->red = false;
						w->red = true;
						rotate_left(w);
						w = x->parent->left;
					}
					else
					{
						w->red = x->parent->red;
						x->parent->red = false;
						w->left->red = false;
						rotate_right(x->parent)
						x = _root;
					}					
				}
			}
			x->red = false;
		}
	};

} // namespace ft

#endif