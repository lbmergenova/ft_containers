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
        ft::vector<int> arr2(5,10);
        arr2.push_back(3);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        arr2.insert(arr2.begin(), 25, 0);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";

    }
    std::cout << "___________________________________\n";
    std::cout << "______________STL__________________\n";
    {
        std::cout << "___________________________________\n";
        std::vector<int> arr2(5,25);
        arr2.push_back(3);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        arr2.insert(arr2.begin(), 25, 0);
        std::cout << "\n arr " << " " << &arr2 << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        // std::vector<int>::iterator it = arr2.begin();
        // arr2.insert(it, 200);
    }
    return 0;
}