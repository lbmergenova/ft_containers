#ifndef UTILITY_HPP
#define UTILITY_HPP

// #include <type_traits>
#include "pair.hpp"
#include "iterator_traits.hpp"

namespace ft
{

    struct true_type { static const bool value = true; };

    struct false_type { static const bool value = false; };

// is_same
    template <class T, class U> struct is_same : public false_type {};
    template <class T> struct is_same<T, T> : public true_type {};

// enable_if
    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> { typedef T type; };

// is_integral

    template <class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T                       value_type;
		typedef integral_constant       type;
		operator value_type() const { return (value); }
	};

    template <class T>   struct is_integral                     : public integral_constant<T, false> {};
    template <>          struct is_integral<bool>               : public integral_constant<bool, true> {};
    template <>          struct is_integral<char>               : public integral_constant<bool, true> {};
    template <>          struct is_integral<signed char>        : public integral_constant<bool, true> {};
    template <>          struct is_integral<unsigned char>      : public integral_constant<bool, true> {};
    template <>          struct is_integral<wchar_t>            : public integral_constant<bool, true> {};
    template <>          struct is_integral<char16_t>           : public integral_constant<bool, true> {};
    template <>          struct is_integral<char32_t>           : public integral_constant<bool, true> {};
    template <>          struct is_integral<short>              : public integral_constant<bool, true> {};
    template <>          struct is_integral<unsigned short>     : public integral_constant<bool, true> {};
    template <>          struct is_integral<int>                : public integral_constant<bool, true> {};
    template <>          struct is_integral<unsigned int>       : public integral_constant<bool, true> {};
    template <>          struct is_integral<long>               : public integral_constant<bool, true> {};
    template <>          struct is_integral<unsigned long>      : public integral_constant<bool, true> {};
    template <>          struct is_integral<long long>          : public integral_constant<bool, true> {};
    template <>          struct is_integral<unsigned long long> : public integral_constant<bool, true> {};
    template <>          struct is_integral<__int128_t>         : public integral_constant<bool, true> {};
    template <>          struct is_integral<__uint128_t>        : public integral_constant<bool, true> {};

// equal

    template <class InputIter1, class InputIter2, class BinaryPredicate>
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, BinaryPredicate pred)
    {
        while (first1!=last1) {
            if (!pred(*first1,*first2))
            return false;
            ++first1; ++first2;
        }
        return true;
    }

    template <class InputIter1, class InputIter2>
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
    {
        while (first1!=last1) {
            if (!(*first1 == *first2))
            return false;
            ++first1; ++first2;
        }
        return true;
    }
    
// lexicographical_compare
    template <class InputIter1, class InputIter2>
    bool lexicographical_compare (InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
    {
        for (; first2 != last2; ++first1, (void) ++first2)
        {
            if (first1 == last1 || *first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return false;
    }

    template<class InputIter1, class InputIter2, class Compare>
    bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Compare comp)
    {
        for (; first2 != last2; ++first1, (void) ++first2)
        {
            if (first1 == last1 || comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }
        return false;
    }

    template<class InputIter>
	typename ft::iterator_traits<InputIter>::difference_type distance (InputIter first, InputIter last)
	{
		typename ft::iterator_traits<InputIter>::difference_type n = 0;
		while (first++ != last)
			n++;
		return (n);
	}

} // namespace ft

#endif
