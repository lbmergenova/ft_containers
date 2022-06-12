#include <iostream>
#include <string>
#include <deque>

# ifndef FLAG
#  define FLAG 0
# endif

#if FLAG //CREATE A REAL STL EXAMPLE
	#include <map>
	namespace ft = std;
    #define TYPE "STD" 
#else
	#include "map.hpp"
    #define TYPE "FT"
#endif

#include <stdlib.h>

#define COUNT 5

// void print_tree(ft::map<int, int>::iterator first, ft::map<int, int>::iterator last, int size )
// {
//     int i = -1;
//     std::cout << "PRINT TREE size: " << size << std::endl;
//     while (first != last)
//     {
//         std::cout << ++i << "  : " << first->first << " " << first->second << std::endl;
//         first++;
//     }
// }

// void revers_print_tree(ft::map<int, int>::iterator first, ft::map<int, int>::iterator last, int size )
// {
//     int i = size;
//     std::cout << "PRINT REVERS TREE size: " << size << std::endl;
//     while (--first != last)
//     {
//         std::cout << --i << "  : " << first->first << " " << first->second << std::endl;
//     }
//     std::cout << "END REVERS PRINT" << std::endl;
// }

// ft::map<int, int> construct_map(ft::map<int, int> mp)
// {
//     std::cout << " f !!!" << std::endl;
//     ft::map<int, int> mp2(mp);
//     print_tree(mp.begin(), mp.end(), mp.size());
//     for (int i = 100, j = 10; i < 105; ++i, ++j) {
//         mp.insert(ft::make_pair(i, j));
//     }
//     return mp2;
// }

void fillMap(ft::map<int, int> &mp) {
	mp.insert(ft::make_pair(16, 3));
	mp.insert(ft::make_pair(8, 3));
	mp.insert(ft::make_pair(23, 3));
	mp.insert(ft::make_pair(7, 3));
	mp.insert(ft::make_pair(19, 3));
	// mp.insert(ft::make_pair(29, 3));
	// mp.insert(ft::make_pair(41, 3));
	// mp.insert(ft::make_pair(4, 3));
	// mp.insert(ft::make_pair(11, 3));
}


