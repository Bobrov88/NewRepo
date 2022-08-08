#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <tuple>
#include <variant>
#include <cassert>

//#define VARIANT


#ifdef VARIANT	
struct A {
	A() { throw "Ha ha!"; }
};
struct B {
	operator int() { throw "ha ha!"; }
};
struct C {
	C() = default;
	C& operator=(C&&) = default;
	C(C&&) { throw "Ha ha!"; }
};
#endif
enum class Color {
	RED = 1,
	BLACK = 2
};
enum class Size {
	SMALL = 1,
	MEDIUM = 2,
	LARGE = 3
};
template <typename...Ts>
auto sum(Ts...ts) {
	return (ts + ...);
}

using sixtype = std::pair<Color, Size>;
//using fivetype = std::variant<Color, Size>; ??
using Author = std::pair<std::string, std::string>;
int main() {
	int result = 0;
	auto task = [](int& r) {r = 42; };
	std::thread t(task, std::ref(result));
	t.join();
	//std::vector<Author> authors = {
	//	{"Fyodor","Dosoevskiy"},
	//	{"Aleksandr","Pushkin"},
	//	{"Afanasiy", "Fet"},
	//	{"Joahn", "Rowling"} };
	//std::sort(authors.begin(), authors.end(), [](auto&& a, auto&& b) {
	//	return std::tie(a.second, a.first) < std::tie(b.second, b.first);
	//	});
	//auto A = std::make_tuple( 1, 3, 4 );
	//std::cout << std::get<0>(A);
	//std::cout << std::tuple_size_v<decltype(A)>;
	
	//std::variant<int, double> v1;
	//v1 = 1;
	//assert(v1.index() == 0);
	//assert(std::get<0>(v1) == 1);
	//try {
	//	std::cout << std::get<int>(v1) << std::endl;
	//}
	//catch (const std::bad_variant_access&) {};
	//if (v1.index() == 0) {
	//	std::cout << std::get<int>(v1) << std::endl;
	//}
	//if (std::holds_alternative<int>(v1)) {
	//	std::cout << std::get<int>(v1) << std::endl;
	//}
	//if (int* p = std::get_if<int>(&v1)) {
	//	std::cout << *p << std::endl;
	//}
#ifdef VARIANT
	
	std::variant<int, A, C> v1 = 42;
	std::variant<int, A, C> v2 = 42;
	try {
		v1.emplace<A>();
	}
	catch (const char* haha) {}
	assert(v1.valueless_by_exception());

	try {
		v1.emplace<int>(B());
	}
	catch (const char* haha) {};
	assert(v1.valueless_by_exception());
#endif
//	std::cout << double();
//	std::is_default_constructible_v<int>;
	int theSum{ sum(1,2,3,4,5) };
	std::cout << theSum;
	return 0;

}
