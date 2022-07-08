#include<iostream>
#include <array>
#include <vector>
#include <list>
#include <cassert>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>


//std::array<int,3> cross_product(const std::array<int, 3>& a, const std::array<int, 3>& b)
//{
//	return { {
//			a[1] * b[2] - a[2] * b[1],
//			a[2] * b[0] - a[0] * b[2],
//			a[0] * b[1] - a[1] * b[0]
//		} };
//}
//
//struct Bad {
//	int x = 0;
//	Bad() = default;
//	Bad(const Bad&) { puts("copy Bad"); }
//	Bad(Bad&&) { puts("move Bad"); }
//};
//
//struct Good {
//	int x = 0;
//	Good() = default;
//	Good(const Good&) { puts("copy Good"); }
//	Good(Good&&) noexcept { puts("move Good"); }
//};
//
//class ImplicitlyGood {
//	std::string x;
//	Good y;
//};
//
//class ImplicitlyBad {
//	std::string x;
//	Bad y;
//};
//
//template<class T>
//void test_resizing() {
//	std::vector<T> vec(1);
//	vec.resize(vec.capacity() + 1);
//}
template <class T>
class _CreateVector {
public:
	_CreateVector() {
		v.reserve(2); v.at(0) = 0;
	};
	_CreateVector(T _begin, T _end, size_t _number_of_values) {
		if (_end - _begin == 0) ++_end;
		srand(time(NULL));
		v.resize(_number_of_values);
		while (_number_of_values) {
			v.emplace_back(rand() % (_end - _begin) + _begin);
			--_number_of_values;
		}
	}
	_CreateVector(const _CreateVector& _other_obj) {
		this->v.resize(_other_obj.v.size());
		std::copy(_other_obj.v.begin(),
			_other_obj.v.end(),
			this->v.begin());
	}
	_CreateVector(const _CreateVector&& _other_obj) noexcept{
		this->v.resize(_other_obj.v.size());
		std::move(_other_obj.v.begin(),
			_other_obj.v.end(),
			this->v.begin());
	}

	_CreateVector& operator+(const _CreateVector& _other_obj) {
		auto begin = this->v.begin();
		std::merge(this->v.begin(), this->v.end(), _other_obj.v.begin(), _other_obj.v.end(), begin);
		return *this;
	}

private:
	std::vector<T> v;
};

int main() {

	_CreateVector<int> _CVI(10,20,6);
	_CreateVector<int> _CVI_copy(_CVI);
	_CreateVector<int> _CVI_move = _CreateVector(20, 20, 5) + _CreateVector(10, 20, 4);
	/*std::array<int, 3> A{ 1,2,3 };
	std::array<int, 3> B{ 4,5,6 };
	auto C = cross_product(A, B);*/

	/*test_resizing<Good>();
	test_resizing<Bad>();
	test_resizing<ImplicitlyGood>();
	test_resizing<ImplicitlyBad>();*/

	/*std::list<int> L {3,1,4,1,5,9,2,6,5};
	auto begin = std::next(L.begin(), 2);
	auto end = std::next(L.end(), -2);
	std::list<int> sub;
	sub.splice(sub.begin(), L, begin, end);
	sub.sort();
	L.splice(end, sub);
	assert(sub.empty());
	assert((L == std::list<int>{3,1,1,2,4,5,9,6,5}));*/

	//std::map<std::string, std::string> m;
	//m["hello"] = "world";
	//m["quick"] = "brown";
	//-----------
	//std::map<std::string, std::string> otherm{
	//	{"hello", "dolly"},
	//	{"sad", "clown"} };
	//-----------
	//using Pair = decltype(m)::value_type;
	//-----------
	//auto nh1 = otherm.extract("sad");
	//assert(nh1.key() == "sad" && nh1.mapped() == "clown");
	//auto [it2, inserted2, nh2] = m.insert(std::move(nh1));
	//assert(*it2 == (std::pair<const std::string, std::string> {"sad", "clown"}) && inserted2 == true && nh2.empty());
	//-----------
	//auto nh3 = otherm.extract("hello");
	//assert(nh3.key() == "hello" && nh3.mapped() == "dolly");
	//auto [it4, inserted4, nh4] = m.insert(std::move(nh3));
	//assert(*it4 == Pair("hello", "world") && inserted4 == false && !nh4.empty());
	//-----------
	//m.insert_or_assign(nh4.key(), nh4.mapped());
	//-----------
	//m.erase(it4);
	//m.insert(std::move(nh4));
	//assert(m.size() == 2);
	//assert(m["literally"] == "");
	//assert(m.size() == 3);

	return 0;
}