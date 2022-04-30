#include <iostream>
#include <vector>
#include <stack>

int main()
{
    {
        std::vector<int> arr;
        std::cout << arr.size() << " " << arr.capacity() << " " << arr.max_size() << "\n";
        int i = 0;
        for (int i = 0; i < 10; i++)
        {
            arr.push_back(i);
            std::vector<int>::iterator it_begin = arr.begin();
            std::cout << &arr << " " << arr.size() << " " << arr.capacity() << " " << arr.max_size() << "\n";
        }
    }

    std::pair<int, double> pair(1, 1.5);
    std::pair<int, double> pair2;
    std::pair<int, int> pair3(pair);
    pair2 = std::make_pair(2, 3.5);
    pair.swap(pair2);

    std::cout << pair3.first << " "<< pair3.second << std::endl;


    return 0;
}