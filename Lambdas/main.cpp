#include <iostream>
#include <string>
#include <functional>
#include <deque>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::string;

//#define function_dynamic_definition
//#define functional_polymorph
#define concatinations
#ifdef functional_polymorph
static auto consumer(auto &container) {
	return [&container](auto value) { // container added? to avoid allocation much memory by enclosing with &
		container.push_back(value);
	};
}

static void print(const auto& c) {
	for (auto i : c) {
		std::cout << i << ", ";
	}
	std::cout << endl;
}
#endif // functional_polymorph

#ifdef concatinations
template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts) {
	if constexpr (sizeof...(ts) > 0) {
		return [=](auto...parameters) {
			return t(concat(ts...)(parameters...));
		};
	}
	else {
		return t;
	}
}
#endif // concatinations


int main() {

#ifdef concatinations
	auto twice([](int i) {return i * 2; });
	auto thrice([](int i) {return i * 3; });
	auto combined{
		concat(twice,thrice,std::plus<int>{})
	};
	std::cout << combined(2, 3) << endl;
#endif // concatinations


	{
#ifdef function_dynamic_definition
		auto just_one([]() { return 1; });
		auto just_two([]() { return 2; });
		cout << just_one() << ", " << just_two() << endl;
		auto plus([](auto l, auto r) { return l + r; });
		cout << plus(1, 2) << endl;
		cout << plus(string{ "a" }, "b") << endl;
		cout << plus(just_one(), just_two()) << endl;
		cout << [](auto l, auto r) {return l + r; } (1, 2) << endl;
		auto counter([count = 0]() mutable {return ++count; });
		for (size_t i{ 0 }; i < 5; ++i) {
			cout << counter() << ", ";
		}
		cout << endl;
		int a{ 0 };
		auto incrementer([&a] {++a; });
		incrementer();
		incrementer();
		incrementer();
		cout << "Value of 'a' after 3 incrementer() calls: " << a << endl;
		auto plus_ten([=](int x) {return plus(10, x); });
		cout << plus_ten(5) << "\n";
#endif // function_dynamic_definition
#ifdef functional_polymorph
	std::deque<size_t> d;
	std::list<size_t> l;
	std::vector<size_t> v;
	const std::vector<std::function<void(size_t)>> consumers { consumer(d), consumer(l), consumer(v) };
	for (size_t i{ 0 }; i < 10; ++i) {
		for (auto && consume : consumers) {
			consume(i);
		}
	}
	print(d);
	print(l);
	print(v);
#endif // functional_polymorph
	}


	return 1;
}