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

		typedef typename Allocator::template
		rebind<Node<T> >::other								node_allocator;
		typedef typename node_allocator::value_type			node_type;
		typedef	typename node_allocator::pointer			node_pointer;
		typedef typename node_allocator::const_pointer		node_const_pointer;
		typedef typename node_allocator::reference			node_reference;
		typedef typename node_allocator::const_reference	node_const_reference;
		typedef typename node_allocator::size_type			size_type;
		// typedef tree_iter<value_type>						iterator;
		// typedef tree_iter<value_type>						const_iterator;
		// typedef ft::reverse_iterator<iterator>				reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


	private:
		node_allocator											_node_alloc;
		value_compare 											_compare;
		node_pointer											_root;
		node_pointer											_end;
		size_type												_size;


	public:
	//construct/copy/destroy:

		rb_tree(const value_compare& comp = value_compare(), const node_allocator& a = node_allocator()) : 
				_node_alloc(a), _compare(comp), _end(nullptr), _root(nullptr), _size(0)
		{
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, node_type());
			// _end->left = _root;
			// std::cout << "rb_tree constructor" << std::endl;
		}
		
		// rb_tree& operator=(const rb_tree& __m);

		node_pointer find(node_pointer node, node_pointer& key_node)
		{
			// std::cout << "find 2 elem" << std::endl;
			while (node != nullptr && node->value != nullptr &&  !(_compare(*node->value, *key_node->value) && _compare(*key_node->value, *node->value))) 
			{
				if (_compare(*key_node->value, *node->value))
					node = node->left;
				else
					node = node->right;
			}
			// std::cout << "find 2 elem" << std::endl;
			// if (node == _end)
			// 	std::cout << "node == _end" <<std::endl;
			// else if(node == nullptr)
			// 	std::cout << "node != nullptr" <<std::endl;
			if (node == nullptr)
				return _end;
			return node;
		}

		node_pointer find(node_pointer& key_node)
		{
			// std::cout << "find 1 elem" << std::endl;
			return find(_end, key_node);
		}

		void clear()
		{
			destroy(_root);
			_size = 0;
			_root = nullptr;
			_end->left = _root;
		}

		void destroy(const node_pointer& _x)
		{
			// std::cout << "~rb_tree() destroy" << std::endl;
			if (_x != nullptr)
			{
				destroy(_x->left);
				destroy(_x->right);
			// std::cout << "~rb_tree() destroy!!!!" << std::endl;
				destroy_node(_x);
			}
		}

		void destroy_node(const node_pointer& _x)
		{
			// std::cout << "destroy_node " << std::endl;
			// if (_x == _end)
			// {
			// 	std::cout << "_x == _end" << std::endl;
			// }
			if (_x != nullptr)
			{
				allocator_type _alloc;
				if (_x->value)
				{
			// std::cout << "destroy_node end " << _x->value->first << std::endl;
					_alloc.destroy(_x->value);
					_alloc.deallocate(_x->value, 1);
				}
				_node_alloc.destroy(_x);
				_node_alloc.deallocate(_x, 1);
			}
		}

		~rb_tree()
		{
			// std::cout << "~rb_tree()" << std::endl;
			destroy(_root);
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
		}

		node_pointer min(node_pointer p_x)
		{
			// std::cout << "min" <<std::endl;
			while (p_x->left != nullptr)
				{
					// std::cout << "min" <<std::endl;
					p_x = p_x->left;}
			return p_x;
		}

	//iterators
			// iterator begin() {return min(_root);}
			// const_iterator begin() const {return min(_root);}
			// iterator end() {return _end(_root);}
			// const_iterator end() const {return _end(_root);}
			node_pointer begin() {return min(_end);}
			// node_const_pointer begin() const {return min(_root);}
			node_pointer end() {return _end;}
			// node_const_pointer end() const {return max(_root);}

	//capacity
			bool      empty() const {return _size == 0;}
			size_type size() const {return _size;}
			size_type max_size() const {return _node_alloc.max_size();}


	//rotates

		void rotate_left(node_pointer __x)
		{
			// std::cout << "  rotate_left" << std::endl;
			if (__x == nullptr)
				return ;
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
			// std::cout << "  rotate_right" << std::endl;
			if (__x == nullptr)
				return ;
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

		node_pointer init_node(value_type v_x)
		{
			node_pointer z = _node_alloc.allocate(1);
			_node_alloc.construct(z, v_x);
			return z;
		}

		pair<node_pointer, bool> insert(node_pointer& z)
		// void insert(node_pointer& z)
		{
			// if (_root != nullptr)
				// std::cout << "1 _root != nullptr  _root = z = " << _root->value->second << std::endl;
			pair<node_pointer, bool> ret;
			ret.first = find(_root,z);
			if (ret.first != _end)
			{
				// std::cout << "pair<node_pointer, bool> insert" << std::endl;
				ret.second = false;
				return ret;
			}
			// std::cout << "!!!" << std::endl;
			// if (_root != nullptr)
			// 	std::cout << "2 _root != nullptr  _root = z = " << _root->value->second << std::endl;
			node_pointer y = _end;
			node_pointer x = _root;
			while (x != nullptr)
			{
				// std::cout << "   x:"<< std::endl;
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
				_end->left = _root;
				// if (_root != nullptr)
				// 	std::cout << "_root != nullptr" << std::endl;
				// std::cout << "_root = z = " << _root->value->second << std::endl;
				// std::cout << "_root = z = " << _end->left->value->second << std::endl;
			}
			else if (_compare(*z->value, *y->value)) // _compare(z->value, y->value) z->value < y->value
				y->left = z;
			else
				y->right = z;
			// std::cout << "!!!" << std::endl;
			z->left = nullptr;
			z->right = nullptr;
			z->red = true;
			insert_fixup(z);
			// std::cout << "insert tree" << std::endl;
			++_size;
			ret.first = z;
			ret.second = true;
			// if (_root != nullptr)
			// 	std::cout << "insert end" << std::endl;
			return ret;
		}

		void insert_fixup(node_pointer& z)
		{
			node_pointer y = nullptr;
			// std::cout << "insert_fixup" << std::endl;
			while (z != _root && z->parent->red == true)
			{
				std::cout << "insert_fixup" << std::endl;
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
					// std::cout << "else     _fixup" << std::endl;
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
			if (y == nullptr)
				return ;
			if (x->parent == nullptr)
			{
				// std::cout << "_root = y" <<std::endl;
				_root = y;
			}
			else if (x == x->parent->left)
			{
				// std::cout << "x->parent->left = y" <<std::endl;
				x->parent->left = y;
			}
			else
			{
				// std::cout << "x->parent->right = y" <<std::endl;
				x->parent->right = y;
			}
			// std::cout << "transplant" <<std::endl;
			y->parent = x->parent;
		}

		void erase(node_pointer& z)
		{
			// std::cout << "tree erase" <<std::endl;
			if (_size == 0)
				return ;
			node_pointer x;
			node_pointer y = z;
			bool y_is_red = y->red;
			if (z->left == nullptr)
			{
				x = z->right;
				transplant(z, z->right);
			// std::cout << "tree erase if" <<std::endl;
			}
			else if (z->right == nullptr)
			{
			// std::cout << "tree erase elseif" <<std::endl;
				x = z->left;
				transplant(z, z->left);
			}
			else 
			{
			// std::cout << "tree erase else" <<std::endl;
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
			destroy_node(z);
			// std::cout << "end tree erase" <<std::endl;
			--_size;
		}

		void erase_fixup(node_pointer& x)
		{
			// std::cout << "erase_fixup" <<std::endl;
			node_pointer w;
			if (x == nullptr)
				return ;
			while (x != _root && x->red == false)
			{
				if (x == x->parent->left)
				{
					// std::cout << "erase_fixup if" <<std::endl;
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
					// std::cout << "erase_fixup else" <<std::endl;
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

		void delete_node(node_pointer& z)
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
				y = min(z);
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
				transplant(z,y);
				y->left = z->left;
				y->left->parent = y;
				y->red = z->red;
			}
			if (y_is_red == false)
				delete_fixup(x);
		}
		
		void delete_fixup(node_pointer& x)
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
					if (w->left->red == false and w->right->red == false)
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
					if (w->right->red == false and w->left->red == false)
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
				std::swap(_root, other._root);
				std::swap(_size, other._size);
			}
		}
	};

} // namespace ft

#endif