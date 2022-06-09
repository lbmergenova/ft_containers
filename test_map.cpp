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

#define MAX_RAM 4294967296

#define COUNT 5

int main(int argc, char** argv) {

    std::cout << "____________" << TYPE << "____________" << std::endl;
	// ft::map<int, int> mp;
	
	// for (int i = 0, j = 10; i < COUNT; ++i, ++j)
	// {
	// 	mp.insert(ft::make_pair<int, int>(i, j));
	// }
    // for (int i = 2; i < 10; i++)
    // {
    //     mp.insert(ft::make_pair<int, int>(i, 15));
    // }

    // std::cout << "//--//--//--MP/--//--//--//" << std::endl;

    // ft::map<int, int> mp2(mp.begin(), mp.end());
    // // mp.tree_print();
    // std::cout << mp.size() << std::endl;

    // ft::map<int,int>::iterator it;
    // it = mp.find(3);
    // if (it != mp.end())
    //     std::cout << "find " << it->second << std::endl;
    // else
    //     std::cout << "not find" << std::endl;

    // // ft::map<int, int>::iterator it = mp.begin();
    // // std::cout << it->first << std::endl;

    // // std::cout << "//--//--//--MP2/--//--//--//" << std::endl;

    // // mp2.clear();

    // std::cout << "**************************" << std::endl;
    // {
    //     ft::map<int, int>::iterator it = mp2.begin();
    //     ft::map<int, int>::iterator it_end = mp2.end();
    //     // std::cout << &it << std::endl;
    //     // std::cout << &it_end << std::endl;
    //     std::cout << std::endl;
    //     int i = -1;
    //     while (it != it_end)
    //     {
    //         // std::cout << &it << std::endl;
    //         std::cout << ++i << ": " << it->first << " " << it->second << std::endl;
    //         it++;
    //         // std::cout << " NNN " << std::endl;
    //     }
    //     std::cout << "//--//--//--" << std::endl;
    // }
    // std::cout << "**************************" << std::endl;

    // ft::pair<ft::map<int, int>::iterator , bool> pair2 = mp.insert(ft::make_pair(9, 9));

    // {
    //     ft::map<int, int>::iterator it = mp.end();
    //     ft::map<int, int>::iterator it_end = mp.begin();
    //     std::cout << &it << std::endl;
    //     std::cout << &it_end << std::endl;
    //     std::cout << std::endl;
    //     while (--it != it_end)
    //     {
    //         std::cout << &it << std::endl;
    //         std::cout << " TTT " << " " << it->first << " " << it->second << std::endl;
    //         std::cout << " NNN " << std::endl;
    //     }
        
    //     std::cout << "//--//--//--" << std::endl;
    // }

    // {
    //     ft::map<int, int> mp;
    //     ft::pair<ft::map<int, int>::iterator , bool> pair = mp.insert(ft::make_pair(7, 77));
    //     ft::map<int, int>::iterator it = mp.begin();
    //     mp.insert(ft::make_pair(9, 9));
    //     ft::pair<ft::map<int, int>::iterator , bool> pair2 = mp.insert(ft::make_pair(9, 99));
    //     ft::map<int, int>::iterator it2 = pair.first;

    //     ft::map<int, int>::iterator itt = mp.begin();
    //     ft::map<int, int>::iterator itt_end = mp.end();
    //     int i = -1;
    //     while (itt != itt_end)
    //     {
    //         std::cout << ++i << ": " << itt->first << " " << itt->second << std::endl;
    //         itt++;
    //     }

    //     for (int i = 0, j = 0; i < 12; ++i, ++j) {
    //         // std::cout << "** " << i << std::endl;
    //         mp.insert(ft::make_pair(i, j));
    //     }

    //     // itt = mp.begin();
    //     // itt_end = mp.end();
    //     // while (itt != itt_end)
    //     // {
    //     //     std::cout << ++i << ": " << itt->first << " " << itt->second << std::endl;
    //     //     itt++;
    //     // }
        
    // }

    // find test
    // {
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
    {
        std::cout << "ERASE TESR" << std::endl;
        ft::map<int, int> mp;
        int _ratio = 10;
        std::cout << "number of erase " << mp.erase(3) << std::endl;
        for (int i = 0, j = 0; i < 1 * _ratio; ++i, ++j)
            mp.insert(ft::make_pair(i, j));
        ft::map<int,int>::iterator it = mp.begin();
        std::cout << it->first <<std::endl;
        std::cout << "number of erase " << mp.erase(-5) << ", current size:" << mp.size() << std::endl;
        std::cout << "number of erase " << mp.erase(0) << ", current size:" << mp.size() << std::endl;
        // ft::map<int,int>::iterator it4 = mp.begin();
        // g_start2 = timer();
        // int i = -1;
        // for (; it4 != mp.end() && i < 10; it4 = mp.begin())
        //     std::cout << ++i << ": number of erase " << mp.erase(it4->first) << ", current size:" << mp.size() << std::endl;
        // // g_end2 = timer();
        // ft::map<int, int>::iterator it2 = mp.end();
        // std::cout << "number of erase " << mp.erase(30 * _ratio - 1) << ", current size:" << mp.size() << std::endl;
        // ft::map<int, int> mp2;
        // for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        //     mp2.insert(ft::make_pair(i, j));
        // std::cout << " number of erase " << mp.erase(2) << ", current size:" << mp.size() << std::endl;
        // std::cout << " number of erase " << mp.erase(7) << ", current size:" << mp.size() << std::endl;
        // ft::map<int, int>::iterator it3 = mp.begin();
        // for (; it3 != mp.end(); ++it3) {
        //     std::cout << "MP  key: " << it3->first << " value: " << it3->second << std::endl;
        // }
        // std::cout << "Current size:" << mp.size() << std::endl;
    }

	std::cout << std::endl;
	return (0);
}