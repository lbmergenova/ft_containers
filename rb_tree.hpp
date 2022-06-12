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
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef typename Allocator::template
		rebind<Node<T> >::other								node_allocator;
		typedef typename node_allocator::value_type			node_type;
		typedef	typename node_allocator::pointer			node_pointer;
		typedef typename node_allocator::const_pointer		node_const_pointer;
		typedef typename node_allocator::reference			node_reference;
		typedef typename node_allocator::const_reference	node_const_reference;
		typedef typename node_allocator::size_type			size_type;
		typedef tree_iter<value_type, pointer>				iterator;
		typedef tree_iter<value_type, const_pointer>		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		node_allocator											_node_alloc;
		value_compare 											_compare;
		node_pointer											_end;
		node_pointer											_root;
		size_type												_size;


	public:
	//construct/copy/destroy:

		rb_tree(const value_compare& comp = value_compare(), const node_allocator& a = node_allocator()) : 
				_node_alloc(a), _compare(comp), _end(nullptr), _root(nullptr), _size(0)
		{
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, node_type(false));
		}

		rb_tree(const rb_tree& __t) : _node_alloc(__t._node_alloc), _compare(__t._compare), _end(nullptr), _root(nullptr), _size(0)
		{
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, node_type(false));
			if (__t.size() == 0)
				return;
			node_const_pointer x = __t.min_const(__t._root);
			node_pointer _node;
			while (x != __t._end)
			{
				_node = init_node(*(x->value));
				insert(_node);
				x = successor(x);
			}
		}

		rb_tree& operator=(const rb_tree& __t)
		{
			if (this != &__t)
			{
				clear();
				if (__t.size() == 0)
					return *this;
				node_const_pointer x = __t.min(__t._root);
				node_pointer _node;
				while (x != __t._end)
				{
					_node = init_node(*(x->value));
					insert(_node);
					x = successor(x);
				}
			}
			return *this;
		}
		
		~rb_tree()
		{
			if (_root)
				destroy(_root);
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
		}

		void clear()
		{
			if (_root)
				destroy(_root);
			_size = 0;
			_root = nullptr;
			_end->left = _root;
		}

		void destroy(const node_pointer& _x)
		{
			if (_x != _end)
			{
				destroy(_x->left);
				destroy(_x->right);
				destroy_node(_x);
			}
		}

		node_pointer init_node(value_type v_x)
		{
			allocator_type _alloc;
			pointer _p = _alloc.allocate(1);
			_alloc.construct(_p, v_x);
			node_pointer z = _node_alloc.allocate(1);
			_node_alloc.construct(z, _p);
			return z;
		}

		void destroy_node(const node_pointer& _x)
		{
			if (_x != _end)
			{
				allocator_type _alloc;
				if (_x->value)
				{
					_alloc.destroy(_x->value);
					_alloc.deallocate(_x->value, 1);
				}
				_node_alloc.destroy(_x);
				_node_alloc.deallocate(_x, 1);
			}
		}
		
		node_pointer search(node_pointer node, node_pointer& key_node)
		{
			if (!node)
				return _end;
			while (node != _end && (_compare(*node->value, *key_node->value) || _compare(*key_node->value, *node->value))) 
			{
				if (_compare(*key_node->value, *node->value))
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}

		node_pointer search(value_type _v) const
		{
			node_pointer node = _root;
			if (!node)
				return _end;
			while (node != _end && (_compare(*node->value, _v) || _compare(_v, *node->value))) 
			{
				if (_compare(_v, *node->value))
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}

		node_pointer search(node_pointer& key_node)
		{
			return search(_root, key_node); 
		}

		bool is_tree_position(node_pointer& key_node)
		{
			node_pointer node = _root;
			if (!node)
				return false;
			while (node != _end && node != key_node) 
			{
				if (_compare(*key_node->value, *node->value))
					node = node->left;
				else
					node = node->right;
			}
			if (node == _end)
				return false;
			return true; 
		}

		node_pointer min(node_pointer p_x) const
		{
			while (p_x->left != nullptr && p_x->left->value != nullptr)
			{
				p_x = p_x->left;
			}		
			return p_x;
		}

		node_const_pointer min_const(node_pointer p_x) const
		{
			while (p_x->left != nullptr && p_x->left->value != nullptr)
					p_x = p_x->left;
			return p_x;
		}

		node_const_pointer successor(node_const_pointer x) const
		{
			if (x->value != nullptr && x->right->value != nullptr)
				return min_const(x->right);
			node_pointer y = x->parent;
			while (y->value != nullptr && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
        }

	//iterators
			iterator begin() {return min(_end);}
			const_iterator begin() const {return min(_end);}
			iterator end() {return _end;}
			const_iterator end() const {return _end;}

			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

	//capacity
			bool      empty() const {return _size == 0;}
			size_type size() const {return _size;}
			size_type max_size() const {return _node_alloc.max_size();}


	//rotates

		void rotate_left(node_pointer x)
		{
			if (x == _end)
				return ;
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _end)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _end)
			{
				_root = y;
				// _root->parent = _end; // ???
				_end->left = _root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void rotate_right(node_pointer x)
		{
			if (x == _end)
				return ;
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != _end)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _end)
			{
				_root = y;
				// _root->parent = _end; // ???
				_end->left = _root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->right = x;
			x->parent = y;
		}

		node_pointer insert(node_pointer& z)
		{
			node_pointer y = _end;
			node_pointer x = _root;
			while (x && x != _end)
			{
				y = x;
				if (_compare(*z->value, *x->value)) // _compare(z->value, x->value) z->value < x->value
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == _end)
			{
				_root = z;
				// _root->parent = _end; // ???
				_end->left = _root;
			}
			else if (_compare(*z->value, *y->value)) // _compare(z->value, y->value) z->value < y->value
				y->left = z;
			else
				y->right = z;
			z->left = _end;
			z->right = _end;
			z->red = true;
			insert_fixup(z);
			++_size;
			return z;
		}

		void insert_fixup(node_pointer& z)
		{
			node_pointer y;
			while (z != _root && z->parent->red == true)
			{
				if (z->parent == z->parent->parent->left)
				{
					y = z->parent->parent->right;
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
					y = z->parent->parent->left;
					if (y && y->red == true)
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

		void transplant(node_pointer& x, node_pointer& y)
		{
			if (x->parent == _end)
			{
				_root = y;
				// _root->parent = _end; // ???
				_end->left = _root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			_end->left = _root;
			if (y != _end)
				y->parent = x->parent;
		}

		void erase(node_pointer& z)
		{
			if (_size == 0)
				return ;
			node_pointer x;
			node_pointer y = z;
			bool y_is_red = y->red;
			if (z->left == _end)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _end)
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
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->red = z->red;
			}
			if (y_is_red == false)
				erase_fixup(x);
			--_size;
			destroy_node(z);
		}

		void erase_fixup(node_pointer& x)
		{
			node_pointer w;
			if (x == _end)
				return ;
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
						rotate_left(x->parent);
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
					if (w->right->red == false && w->left->red == false)
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
						rotate_right(x->parent);
						x = _root;
					}					
				}
			}
			x->red = false;
		}

		void swap(rb_tree& other){
			if (this != other)
			{
				std::swap(_node_alloc, other._node_alloc);
				std::swap(_compare, other._compare);
				std::swap(_end, other._end);
				std::swap(_root, other._root);
				std::swap(_size, other._size);
			}
		}

// 
	iterator lower_bound(const value_type& value) const
	{
		if (_root != nullptr)
		{
			node_pointer node, remembered;
			for (node = _root, remembered = _root; node != _end;) {
				if ((_compare(*node->value, value) || _compare(value, *node->value)))
					return node;
				if (_compare(value, node->data->first)) {
					remembered = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return _compare(value, remembered->data->first) ? iterator(remembered) : end();
		}
		return _nil;
	}

	const_iterator upper_bound(const value_type& value) const
	{
		if (_root != nullptr)
		{
			node_pointer node, remembered;
			for (node = _root, remembered = _root; node != _end;) {
				if (_compare(value, node->data->first)) {
					remembered = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			return _compare(value, remembered->data->first) ? iterator(remembered) : end();
		}
		return _nil;
	}

//
		friend inline bool operator==(const rb_tree& __x, const rb_tree& __y) 
		{ return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin()); }

		friend  inline bool operator<(const rb_tree& __x, const rb_tree& __y) 
		{ return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()); }
	};


} // namespace ft

#endif