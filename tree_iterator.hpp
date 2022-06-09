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

		~Node(){
			std::allocator<T> _alloc;
			_alloc.destroy(value);
			_alloc.deallocate(value,1);
		} // virtual
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
		// iterator_type	__p_node;
		pointer	__p_node;
		pointer	__root;

		inline pointer tree_min(pointer p_x){
			while (p_x->left != nullptr)
				p_x = p_x->left;
			return p_x;
		}

		inline pointer tree_max(pointer p_x){
			while (p_x->right != nullptr)
				p_x = p_x->right;
			return p_x;
		}

		// pointer next(pointer x)// everything is fine!
        //     {
        //         // std::cout << "successor"<< std::endl;
        //         //to do& try and catch
        //         if(x == nullptr)
        //             return NULL;
        //         if(x->right != nullptr)//leftmost node in right subtree
        //             return tree_min(x->right);
        //         pointer y = nullptr;
        //         y = x->parent;
        //         while(y != nullptr && x == y->right)
        //         {
        //             x = y;
        //             y = y->parent;
        //         }
        //         return y;
        //     }

        pointer next(pointer node)
        {
            if (node == nullptr)
                return nullptr;

            if (node->right != nullptr)
                return tree_min(node->right);

            pointer ptr = node->parent;
            while (ptr!= nullptr && node == ptr->right) {
                node = ptr;
                ptr = ptr->parent;
            }
            return ptr;
        }

        pointer prev(pointer node)
        {
            if (node == nullptr)
                return tree_max(__root);

            if (node != nullptr && node->left != nullptr)
                return tree_max(node->left);

            pointer ptr = node->parent;
            while (ptr!= nullptr && node == ptr->left) {
                node = ptr;
                ptr = ptr->parent;
            }

            return ptr!= nullptr ? ptr : node;
        }

	public:
		tree_iter() {}

		tree_iter(pointer _x, pointer root) : __p_node(_x), __root(root) {}

		_Tp& operator*() const {return *(__p_node->value) ;}
		_Tp* operator->() const {return __p_node->value ;}


        tree_iter& operator++()
        {
			pointer	t;
            __p_node = next(__p_node);
            return *this;
        }

        tree_iter operator++(int)
        {
            tree_iter tmp(*this);
			pointer	t;
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

		// tree_iter& operator++() {
		// 	if (__p_node->right != nullptr)
		// 		return tree_min(__p_node->right);
		// 	pointer next = __p_node->parent;
		// 	while (next != nullptr && __p_node == next->right)
		// 	{
		// 		__p_node = next;
		// 		next = next->parent;
		// 	}
		// 	__p_node = next;
		// 	return *this;
		// }

		// tree_iter operator++(int){
		// 	tree_iter tmp(*this);
		// 	if (__p_node->right != nullptr)
		// 		return tree_min(__p_node->right);
		// 	pointer next = __p_node->parent;
		// 	while (next != nullptr && __p_node == next->right)
		// 	{
		// 		__p_node = next;
		// 		next = next->parent;
		// 	}
		// 	__p_node = next;
		// 	return tmp;
		// }

		// tree_iter& operator--() {
		// 	if (__p_node->left != nullptr)
		// 		return tree_max(__p_node->left);
		// 	pointer before = __p_node->parent;
		// 	while (before != nullptr && __p_node == before->left)
		// 	{
		// 		__p_node = before;
		// 		before = before->parent;
		// 	}
		// 	__p_node = before;
		// 	return *this;
		// }
		// tree_iter operator--(int){
		// 	tree_iter tmp(*this);
		// 	if (__p_node->left != nullptr)
		// 		return tree_max(__p_node->left);
		// 	pointer before = __p_node->parent;
		// 	while (before != nullptr && __p_node == before->left)
		// 	{
		// 		__p_node = before;
		// 		before = before->parent;
		// 	}
		// 	__p_node = before;
		// 	return tmp;
		// }

		friend bool operator==(const tree_iter& __x, const tree_iter& __y)
			{return __x.__p_node == __y.__p_node;}

		friend bool operator!=(const tree_iter& __x, const tree_iter& __y)
			{return __x.__p_node != __y.__p_node;}

// __________________________________________________
// Returns:  pointer to a node which has no children
// Precondition:  __x != nullptr.
// template <class _NodePtr>
// _NodePtr
// __tree_leaf(_NodePtr __x) _NOEXCEPT
// {
//     while (true)
//     {
//         if (__x->__left_ != nullptr)
//         {
//             __x = __x->__left_;
//             continue;
//         }
//         if (__x->__right_ != nullptr)
//         {
//             __x = __x->__right_;
//             continue;
//         }
//         break;
//     }
//     return __x;
// }
// __________________________________________________

	};

} // namespace ft

#endif
