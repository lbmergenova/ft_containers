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

		~Node(){std::cout << "Destructer of node" << std::endl;} // virtual
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

        pointer next(pointer node)
        {
            if (node == nullptr)
                return node;

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
                return node->parent;

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

		tree_iter(pointer _x) : __p_node(_x) {}

		// tree_iter(_TreeIter __i) : __p_node(__i) {}

		value_type operator*() const {return *__p_node ;}
		pointer operator->() const {return __p_node;}


        tree_iter& operator++()
        {
            __p_node = next(__p_node);
            return *this;
        }

        tree_iter operator++(int)
        {
            tree_iter tmp(*this);
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



// DRAFT

// // tree_iter
// //________________________________________________________________________________________________________
// //________________________________________________________________________________________________________

// 	template <class _TreeIter>
// 	class tree_iter
// 	{
// 	public:

// 		typedef _TreeIter													iterator_type;
// 		typedef std::bidirectional_iterator_tag								iterator_category;
// 		typedef typename iterator_traits<iterator_type *>::value_type		value_type;
// 		typedef typename iterator_traits<iterator_type *>::difference_type	difference_type;
// 		typedef typename iterator_traits<iterator_type *>::pointer			pointer;
// 		typedef typename iterator_traits<iterator_type *>::reference		reference;
// 		typedef Node<typename remove_const<_TreeIter>::type>*				node_pointer;

// 	private:
// 		node_pointer	__p_node;

// 		inline node_pointer tree_min(node_pointer p_x){
// 			while (p_x->left != nullptr)
// 				p_x = p_x->left;
// 			return p_x;
// 		}

// 		inline node_pointer tree_max(node_pointer p_x){
// 			while (p_x->right != nullptr)
// 				p_x = p_x->right;
// 			return p_x;
// 		}

// 	public:
// 		tree_iter() {}

// 		tree_iter(_TreeIter __i) : __p_node(__i.__p_node) {}

// 		reference operator*() const {return *(__p_node->p_value);}
// 		pointer operator->() const {return __p_node->p_value;}

// 		tree_iter& operator++() {
// 			if (__p_node->right != nullptr)
// 				return tree_min(__p_node->right);
// 			node_pointer next = __p_node;
// 			while (next != nullptr && __p_node == next->right)
// 			{
// 				__p_node = next;
// 				next = next->parent;
// 			}
// 			__p_node = next;
// 			return *this;
// 		}

// 		tree_iter operator++(int){
// 			tree_iter tmp(*this);
// 			if (__p_node->right != nullptr)
// 				return tree_min(__p_node->right);
// 			node_pointer next = __p_node->parent;
// 			while (next != nullptr && __p_node == next->right)
// 			{
// 				__p_node = next;
// 				next = next->parent;
// 			}
// 			__p_node = next;
// 			return tmp;
// 		}

// 		tree_iter& operator--() {
// 			if (__p_node->left != nullptr)
// 				return tree_max(__p_node->left);
// 			node_pointer before = __p_node->parent;
// 			while (before != nullptr && __p_node == before->left)
// 			{
// 				__p_node = before;
// 				before = before->parent;
// 			}
// 			__p_node = before;
// 			return *this;
// 		}
// 		tree_iter operator--(int){
// 			tree_iter tmp(*this);
// 			if (__p_node->left != nullptr)
// 				return tree_max(__p_node->left);
// 			node_pointer before = __p_node->parent;
// 			while (before != nullptr && __p_node == before->left)
// 			{
// 				__p_node = before;
// 				before = before->parent;
// 			}
// 			__p_node = before;
// 			return tmp;
// 		}

// 		friend bool operator==(const tree_iter& __x, const tree_iter& __y)
// 			{return __x.__p_node == __y.__p_node;}

// 		friend bool operator!=(const tree_iter& __x, const tree_iter& __y)
// 			{return __x.__p_node != __y.__p_node;}