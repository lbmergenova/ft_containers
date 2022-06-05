#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "utility.hpp"
#include "iterator_traits.hpp"
// #include "tree_iterator.hpp"
#include <memory>

namespace ft
{
	// Node
	template <class T>
	struct Node
	{
	public:
		T		value;
		Node*	parent;
		Node*	left;
		Node*	right;
		bool	red;

		Node(T v = T()) : value(v), parent(nullptr), left(nullptr), right(nullptr), red(true) {}
		
		Node(Node const &src): value(src.value), parent(src.parent), left(src.left), right(src.right), red(src.red) {}

		Node& operator=(Node const &src)
		{
			if (this != &src)
			{
				value = src.value;
				parent = src.parent;
				left = src.left;
				right = src.right;
				red = src.red;
			}
			return *this;
		}

		~Node(){}//std::cout << "Destructer of node" << std::endl;} // virtual
	};


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
		// typedef tree_iter<node_pointer>						iterator;
		// typedef tree_iter<node_const_pointer>				const_iterator;
		// typedef ft::reverse_iterator<iterator>				reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


	private:
		node_allocator											_node_alloc;
		value_compare 											_compare;
		node_pointer											_root;
		// node_pointer											_nill;
		size_type												_size;

		inline node_pointer min(node_pointer p_x){
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
			std::cout << "key " << _x->value.first << " value " << _x->value.second <<std::endl;
		}

	public:

		void tree_print(void)
		{
			inorder_tree_walk(_root);
		}

	//construct/copy/destroy:

		rb_tree(const node_allocator& a = node_allocator(), const value_compare& comp = value_compare()) : 
				_node_alloc(a), _compare(comp), _root(nullptr), _size(0)
		{
			// _node_alloc.construct(_root, node_type());
		}

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

			}     
			return *this;
		}

		void clear()
		{
			std::cout << "clear" << std::endl;
			destroy(_root);
			_size = 0;
		}

		void destroy(const node_pointer& _x)
		{
			// std::cout << "destroy" << std::endl;
			if (_x != nullptr)
			{
				destroy(_x->left);
				destroy(_x->right);
				std::cout << "!destroy node" << std::endl;
				_node_alloc.destroy(_x);
				// std::cout << "!destroy deallocate" << std::endl;
				// _node_alloc.deallocate(_x, 1);
				// std::cout << "!destroy end" << std::endl;
			}
		}

		~rb_tree()
		{
			std::cout << "Destructer rb_tree" << std::endl;
			destroy(_root);
			std::cout << "end Destructer rb_tree" << std::endl;
		}

	//iterators
			node_pointer begin() {return min(_root);}
			node_const_pointer begin() const {return min(_root);}
			node_pointer end() {return max(_root);}
			node_const_pointer end() const {return max(_root);}

	//capacity
			bool      empty() const {return _size == 0;}
			size_type size() const {return _size;}
			size_type max_size() const {return _node_alloc.max_size();}


	//rotates

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
			std::cout << "   insert" << std::endl;
			std::cout << "   z:" << z << " " << z->value << " " << z->value.first << " " << z->value.second << std::endl;
			while (x != nullptr)
			{
				std::cout << "   insert while" << std::endl;
				std::cout << "   x:" << x << " " << x->value << " " << x->value.first << " " << x->value.second << std::endl;
				y = x;
				if (z->value < x->value) // _compare(z->value, x->value)
				{
					std::cout << "   insert while <" << std::endl;
					x = x->left;
				}
				else
				{
					std::cout << "   insert while >" << std::endl;
					x = x->right;
				}
			}
			z->parent = y;
			if (y == nullptr)
			{
				// std::cout << "y == nullptr" << std::endl;
				_root = z;
			}
			else if (z->value < y->value) // _compare(z->value, y->value)
			{
				// std::cout << "_compare(z->value, y->value)" << std::endl;
				y->left = z;
			}
			else
			{
				// std::cout << "else _compare()" << std::endl;
				y->right = z;
			}
			z->left = nullptr;
			z->right = nullptr;
			z->red = true;
			insert_fixup(z);
		}

		void insert_fixup(node_pointer z)
		{
			std::cout << "     _fixup" << std::endl;
			node_pointer y = nullptr;
			while (z != _root && z->parent->red == true)
			{
				std::cout << "!  _fixup" << std::endl;
				if (z->parent == z->parent->parent->left)
				{
					std::cout << "!-1 _fixup" << std::endl;
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
					std::cout << "!-2 _fixup" << std::endl;
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
			std::cout << "end  _fixup" << std::endl;
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
	};

} // namespace ft

#endif