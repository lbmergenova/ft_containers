#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

namespace ft
{
// Node
//________________________________________________________________________________________________________
//________________________________________________________________________________________________________

	template <class T>
	struct Node
	{
	public:
		T*		value;
		Node*	parent;
		Node*	left;
		Node*	right;
		bool	red;

		Node() : value(nullptr), parent(nullptr), left(nullptr), right(nullptr), red(true) {}
		Node(T* v) : value(v), parent(nullptr), left(nullptr), right(nullptr), red(true) {}
		
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

		~Node() {}
	};

// tree_iter
//________________________________________________________________________________________________________
//________________________________________________________________________________________________________

	template <class _Tp>
	class tree_iter
	{
	public:

		typedef Node<_Tp> *													iterator_type; // _Tp = pair<class U, class V>
		typedef std::bidirectional_iterator_tag								iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		iterator_type	__p_node;

		inline pointer min(pointer p_x)
		{
			while (p_x->left != nullptr)
				p_x = p_x->left;
			return p_x;
		}

		inline pointer max(pointer p_x)
		{
			while (p_x->right != nullptr)
				p_x = p_x->right;
			return p_x;
		}

        pointer next(pointer x)
        {
			// std::cout << "next->" << std::endl;
			if (x != nullptr && x->right != nullptr)
				return min(x->right);
			pointer y = x->parent;
			while (y != nullptr && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			// std::cout << "<-next" << std::endl;
			// if (y != nullptr)
			// 	std::cout << "y " << y->value->first << std::endl;
			// else
			// 	std::cout << "y = null" << std::endl;
			return y;
        }

        pointer prev(pointer x)
        {
			if (x != nullptr && x->left != nullptr)
				return max(x->left);
			pointer y = x->parent;
			while (y != nullptr && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
        }

	public:
		tree_iter() {}

		tree_iter(pointer _x) : __p_node(_x) {}

		_Tp& operator*() const {return *(__p_node->value) ;}
		_Tp* operator->() const {
			// std::cout << "operator->" << std::endl;
			return __p_node->value ;}


        tree_iter& operator++()
        {
			pointer	t;
            __p_node = next(__p_node);
            return *this;
        }

        tree_iter operator++(int)
        {
			// std::cout << "operator++" << std::endl;
            tree_iter tmp(*this);
			pointer	t;
            __p_node = next(__p_node);
			// std::cout << "end operator++" << std::endl;
            return tmp;
        }

        tree_iter& operator--()
        {
            __p_node = prev(__p_node);
            return *this;
        }

        tree_iter operator--(int)
        {
            tree_iter tmp(*this);
            __p_node = prev(__p_node);
            return tmp;
        }

		friend bool operator==(const tree_iter& __x, const tree_iter& __y)
		{ return __x.__p_node == __y.__p_node; }

		friend bool operator!=(const tree_iter& __x, const tree_iter& __y)
		{ return __x.__p_node != __y.__p_node; }

	};

} // namespace ft

#endif
