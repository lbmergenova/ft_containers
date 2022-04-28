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
        for (int i = 0; i < arr2.size(); i++)
            {
                std::cout << &arr2[i] << " " << i << " " << arr2[i] << "\n";
            }

        // arr2.push_back(26);
        // std::cout << " arr2 " << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        // std::cout << "___________________________________\n";
        // ft::vector<int>::iterator it = arr2.begin();
        // ft::vector<int>::iterator it_end = arr2.end();
        // while (it != it_end)
        // {
        //     std::cout << "Iteraror " << *it << std::endl;
        //     it++;
        // }
        // std::cout << "___________________________________\n";
        // arr2.resize(7);
        // std::cout << "\n arr2 " << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
        // std::cout << "___________________________________\n";
        // for (int i = 0; i < arr2.size(); i++)
        // {
        //     std::cout << &arr2[i] << " " << i << " " << arr2[i] << "\n";
        // }

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
        for (int i = 0; i < arr2.size(); i++)
            {
                std::cout << &arr2[i] << " " << i << " " << arr2[i] << "\n";
            }
    //     std::cout << "___________________________________\n";
    //     std::vector<int> arr2(5,25);
    //     arr2.push_back(26);
    //     std::cout << " arr2 " << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
    //     std::cout << "___________________________________\n";
        // std::vector<int>::iterator it = arr2.begin();
        // std::vector<int>::iterator it_end = arr2.end();
        // while (it != it_end)
        // {
        //     std::cout << "Iteraror " << *it << std::endl;
        //     it++;
        // }
    //     arr2.resize(7);
    //     std::cout << "\n arr2 " << " " << arr2.size() << " " << arr2.capacity() << " " << arr2.max_size() << "\n";
    //     std::cout << "___________________________________\n";
    //     for (int i = 0; i < arr2.size(); i++)
    //     {
    //         std::cout << &arr2[i] << " " << i << " " << arr2[i] << "\n";
        // }
    }
    return 0;
}

// class B {
// public:
//     char *l;
//     int i;
//     B():l(nullptr), i(1) {};
//     B(const int &ex) {
//         this->i = ex;
//         this->l = new char('a');
//     };
//     virtual ~B() {
//         delete this->l;
//         this->l = nullptr;
//     };
// };

// class A : public B {
// public:
//     A():B(){};
//     A(const B* ex){
//         this->l = new char(*(ex->l));
//         this->i = ex->i;
//         if (ex->i == -1) throw "n";
//     }
//     ~A() {
//         delete this->l;
//         this->l = nullptr;
//     };
// };

// int main() {
// std::cout << "___________________________________\n";
//     {
//         std::vector<int> v;
//         std::vector<int> tmp;

//         std::unique_ptr<B> k2(new B(3));
//         std::unique_ptr<B> k3(new B(4));
//         std::unique_ptr<B> k4(new B(-1));
//         A a1(&(*k2));
//         std::vector<A> vv;
//         std::vector<B*> v1;

//         v1.push_back(&(*k2));
//         v1.push_back(&(*k3));
//         v1.push_back(&(*k4));
//         vv.push_back(a1);
//         vv.push_back(a1);
//         vv.push_back(a1);
//         vv.push_back(a1);
//         std::cout << vv.size() << " " << vv.capacity() << std::endl;
//         std::cout << v1.size() << " " << v1.capacity() << std::endl;
//         // vv.insert(vv.begin(), v1.begin(), v1.end());
//         try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
//         catch (...) {
//             std::cout << vv.size() << " " << vv.capacity() << std::endl;
//             v.push_back(vv.size());
//             v.push_back(vv.capacity());
//         }
//     }
// std::cout << "___________________________________\n" << std::endl;
//     {
//         std::vector<int> v;
//         ft::vector<int> tmp;

//         std::unique_ptr<B> k2(new B(3));
//         std::unique_ptr<B> k3(new B(4));
//         std::unique_ptr<B> k4(new B(-1));
//         A a1(&(*k2));
//         ft::vector<A> vv;
//         ft::vector<B*> v1;

//         v1.push_back(&(*k2));
//         v1.push_back(&(*k3));
//         v1.push_back(&(*k4));
//         vv.push_back(a1);
//         vv.push_back(a1);
//         vv.push_back(a1);
//         vv.push_back(a1);
//         std::cout << vv.size() << " " << vv.capacity() << std::endl;
//         std::cout << v1.size() << " " << v1.capacity() << std::endl;
//         try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
//         catch (...) {
//             std::cout << vv.size() << " " << vv.capacity() << std::endl;
//             v.push_back(vv.size());
//             v.push_back(vv.capacity());
//         }
//     }
// }

 
// void print_v(ft::vector<int> &vec) {
//     std::cout << "{ ";
//     ft::vector<int>::iterator it = vec.begin();
//     ft::vector<int>::iterator e_it = vec.end();
//     while (it != e_it)
//     {
//         std::cout << *it << " ";
//         it++;
//     }
//     std::cout << "} ";
// }

// int main()
// {
//     ft::vector<int> a1, a2;

//     a1.push_back(1);
//     a1.push_back(2);
//     a1.push_back(3);
//     a2.push_back(4);
//     a2.push_back(5);
 
//     ft::vector<int>::iterator it1 = a1.begin() + 1;
//     ft::vector<int>::iterator it2 = a2.begin() + 1;
 
//     int& ref1 = a1.front();
//     int& ref2 = a2.front();
 
//     std::cout << "a1 " << a1.size() << " " << a1.capacity() << std::endl;
//     std::cout << "a2 " << a2.size() << " " << a2.capacity() << std::endl;
//     print_v(a1);
//     print_v(a2);
//     std::cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
//     std::cout << "_________________________\n";
//     std::swap(a1, a2);
//     std::cout << "_________________________\n";
//     print_v(a1);
//     print_v(a2);
//     std::cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

//     std::cout << "a1 " << a1.size() << " " << a1.capacity() << std::endl;
//     std::cout << "a2 " << a2.size() << " " << a2.capacity() << std::endl;
 
//     // Note that after swap the iterators and references stay associated with their
//     // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
//     // still points to the same element, though this element was moved into 'a2'.
// }