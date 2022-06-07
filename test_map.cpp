#include <iostream>
#include <map>
#include <vector>
#include "rb_tree.hpp"
#include "map.hpp"
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
{
    // std::map<int, int> arr;
    // std::set<int, int> arr;
    // ft::rb_tree<ft::pair<int, int> > tree;
    // ft::rb_tree<ft::pair<int, int> > mp;
    ft::map<int, int> mp;
     
    int count = 5;

    std::vector<int> v;
    std::vector<ft::pair<int, int> > w;

    // ft::pair<int, int> p1(1,11);
    // ft::Node<ft::pair<int, int> > n1(p1);
    // mp.insert(&n1);

    // ft::pair<int, int> p2(2,12);
    // ft::Node<ft::pair<int, int> > n2(p2);
    // mp.insert(&n2);

    // ft::pair<int, int> p3(3,13);
    // ft::Node<ft::pair<int, int> > n3(p3);
    // mp.insert(&n3);
    // mp.delete_node(mp.begin());

    for (int i = 0, j = 10; i < count; ++i, ++j) {
        // ft::pair<int, int> p(i,j);
        // ft::Node<ft::pair<int, int> > n(p);
        // std::cout << "begin add " << i << " elem: " << p.first << " " <<p.second <<std::endl;
        mp.insert( ft::make_pair<int, int>(i,j) );
        // std::cout << "finsh add " << i << " elem" <<std::endl;
    }

    ft::map<int, int> mp2(mp.begin(), mp.end());

    // _map<int, int> mp2(mp.begin(), mp.end());
    // ft::rb_tree<ft::pair<int, int> >::iterator it = mp.begin();
    // for (int i = 0; i < count; ++i, it++) {
    //     v.push_back(it->first);
    //     v.push_back(it->second);
    // }
    std::cout << "//--//--//--END/--//--//--//" << std::endl;

    mp.tree_print();

    ft::map<int, int>::iterator it = mp.begin();

    it++;
    it++;

    std::cout << mp.begin()->value.first << " " << it->value.second << " " << mp.end()->value.first << std::endl;

    // std::cout << "//--//--//--END/--//--//--//" << std::endl;
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

}
    // while (1) {}
    return 0;
}