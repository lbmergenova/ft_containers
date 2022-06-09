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
		// node_pointer											_nill;
		size_type												_size;

		inline node_pointer min(node_pointer p_x){
			if (_size == 0)
				return nullptr;
			if (p_x == nullptr)
				return p_x;
			while (p_x->left != nullptr)
				p_x = p_x->left;
			return p_x;
		}

		inline node_pointer max(node_pointer p_x){
			while (p_x->right != nullptr)
				p_x = p_x->right;
			return p_x;
		}

		void inorder_tree_walk(node_pointer _x)
		{
			if (_x != nullptr)
			{
				inorder_tree_walk(_x->left);
				prnt_node(_x);
				inorder_tree_walk(_x->right);
			}
		}

		void prnt_node(node_pointer _x)
		{
			std::cout << "key " << _x->value->first << " value " << _x->value->second <<std::endl;
		}

	public:
	//helpers
		void tree_print(void)
		{
			inorder_tree_walk(_root);
		}

	//construct/copy/destroy:

		rb_tree(const value_compare& comp = value_compare(), const node_allocator& a = node_allocator()) : 
				_node_alloc(a), _compare(comp), _root(nullptr), _size(0) {}

		// template <class InputIterator>
		// rb_tree(InputIterator _first, InputIterator _last, const node_allocator& a = node_allocator(), const value_compare& comp = value_compare()) : 
		// 		_node_alloc(a), _compare(comp), _root(_node_alloc.allocate(1)), _nill(_root), _size(0)
		// {}

		// rb_tree(const rb_tree& __t) : _node_alloc(node_allocator()), _compare(value_compare()), 
		// 								_root(_node_alloc.allocate(1)), _nill(_root), _size(0)
		// {}
		
		rb_tree& operator=(const rb_tree& __m)
		{
			if (this != &__m) 
			{
				// ?
			}     
			return *this;
		}

		void clear()
		{
			destroy(_root);
			_size = 0;
			_root = nullptr;
		}

		node_pointer find(node_pointer& node, node_pointer& key_node)
		{
			if (node != nullptr) 
			{
				if (!_compare(*node->value, *key_node->value) && !_compare(*key_node->value, *node->value))
					return node;
				else if (_compare(*key_node->value, *node->value))
					return find(node->left, key_node);
				else
					return find(node->right, key_node);
			}
			return nullptr;
		}

		node_pointer find(node_pointer& key_node)
		{
			return find(_root, key_node);
		}

		void destroy(const node_pointer& _x)
		{
			// std::cout << "destroy" << std::endl;
			if (_x != nullptr)
			{
				destroy(_x->left);
				destroy(_x->right);
				_node_alloc.destroy(_x);
				_node_alloc.deallocate(_x, 1);
			}
		}

		void destroy_node(const node_pointer& _x){
			if (_x != nullptr)
			{
				_node_alloc.destroy(_x);
				_node_alloc.deallocate(_x, 1);
			}
		}

		~rb_tree()
		{
			destroy(_root);
		}

	//iterators
			// iterator begin() {return min(_root);}
			// const_iterator begin() const {return min(_root);}
			// iterator end() {return _end(_root);}
			// const_iterator end() const {return _end(_root);}
			node_pointer begin() {return min(_root);}
			// node_const_pointer begin() const {return min(_root);}
			node_pointer end() {return nullptr;}
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
			pair<node_pointer, bool> ret;
			ret.first = find(_root,z);
			if (ret.first != nullptr)
			{
				ret.second = false;
				return ret;
			}
			node_pointer y = nullptr;
			node_pointer x = _root;
			while (x != nullptr)
			{
				// std::cout << "   x:" << x << " " << " " << x->value.first << " " << x->value.second << std::endl;
				y = x;
				if (_compare(*z->value, *x->value)) // _compare(z->value, x->value) z->value < x->value
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == nullptr)
				_root = z;
			else if (_compare(*z->value, *y->value)) // _compare(z->value, y->value) z->value < y->value
				y->left = z;
			else
				y->right = z;
			z->left = nullptr;
			z->right = nullptr;
			z->red = true;
			insert_fixup(z);
			// std::cout << "insert tree" << std::endl;
			++_size;
			ret.first = z;
			ret.second = true;
			return ret;
		}

		void insert_fixup(node_pointer& z)
		{
			node_pointer y = nullptr;
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
			std::cout << "tree erase" <<std::endl;
			if (_size == 0)
				return ;
			node_pointer x;
			node_pointer y = z;
			bool y_is_red = y->red;
			if (z->left == nullptr)
			{
			// std::cout << "tree erase if" <<std::endl;
				x = z->right;
				transplant(z, z->right);
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
				y->left = z->left;
				y->left->parent = y;
				y->red = z->red;
			}
			if (y_is_red == false)
				erase_fixup(x);
			--_size;
		}

		void erase_fixup(node_pointer& x)
		{
			std::cout << "erase_fixup" <<std::endl;
			node_pointer w;
			if (x == nullptr)
				return ;
			while (x != _root && x->red == false)
			{
				if (x == x->parent->left)
				{
					std::cout << "erase_fixup if" <<std::endl;
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
					std::cout << "erase_fixup else" <<std::endl;
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

		node_pointer get_root() const { return _root; }
	// additionally

		// void insert(iterator& first, iterator& last)
		// {
		// 	node_pointer __f = static_cast<node_pointer>(first);
		// 	while (first != last)
		// 	{
		// 		insert(__f);
		// 		++__f;
		// 		++first;
		// 	}
		// }

	};

} // namespace ft

#endif