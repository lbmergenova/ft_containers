// #include <iostream>
// // #include "map.hpp"
// #include <map>
// #include <set>
// #include <utility>

// int main()
// {
//     std::map<int, int> m;
//     std::set<int> s;
//     std::pair<int, int> p;

//     return 0;
// }

#include <iostream>
// #include <ostream>
#include "vector.hpp"
#include <vector>
int main()
{
    {
        std::cout << "___________________________________\n";
        ft::vector<int> arr2(5,25);
        arr2.push_back(15);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        arr2.assign(6,10);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        ft::vector<int>::iterator it = arr2.begin();
        ft::vector<int>::const_iterator c_it = it + 5;
        arr2.insert(it, 200);

    }
    std::cout << "___________________________________\n";
    std::cout << "______________STL__________________\n";
    {
        std::cout << "___________________________________\n";
        std::vector<int> arr2(5,25);
        arr2.push_back(15);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        arr2.assign(6,10);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        std::vector<int>::iterator it = arr2.begin();
        arr2.insert(it, 200);
    }
    return 0;
}