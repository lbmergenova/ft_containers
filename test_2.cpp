// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

int main() {

  short int i = 1;    // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;

  return 0;
}


// equal algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::equal
#include <vector>       // std::vector

bool mypredicate (int i, int j) {
  return (i==j);
}

int main () {
  int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
  std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

  // using default comparison:
  if ( std::equal (myvector.begin(), myvector.end(), myints) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  myvector[3]=81;                                 // myvector: 20 40 60 81 100

  // using predicate comparison:
  if ( std::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  return 0;

}


#include <iostream>
#include <iterator>
#include <vector>
#include <list>
 
template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}
 
// int main()
// {
//     std::vector<int> v{1, 2, 3, 4, 5};
//     my_reverse(v.begin(), v.end());
//     for (int n : v) {
//         std::cout << n << ' ';
//     }
//     std::cout << '\n';
 
//     std::list<int> l{1, 2, 3, 4, 5};
//     my_reverse(l.begin(), l.end());
//     for (int n : l) {
//         std::cout << n << ' ';
//     }
//     std::cout << '\n';
 
//     int a[] = {1, 2, 3, 4, 5};
//     my_reverse(a, a + std::size(a));
//     for (int n : a) {
//         std::cout << n << ' ';
//     }
//     std::cout << '\n';
 
// //    std::istreambuf_iterator<char> i1(std::cin), i2;
// //    my_reverse(i1, i2); // compilation error
 
// }


#include <iostream>
#include <iterator>
 
template<typename T, size_t SIZE>
class Stack {
    T arr[SIZE];
    size_t pos = 0;
public:
    T pop() {
        return arr[--pos];
    }
    Stack& push(const T& t) {
        arr[pos++] = t;
        return *this;
    }
    // we wish that looping on Stack would be in LIFO order
    // thus we use std::reverse_iterator as an adaptor to existing iterators
    // (which are in this case the simple pointers: [arr, arr+pos)
    auto begin() {
        return std::reverse_iterator(arr + pos);
    }
    auto end() {
        return std::reverse_iterator(arr);
    }
};
 
int main() {
    Stack<int, 8> s;
    s.push(5).push(15).push(25).push(35);
    for(int val: s) {
        std::cout << val << ' ';
    }
}