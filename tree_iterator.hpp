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
		Node(bool _red) : value(nullptr), parent(nullptr), left(nullptr), right(nullptr), red(_red) {}
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

	// template <class Key, class T, class _Tp>
	template <class T, class _Tp>
	class tree_iter
	{
	public:
	
		typedef _Tp															iterator_type; // _Tp = pair<class U, class V>
		typedef std::bidirectional_iterator_tag								iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		typedef Node<T> *						node_pointer;
		node_pointer	__p_node;

		inline node_pointer min(node_pointer p_x)
		{
			while (p_x->left->value != nullptr)
				p_x = p_x->left;
			return p_x;
		}

		inline node_pointer max(node_pointer p_x)
		{
			// std::cout << "max \n"; // << p_x->value->first <<std::endl;
			while (p_x->right->value != nullptr)
				p_x = p_x->right;
			// std::cout << "max\n";
			return p_x;
		}

		node_pointer next(node_pointer x)
		{
			if (x->value != nullptr && x->right->value != nullptr)
				return min(x->right);
			node_pointer y = x->parent;
			while (y->value != nullptr && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
        }

        node_pointer prev(node_pointer x)
        {
			// if (x && x->value)
				// std::cout << "input " << x->value->first <<std::endl;
			if (x->value == nullptr && x->left != nullptr)
			{
				// std::cout << "! " <<std::endl;
				return max(x->left);
			}
			node_pointer y = x->parent;
			if (y->value == nullptr)
			{
				// std::cout << "!! " <<std::endl;
				if (x->left->value != nullptr)
					return max(x->left);
				return x;
			}
			if (x->value != nullptr && x->left->value != nullptr)
			{
				// std::cout << "!!! " <<std::endl;
				return max(x->left);
			}
			while (x->value != nullptr && x == y->left)
			{
				// std::cout << "!!! " <<std::endl;
				x = y;
				y = y->parent;
			}
			return y;
        }

	public:
		tree_iter() {}

		tree_iter(node_pointer _x) : __p_node(_x) {}

        template<class U>
		tree_iter(const tree_iter<T, U>& other) : __p_node(other.base()) {}

		~tree_iter() {}

		tree_iter& operator=(const tree_iter& other)
		{
			if (this != &other)
				__p_node = other.__p_node;
			return *this;
		}

		reference operator*() const { return *(__p_node->value) ;}
		pointer operator->() const { return __p_node->value ; }

        tree_iter& operator++()
        {
			node_pointer	t;
            __p_node = next(__p_node);
            return *this;
        }

        tree_iter operator++(int)
        {
            tree_iter tmp(*this);
			node_pointer	t;
            __p_node = next(__p_node);
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

        node_pointer base() const
        {
			return __p_node;
        }

		friend bool operator==(const tree_iter& __x, const tree_iter& __y)
		{ return __x.__p_node == __y.__p_node; }

		friend bool operator!=(const tree_iter& __x, const tree_iter& __y)
		{ return __x.__p_node != __y.__p_node; }

	};


} // namespace ft

#endif
