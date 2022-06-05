#include <iostream>
#include <map>
#include <vector>
#include "rb_tree.hpp"
#include "pair.hpp"

// template <class T>
// void inorder_tree_walk(T _x)
// {
//     if (_x != nullptr)
//     {
//         inorder_tree_walk(_x->left);
//         prnt_node(_x);
//         inorder_tree_walk(_x->right);
//     }
// }

int main()
{
    std::map<int, int> arr;
    // ft::rb_tree<ft::pair<int, int> > tree;
    ft::rb_tree<ft::pair<int, int> > mp;
     
    int count = 3;

    std::vector<int> v;
    std::vector<ft::pair<int, int> > w;

    for (int i = 0, j = 10; i < count; ++i, ++j) {
        ft::pair<int, int> p(i,j);
        ft::Node<ft::pair<int, int> > n(p);
        std::cout << "begin add " << i << " elem: " << p.first << " " <<p.second <<std::endl;
        mp.insert(&n);
        std::cout << "finsh add " << i << " elem" <<std::endl;
    }

    // _map<int, int> mp2(mp.begin(), mp.end());
    // ft::rb_tree<ft::pair<int, int> >::iterator it = mp.begin();
    // for (int i = 0; i < count; ++i, it++) {
    //     v.push_back(it->first);
    //     v.push_back(it->second);
    // }
    std::cout << "//--//--//--END/--//--//--//" << std::endl;

    mp.tree_print();

    std::cout << mp.begin() << " " << mp.end() << std::endl;

    std::cout << "//--//--//--END/--//--//--//" << std::endl;
    // v.push_back(mp.begin()->value.first);
    // v.push_back(mp.begin()->value.second);
    // v.push_back(mp.end()->value.first);
    // v.push_back(mp.end()->value.second);

    // count = v.size();
    // for (int i = 0; i < count; i++)
    // {
    //     std::cout << v[i] << std::endl;
    // }
    // std::cout << "END" << std::endl;

    return 0;
}