int main(int argc, char** argv) {
    int i = -1;
    int _ratio = 10;
    std::cout << "____________" << TYPE << "____________" << std::endl;

    {
        std::cout << "//--//--//--CONSTRUCTOR/--//--//--//" << std::endl;
        ft::map<int, int> mp;
        // mp.insert(ft::make_pair<int, int>(0, 15));
        // mp.insert(ft::make_pair<int, int>(5, 25));
        int koef = 30;
        for (int i = 0, j = 10; i < koef * _ratio; ++i, ++j) {
            mp.insert(ft::make_pair(i, j));
        }

        ft::map<int, int>::iterator it = mp.begin();
        std::cout << " MP = " << mp.size() << std::endl;
        std::cout << " MP first = " << it->first << std::endl;
        std::cout << "//--//--//--CONSTRUCTOR/--//--//--//" << std::endl;

        // ft::map<int, int> mp2(mp.begin(), mp.end());
        // std::cout << " MP = " << mp.size() << std::endl;
        // // print_tree(mp.begin(), mp.end(), mp.size());
        // std::cout << " MP2 = " << mp2.size() << std::endl;
        // // print_tree(mp2.begin(), mp2.end(), mp2.size());
        // std::cout << "//--//--//--END/--//--//--//" << std::endl;
    }

    // {
    //     std::cout << "//--//--//--CONSTRUCTOR COPY/--//--//--//" << std::endl;
    //     ft::map<int, int> mp;
    //     // for (int i = 0, j = 10; i < 10; ++i, ++j) {
    //     //     mp.insert(ft::make_pair(i, j));
    //     // }
    //     ft::map<int, int> mp2 = construct_map(mp);
    //     print_tree(mp.begin(), mp.end(), mp.size());
    // }

    // find test
    // {
    //     std::cout << "//--//--//--FIND/--//--//--//" << std::endl;
    //     int ft_ratio = 1;
    //     int begin = 10;
    //     int search = 5;
    //     ft::map<int, int> mp_f;
    //     std::cout << "FIND TESR" << std::endl;
    //     for (int i = -begin * ft_ratio, j = 0; i < begin * ft_ratio; ++i, ++j) {
    //         mp_f.insert(ft::make_pair(i, j));
    //     }
    //     ft::map<int, int>::iterator it_f = mp_f.find(search * ft_ratio);
    //     std::cout << it_f->first << " " << it_f->second << " " << mp_f.at(search * ft_ratio) << std::endl;
    //     it_f = mp_f.find(-search * ft_ratio);
    //     std::cout << it_f->first << " " << it_f->second << " " << mp_f.at(-search * ft_ratio) << std::endl;
    //     it_f = mp_f.find(-begin * ft_ratio);
    //     if (it_f == mp_f.end())
    //         std::cout << it_f->first << " " << it_f->second << std::endl;
    // }

    // erase test
    // {
    //     std::cout << "ERASE TESR" << std::endl;
    //     ft::map<int, int> mp;
    //     int _ratio = 5;
    //     std::cout << "number of erase " << mp.erase(3) << std::endl;
    //     for (int i = 0, j = 0; i < 1 * _ratio; ++i, ++j)
    //         mp.insert(ft::make_pair(i, j));
    //     // mp.insert(ft::make_pair(0, 0));
    //     // mp.insert(ft::make_pair(5, 5));
    //     ft::map<int,int>::iterator it = mp.begin();
    //     // print_tree(mp.begin(), mp.end(), mp.size());
    //     // std::cout << "number of erase " << mp.erase(-5) << ", current size:" << mp.size() << std::endl;
    //     print_tree(mp.begin(), mp.end(), mp.size());
    //     // std::cout << "number of erase " << mp.erase(0) << ", current size:" << mp.size() << std::endl;
    //     // mp.erase(mp.begin());
    //     mp.print_root();
    //     revers_print_tree(mp.end(), mp.begin(), mp.size());
    //     std::cout << "ERASE" << std::endl;
    //     mp.erase(mp.begin(), --mp.end());
    //     print_tree(mp.begin(), mp.end(), mp.size());
    //     // ft::map<int,int>::iterator it4 = mp.begin();
    //     // std::cout << "  " << it4->first << " " << it4->second << ", current size:" << mp.size() << std::endl;
    //     // g_start2 = timer();
    //     // int i = -1;
    //     std::cout << "ERASE" << std::endl;
    //     // for (; it4 != mp.end() && i < 10; it4 = mp.begin())
    //     //     std::cout << ++i << ": number of erase " << mp.erase(it4->first) << ", current size:" << mp.size() << std::endl;
    //     // // g_end2 = timer();
    //     // ft::map<int, int>::iterator it2 = mp.end();
    //     // std::cout << "number of erase " << mp.erase(30 * _ratio - 1) << ", current size:" << mp.size() << std::endl;
    //     // ft::map<int, int> mp2;
    //     // for (int i = 0, j = 0; i < 10 ; ++i, ++j)
    //     //     mp2.insert(ft::make_pair(i, j));
    //     // std::cout << " number of erase " << mp.erase(2) << ", current size:" << mp.size() << std::endl;
    //     // std::cout << " number of erase " << mp.erase(7) << ", current size:" << mp.size() << std::endl;
    //     // ft::map<int, int>::iterator it3 = mp.begin();
    //     // for (; it3 != mp.end(); ++it3) {
    //     //     std::cout << "MP  key: " << it3->first << " value: " << it3->second << std::endl;
    //     // }
    //     // std::cout << "Current size:" << mp.size() << std::endl;
    // }

    // {
    //     std::cout << "//--//--//--SWAP/--//--//--//" << std::endl;
    //     ft::map<int, int> mp;
    //     ft::map<int, int> mp2;
    //     mp.insert(ft::make_pair<int, int>(0, 15));
    //     mp.insert(ft::make_pair<int, int>(5, 25));
    //     int koef = 30;
    //     for (int i = 0, j = 10; i < koef * _ratio; ++i, ++j) {
    //         mp2.insert(ft::make_pair(i, j));
    //     }

    //     std::cout << " MP = " << mp.size() << std::endl;
    //     // print_tree(mp.begin(), mp.end(), mp.size());
    //     std::cout << " MP2 = " << mp2.size() << std::endl;
    //     // print_tree(mp2.begin(), mp2.end(), mp2.size());
    //     mp.swap(mp2);
    //     std::cout << " MP = " << mp.size() << std::endl;
    //     std::cout << " MP2 = " << mp2.size() << std::endl;
    //     std::cout << "//--//--//--END/--//--//--//" << std::endl;
    // }

    // {
    //      std::cout << "//--//--//--ITERATOR/--//--//--//" << std::endl;
    //     ft::map<int, int> mp;
    //     ft::map<int, int> mpp;
    //     fillMap(mpp);
    //     mpp.print_root();
    //     // for (ft::map<int, int>::iterator it = mpp.begin(); it != mpp.end(); it++) { std::cout << "key : " << it->first << std::endl; }
    //     print_tree(mpp.begin(), mpp.end(), mpp.size());
    //     for (ft::map<int, int>::iterator it = --mpp.end(); it != mpp.begin(); it--) { std::cout << "revoder key : " << it->first << std::endl; }
    //     ft::map<int, int> mp0;
    //     ft::map<int, int>::iterator ii = mp0.insert(ft::make_pair(3, 3)).first;
    //     ii++;
    //     std::cout <<"ii " << (--ii)->first << std::endl;
    //     for (int i = 0, j = 10; i < 5; ++i, ++j)
    //         mp.insert(ft::make_pair(i, j));
    //     ft::map<int, int>::iterator it = mp.begin();
    //     ft::map<int, int>::iterator it2 = mp.end();
    //     std::cout <<"it " << it->first << std::endl;
    //     it++;
    //     it++;
    //     it++;
    //     it++;
    //     std::cout <<"it " << it->first << std::endl;
    //     it++;
    //     it--;
    //     std::cout <<"it " << it->first << std::endl;
    //     it2--;
    //     std::cout <<"it2 " << it2->first << std::endl;
    //     std::cout <<"compar " << (it2 == it) << std::endl;
    //     std::cout <<"it2 " << (--it2)->first << std::endl;
    //     std::cout <<"it2 " << (it2--)->first << std::endl;
    //     std::cout <<"it2 " << (it2++)->first << std::endl;
    //     std::cout <<"it2 " << (++it2)->first << std::endl;
    //     std::cout << "//--//--//--END ITERATOR/--//--//--//" << std::endl;
    // }

    // {
    //      std::cout << "//--//--//--REVERSE ITERATOR/--//--//--//" << std::endl;
    //     ft::map<int, int> mp;
    //     ft::map<int, int> mpp;
    //     fillMap(mpp);
    //     // mpp.print_root();
    //     // for (ft::map<int, int>::iterator it = mpp.begin(); it != mpp.end(); it++) { std::cout << "key : " << it->first << std::endl; }
    //     print_tree(mpp.begin(), mpp.end(), mpp.size());
    //     // for (ft::map<int, int>::iterator it = --mpp.end(); it != mpp.begin(); it--) { std::cout << "revoder key : " << it->first << std::endl; }
    //     // ft::map<int, int> mp0;
    //     // ft::map<int, int>::iterator ii = mp0.insert(ft::make_pair(3, 3)).first;
    //     // ii++;
    //     // std::cout <<"ii " << (--ii)->first << std::endl;
    //     for (int i = 0, j = 10; i < 5; ++i, ++j)
    //         mp.insert(ft::make_pair(i, j));
    //     ft::map<int, int>::reverse_iterator it = mp.rbegin();
    //     ft::map<int, int>::reverse_iterator it2 = --mp.rend();
    //     std::cout <<"it " << it->first << std::endl;
    //     // it++;
    //     // it++;
    //     // it++;
    //     // it++;
    //     // std::cout <<"it " << it->first << std::endl;
    //     // it++;
    //     // it--;
    //     // std::cout <<"it " << it->first << std::endl;
    //     // it2--;
    //     std::cout <<"it2 " << it2->first << std::endl;
    //     // std::cout <<"compar " << (it2 == it) << std::endl;
    //     // std::cout <<"it2 " << (--it2)->first << std::endl;
    //     // std::cout <<"it2 " << (it2--)->first << std::endl;
    //     // std::cout <<"it2 " << (it2++)->first << std::endl;
    //     // std::cout <<"it2 " << (++it2)->first << std::endl;
    //     std::cout << "//--//--//--END ITERATOR/--//--//--//" << std::endl;
    // }
	// std::cout << std::endl;
	return (0);
}