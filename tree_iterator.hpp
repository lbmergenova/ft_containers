#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

namespace ft
{
// // Node
// 	template <class T>
// 	struct Node
// 	{
// 	public:
// 		T*		p_value;
// 		Node*	parent;
// 		Node*	left;
// 		Node*	right;
// 		bool	red;
// 		bool	nil;

// 		Node(T* v = 0) : p_value(v), parent(nullptr), left(nullptr), right(nullptr), red(true), nil(false) {}
// 		Node(Node const &src){
// 			if (this != &src)
// 			{
// 				p_value = src.p_value;
// 				parent = src.parent;
// 				left = src.left;
// 				right = src.right;
// 				red = src.red;
// 				nil = src.nil;
// 			}
// 		}

// 		Node& operator=(Node const &src){
// 			if (this != &src)
// 			{
// 				p_value = src.p_value;
// 				parent = src.parent;
// 				left = src.left;
// 				right = src.right;
// 				red = src.red;
// 				nil = src.nil;
// 			}
// 			return *this;
// 		}

// 		~Node(){} // virtual
// 	};

// tree_iter
//________________________________________________________________________________________________________
//________________________________________________________________________________________________________

	template <class _TreeIter>
	class tree_iter
	{
	public:

		typedef _TreeIter													iterator_type; // _TreeIter = typename Node<value>::pointer
		typedef std::bidirectional_iterator_tag								iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		pointer	__p_node;

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

	public:
		tree_iter() {}

		tree_iter(pointer _x) : __p_node(_x) {}

		// tree_iter(_TreeIter __i) : __p_node(__i) {}

		reference operator*() const {return *(__p_node->value);}
		pointer operator->() const {return __p_node->value;}

		tree_iter& operator++() {
			if (__p_node->right != nullptr)
				return tree_min(__p_node->right);
			pointer next = __p_node;
			while (next != nullptr && __p_node == next->right)
			{
				__p_node = next;
				next = next->parent;
			}
			__p_node = next;
			return *this;
		}

		tree_iter operator++(int){
			tree_iter tmp(*this);
			if (__p_node->right != nullptr)
				return tree_min(__p_node->right);
			pointer next = __p_node->parent;
			while (next != nullptr && __p_node == next->right)
			{
				__p_node = next;
				next = next->parent;
			}
			__p_node = next;
			return tmp;
		}

		tree_iter& operator--() {
			if (__p_node->left != nullptr)
				return tree_max(__p_node->left);
			pointer before = __p_node->parent;
			while (before != nullptr && __p_node == before->left)
			{
				__p_node = before;
				before = before->parent;
			}
			__p_node = before;
			return *this;
		}
		tree_iter operator--(int){
			tree_iter tmp(*this);
			if (__p_node->left != nullptr)
				return tree_max(__p_node->left);
			pointer before = __p_node->parent;
			while (before != nullptr && __p_node == before->left)
			{
				__p_node = before;
				before = before->parent;
			}
			__p_node = before;
			return tmp;
		}

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