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
			iterator it = __t.begin();
			iterator it_end = __t.end();
			while (it != it_end)
			{
				insert(*it);
				++it;
			}
		}

		rb_tree& operator=(const rb_tree& __t)
		{
			if (this != &__t)
			{
				clear();
				if (__t.size() == 0)
					return *this;
				_compare = __t._compare;
				iterator it = __t.begin();
				iterator it_end = __t.end();
				while (it != it_end)
				{
					insert(*it);
					++it;
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
		
		node_pointer search(value_type _v)
		{
			node_pointer node = _root;
			if (!node)
				return _end;
			while (node && node != _end && (_compare(*node->value, _v) || _compare(_v, *node->value))) 
			{
				if (_compare(_v, *node->value))
					node = node->left;
				else
					node = node->right;
			}
			return node;
		}

		iterator search(value_type _v) const
		{
			node_pointer node = _root;
			if (!node)
				return end();
			while (node != _end && (_compare(*node->value, _v) || _compare(_v, *node->value))) 
			{
				if (_compare(_v, *node->value))
					node = node->left;
				else
					node = node->right;
			}
			return iterator(node);
		}

		node_pointer min(node_pointer p_x) const
		{
			while (p_x->left != nullptr && p_x->left->value != nullptr)
			{
				p_x = p_x->left;
			}		
			return p_x;
		}

		void swap(rb_tree& other){
			if (this != &other)
			{
				std::swap(_node_alloc, other._node_alloc);
				std::swap(_compare, other._compare);
				std::swap(_end, other._end);
				std::swap(_root, other._root);
				std::swap(_size, other._size);
			}
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

//

		ft::pair<iterator, bool> insert(const value_type __v)
		{
			node_pointer y = _end;
			node_pointer x = _root;
			while (x && x != _end)
			{
				if (!(_compare(__v, *x->value) || _compare(*x->value, __v)))
					return ft::pair<iterator,bool>(x, false);
				y = x;
				if (_compare(__v, *x->value))
					x = x->left;
				else
					x = x->right;
			}
			allocator_type _alloc;
			pointer _p = _alloc.allocate(1);
			_alloc.construct(_p, __v);
			node_pointer z = _node_alloc.allocate(1);
			_node_alloc.construct(z, node_type());
			z->value = _p;
			z->parent = y;
			if (y == _end)
			{
				_root = z;
				_end->left = _root;
			}
			else if (_compare(*z->value, *y->value))
				y->left = z;
			else
				y->right = z;
			z->left = _end;
			z->right = _end;
			z->red = true;
			insert_fixup(z);
			++_size;
			return ft::pair<iterator,bool>(z, true);;
		}

		void erase(node_pointer it)
		{
			erase_node(it);
		}

		iterator lower_bound(const value_type& __v) const
		{
			if (_root != nullptr)
			{
				node_pointer x, y;
				for (x = _root, y = _root; x != _end;) {
					if (!(_compare(*x->value, __v) || _compare(__v, *x->value)))
						return iterator(x);
					if (_compare(__v, *x->value)) {
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				if (_compare(__v, *y->value))
					return iterator(y);
			}
			return end();
		}

		iterator upper_bound(const value_type& __v) const
		{
			if (_root != nullptr)
			{
				node_pointer x, y;
				for (x = _root, y = _root; x != _end;) {
					if (_compare(__v, *x->value)) {
						y = x;
						x = x->left;
					}
					else
						x = x->right;
				}
				if (_compare(__v, *y->value))
					return iterator(y);
			}
			return end();
		}

		friend inline bool operator==(const rb_tree& __x, const rb_tree& __y) 
		{ return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin()); }

		friend  inline bool operator<(const rb_tree& __x, const rb_tree& __y) 
		{ return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()); }


		private:
//rotates/insert_node/erase_node/destroy

		void rotate_left(node_pointer x)
		{
			if (x == nullptr || x == _end)
				return ;
			node_pointer y = x->right;
			x->right = y->left;
			if (y != _end && y->left != _end)
				y->left->parent = x;
			if (y != _end)
				y->parent = x->parent;
			if (x->parent == _end)
			{
				_root = y;
				_end->left = _root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			if (x != _end)
				x->parent = y;
		}

		void rotate_right(node_pointer x)
		{
			if (x == nullptr || x == _end)
				return ;
			node_pointer y = x->left;
			x->left = y->right;
			if (y != _end && y->right != _end)
				y->right->parent = x;
			if (y != _end)
				y->parent = x->parent;
			if (x->parent == _end)
			{
				_root = y;
				_end->left = _root;
			}
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->right = x;
			if (x != _end)
				x->parent = y;
		}

		void insert_fixup(node_pointer z)
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
						rotate_left(z);
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
						rotate_right(z);
					}
					else
					{
						z->parent->red = false;
						z->parent->parent->red = true;
						rotate_left(z->parent->parent);
					}
				}
			}
			_end->red = false;
			_root->red = false;
		}

		void transplant(node_pointer& x, node_pointer& y)
		{
			if (x->parent == _end)
			{
				_root = y;
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

		void erase_node(node_pointer& z)
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
	
		void destroy(const node_pointer& _x)
		{
			if (_x != _end)
			{
				destroy(_x->left);
				destroy(_x->right);
				destroy_node(_x);
			}
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
		
	};

} // namespace ft

#endif