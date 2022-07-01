#include <type_traits>
#include <iostream>
#include <algorithm>
//#define STD_is_base
//#define Find_First_Of
#define equal_mismatch
#ifdef STD_is_base
struct base
{
    int val;
};

struct derived
    : public base
{
};
#endif // STD_is_base
#ifdef Find_First_Of   
template <class It, class FwdIt>
It first_find_of(It begin, It end, FwdIt targetfirst, FwdIt targetlast) {
    return std::find_if(begin, end, [&](auto&& e) {
        return std::any_of(targetfirst, targetlast, [&](auto&& t) {
            return e == t;
            });
        });
}

template <class It, class FwdIt, class BinaryPredicate>
It first_find_of(It begin, It end, FwdIt targetfirst, FwdIt targetlast,
    BinaryPredicate bp)
{
    return std::find_if(begin, end, [&](auto&& e) {
        return std::any_of(targetfirst, targetlast, [&](auto&& t) {
            return p(e, t);
            });
        });
}
#endif
#ifdef equal_mismatch
    template<class T> constexpr bool is_random_access_iterator_v = 
#endif // equal_mismatch

int main()
{
#ifdef STD_is_base
    std::cout << "is_base_of<base, base> == " << std::boolalpha
        << std::is_base_of<base, base>::value << std::endl;
    std::cout << "is_base_of<base, derived> == " << std::boolalpha
        << std::is_base_of<base, derived>::value << std::endl;
    std::cout << "is_base_of<derived, base> == " << std::boolalpha
        << std::is_base_of<derived, base>::value << std::endl;
#endif // STD_is_base
#ifdef Find_First_Of
    std::istream_iterator<char> ii(std::cin);
    std::istream_iterator<char> iend{};
    std::string s = "hello";
    first_find_of(ii, iend, s.begin(), s.end());
#endif // Find_First_Of
    

    return 0;
}