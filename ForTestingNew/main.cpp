//#include <type_traits>
//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <list>
//#include <cassert>
//#include <numeric>
//#include <xmemory>
//#include <new>
////----------------------------------------------------------
////#define STD_is_base
////#define Find_First_Of
////#define equal_mismatch
//#ifdef STD_is_base
//struct base
//{
//    int val;
//};
//
//struct derived
//    : public base
//{
//};
//#endif // STD_is_base
//#ifdef Find_First_Of   
//template <class It, class FwdIt>
//It first_find_of(It begin, It end, FwdIt targetfirst, FwdIt targetlast) {
//    return std::find_if(begin, end, [&](auto&& e) {
//        return std::any_of(targetfirst, targetlast, [&](auto&& t) {
//            return e == t;
//            });
//        });
//}
//
//template <class It, class FwdIt, class BinaryPredicate>
//It first_find_of(It begin, It end, FwdIt targetfirst, FwdIt targetlast,
//    BinaryPredicate bp)
//{
//    return std::find_if(begin, end, [&](auto&& e) {
//        return std::any_of(targetfirst, targetlast, [&](auto&& t) {
//            return p(e, t);
//            });
//        });
//}
//#endif
//#ifdef equal_mismatch
//   // template<class T> constexpr bool is_random_access_iterator_v = 
//#endif // equal_mismatch
////----------------------------------------------------------
//int main()
//{
//    std::vector<int> v1{ 1,6,-5,2,-3,8,0,3,7,9,3 };
//    std::vector<int> v2{ 1,6,-5,2,-3,8,0,3,7,9,3 };
//    std::vector<int> v3{ 1,1,-5,1,-2,8,8,3 };
//
//    std::list<double> l1{ 1.5, 2.1, -6.7,0.6,4.7,2.6,2.4 };
//    std::list<double> l2{ 1.5, 2.1, -6.7,0.6,4.7,2.6,2.4 };
//    std::list<double> l3{ 2.5, 2.2, -6.1,0.1,0 };
//
//    //assert(std::count_if(v1.begin(), v1.end(), [](int& a) {
//    //    return a > 0; }) == 8);
//    //assert(std::distance(l2.begin(), l2.end()) == 7);
//    //assert(std::distance(v1.begin(), v1.end()) == 11);
//    //assert(std::count(v2.begin(), v2.end(), 3) == 2);
//    //assert(std::all_of(l3.begin(), l3.end(), [](double& d) {
//    //    return d < 10.0; }) == true);
//    //assert(std::any_of(v3.begin(), v3.end(), [](int& a) {
//    //    return a < -4; }) == true);
//    //assert(std::none_of(v3.begin(), v3.end(), [](int& a) {
//    //    return a > -6; }) == false);
//    //assert(std::find(l3.begin(), l3.end(), 2.5) == l3.begin());
//    //assert(*(std::find_if(v1.begin(), v1.end(), [](int& l) {
//    //    return l == 0; })) == 0);
//    //assert(std::find_if_not(v3.begin(), v3.end(), [](int& v) {
//    //    return v > 10; }) == v3.begin());
//    //assert(std::find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end(), [](int& a, int& b) {
//    //    return a == b; }) == v1.begin());
//    //assert(std::find_if(v1.begin(), v1.end(), [&](int& v) {
//    //    return std::any_of(v3.begin(), v3.end(), [&](int& b) {
//    //        return v == b;}); }) == v1.begin());*//*
//    //assert(std::equal(v1.begin(), v1.end(), v2.begin(), v2.end()) == true);
//    //assert(std::equal(v1.begin(), v1.end(), v3.begin(), v3.end()) == false);
//    //auto result = std::mismatch(v1.begin(), v1.end(), v3.begin(), v3.end(), [](int& a, int& b) {
//    //    return (a == b); });
//    //assert(result.first == v1.begin()+1);
//    //assert(result.second == v3.begin()+1);
//
//    std::vector<int> from_v1_v2(v1.size() + v2.size());
//    //std::copy(v1.begin(), v1.end(), std::back_inserter(from_v1_v2));
//  //  std::copy(v1.begin(), v1.end(), from_v1_v2.begin());
//    std::vector<double> from_l1(20);
//    //assert(from_l1.size() == 0);
//    //std::move(l1.begin(), l1.end(), std::back_inserter(from_l1));
//  //  std::move(l1.begin(), l1.end(), from_l1.begin());
//    //typedef std::list<int>::iterator Iter;  Doesn't work
//    //std::copy(std::move_iterator<Iter>(l1.begin()), std::move_iterator<Iter>(l1.end()), from_l1.begin()); Doesn't work
//    /*assert(from_l1.size() == 7);*/
//
//   // std::transform(v1.begin(), v1.end(), std::back_inserter(from_v1_v2), [](int& a) {
//   //    return a * 2; });
//    size_t i = 0;
//    //    std::fill(from_l1.begin(), from_l1.end(), i++);
//      //  std::iota(from_l1.begin(), from_l1.end(), i++);
//        /*std::generate(from_l1.begin(), from_l1.end(), [&]() {   return i+=rand()%12; });
//        std::sort(from_l1.begin(), from_l1.end(), [](double& element1, double& element2) {
//            return element1 > element2; });
//        std::stable_sort(from_l1.begin(), from_l1.end(), [](const double& element1, const double& element2) {
//            return element1 < element2; });
//        std::pair<int, int> Pair{ 0,1 };
//        std::cout << Pair.first << " " << Pair.second << std::endl;
//        std::swap(Pair.first, Pair.second);
//        std::cout << Pair.first << " " << Pair.second << std::endl;
//        std::reverse(l2.begin(), l2.end());*/
//        //std::partition(v1.begin(), v1.end(), [](int& element) {
//        //    return element > 0; });
//        //std::cout << std::is_partitioned(v1.begin(), v1.end(), [](int& element) {
//        //    return element > 0; }) << std::endl;
//        //std::cout << *(std::partition_point(v1.begin(), v1.end(), [](int& element) {
//        //    return element > 0; }));
//        //std::partition_copy(v1.begin(), v1.end(), v2.begin(), v3.begin(), [](int& element) {
//        //    return element > 0;});
//
//        /*std::copy_if(l1.begin(), l1.end(), from_l1.begin(), [](double& element) {
//            return element > 3; });*/
//
//            //  std::remove_copy_if(v1.begin(), v1.end(), from_v1_v2.begin(), [](int& element) {
//            //      return element > 4; });
//
//           //  std::cout<<*(std::rotate(v2.begin(), find(v2.begin(), v2.end(), 3), v2.end()));
//    std::vector<int> Z{ 1,2,3 };
//    std::vector <std::vector<int>> ZZ;
//    for (size_t i = 0; i < 6; i++) {
//        ZZ.push_back(Z);
//        std::next_permutation(Z.begin(), Z.end());
//    }
//
//    //  std::cout<<std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
//
//     // std::make_heap(v2.begin(), v2.end());
//     // std::push_heap(v2.begin(), v2.end());
//     // std::pop_heap(v2.begin(), v2.end());
//   //   std::sort(v2.begin(), v2.end());
//
//#ifdef STD_is_base
//    std::cout << "is_base_of<base, base> == " << std::boolalpha
//        << std::is_base_of<base, base>::value << std::endl;
//    std::cout << "is_base_of<base, derived> == " << std::boolalpha
//        << std::is_base_of<base, derived>::value << std::endl;
//    std::cout << "is_base_of<derived, base> == " << std::boolalpha
//        << std::is_base_of<derived, base>::value << std::endl;
//#endif // STD_is_base
//#ifdef Find_First_Of
//    std::istream_iterator<char> ii(std::cin);
//    std::istream_iterator<char> iend{};
//    std::string s = "hello";
//    first_find_of(ii, iend, s.begin(), s.end());
//#endif // Find_First_Of
//    //  std::iter_swap(v1.begin(), find(v1.begin(), v1.end(), 0));
//    auto pos = find(v1.begin(), v1.end(), 8);
//    //std::sort(v1.begin(), pos);
//    //std::sort(pos, v1.end());
//    //std::inplace_merge(v1.begin(), pos, v1.end());
//   // std::sort(v1.begin(), v1.end());
//    //std::sort(v2.begin(), v2.end());
//    // std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), from_v1_v2.begin());
//   // std::cout << *(std::lower_bound(v1.begin(), v1.end(), 4))<<std::endl;
//   // std::cout << *(std::upper_bound(v1.begin(), v1.end(), 1))<<std::endl;
//    v1.erase(std::remove_if(v1.begin(), v1.end(), [](int& element) {
//        return element % 3 == 0; }), v1.end());
//    std::cout << v1.size() << std::endl;
//    std::cout << v3.size() << std::endl;
//    v3.erase(std::unique(v3.begin(), v3.end()),v3.end());
//    //v3.erase(std::unique(v3.begin(), v3.end()), v3.end());
//    std::cout << v3.size() << std::endl;
//    return 0;
//}

#include<iostream>

class Fraction
{
	int numerator;
	int denominator;
public:

	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int den)
	{
		if (den != 0)
			denominator = den;
		else
			cout << "Знаменатель не может быть равен нулю: " << endl;
	}
	int get_numerator()
	{
		return numerator;
	}
	int get_denominator()
	{
		return denominator;
	}
	Fraction(int num = 0, int den = 1)
	{
		numerator = num;
		set_denominator(den);
	}
	Fraction(const Fraction& other)
	{
		//Fraction f1;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
	}
	void Reduce(Fraction& f)
	{
		while (f.numerator > 0 && f.denominator > 0)
			if (f.numerator > f.denominator) f.numerator %= f.denominator;
			else f.denominator %= f.numerator;
	}

	void Print()
	{
		cout << numerator << "/" << denominator;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	Fraction f(2, 8);
	f.Reduce(f);
	f.Print();
	return 0;
}