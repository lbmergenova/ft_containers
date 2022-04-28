#include <iostream>
// #include <ostream>
#include <vector>
#include <stack>

int main()
{
    {
        std::vector<int> arr;
        std::cout << arr.size() << " " << arr.capacity() << " " << arr.max_size() << "\n";
        // for (int i = 0; i < 10; i++)
        // {
        //     arr.push_back(i);
        //     std::vector<int>::iterator it_begin = arr.begin();
        //     std::cout << &arr[i] << " " << arr.size() << " " << arr.capacity() << " " << arr.max_size() << "\n";
        // }
        std::cout << "___________________________________\n";
        std::vector<int> arr2(5,25);
        arr2.push_back(26);
        std::cout << " arr2 " << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        // for (int i = 0; i < arr2.size(); i++)
        // {
        //     std::cout << &arr2[i] << " " << arr2[i] << "\n";
        // }
        std::cout << "___________________________________\n";
        // arr2.insert(arr2.begin() + 3, arr.begin() + 1, arr.end());
        arr2.insert(arr2.begin() + 3, 2, 0);
        for (int i = 0; i < arr2.size(); i++)
        {
            std::cout << &arr2[i] << " " << i << " " << arr2[i] << "\n";
        }
        std::cout << &arr2 << " arr2 " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        std::cout << "___________________________________\n";
        // arr2.erase(arr2.begin() + 3, arr2.begin() + 4);
        arr2.erase(arr2.begin() + 3);
        for (int i = 0; i < arr2.size(); i++)
        {
            std::cout << &arr2[i] << " " << i << " " << arr2[i] << "\n";
        }
        std::cout << &arr2 << " arr2 " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
    }
    // {    
    //     std::vector<double> arr;
    //     std::cout << arr.size() << " " << arr.capacity() << " " << arr.max_size() << "\n";
    //     for (int i = 0; i < 10; i++)
    //     {
    //         arr.push_back(i);
    //         std::vector<double>::iterator it_begin = arr.begin();
    //         std::cout << &arr << " " << arr.size() << " " << arr.capacity() << " " << arr.max_size() << "\n";
    //     }
    // }
    
    // std::stack<int> s_arr;
    // std::stack<int> s_arr_rev;
    // for (int i = 0; i < 10; i++)
    // {
    //     s_arr.push(i);
    //     s_arr_rev.push(10-i);
    // }
    // s_arr.swap(s_arr_rev);

    return 0;
}