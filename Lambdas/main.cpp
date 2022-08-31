#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <deque>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

using std::cout;
using std::endl;
using std::string;

//#define function_dynamic_definition
//#define functional_polymorph
//#define concatinations
//#define difficult_predicate
//#define unpacking_by_initializer
//#define transform_if
#define decart_set


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
#ifdef difficult_predicate
static bool begins_with_a(const std::string& s) {
	return s.find("a") == 0;
}
static bool ends_with_b(const std::string& s) {
	return s.rfind("b") == s.length() - 1;
}
template<typename A, typename B, typename F>
auto combine(F binary_func, A a, B b) {
	return [=](auto param) {
		return binary_func(a(param), b(param));
	};
}
#endif // difficult_predicate
#ifdef unpacking_by_initializer
static auto multicall(auto ...functions) {
	return [=](auto x) {
		(void)std::initializer_list<int> {
			((void)functions(x), 0)...
		};
	};
}

static auto for_each(auto f, auto ...xs) {
	(void)std::initializer_list<int> {
		((void)f(xs), 0)...
	};
}

static auto brace_print(char a, char b) {
	return [=](auto x) {
		std::cout << a << x << b << ",";
	};
#endif // unpacking_by_initializer
#ifdef transform_if
	template <typename T>
	auto map(T fn) {
		return [=](auto reduce_fn) {
			return [=](auto accum, auto input) {
				return reduce_fn(accum, fn(input));
			};
		};
	}
	template <typename T>
	auto filter(T predicate) {
		return [=](auto reduce_fn) {
			return [=](auto accum, auto input) {
				if (predicate(input))
					return reduce_fn(accum, input);
				else return accum;
			};
		};
	}
#endif // transform_if
#ifdef decart_set
	static void print(int x, int y) {
		std::cout << "(" << x << ", " << y << ")\n";
	}
#endif // decart_set


	int main() {

#ifdef decart_set
		constexpr auto call_cart(
			[=](auto f, auto x, auto ...rest) constexpr {
				(void)std::initializer_list<int> {
					(((x < rest) ? (void)f(x, rest) : (void)0), 0)...
				};
			});
		constexpr auto cartesian([=](auto ...xs) constexpr {
			return [=](auto f) constexpr {
				(void)std::initializer_list<int>{
					((void)call_cart(f, xs, xs...), 0)...
				};
			};
			});
		constexpr auto print_cart (cartesian(1, 2, 3));
	//	print_cart(print);
#endif // decart_set

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
			const std::vector<std::function<void(size_t)>> consumers{ consumer(d), consumer(l), consumer(v) };
			for (size_t i{ 0 }; i < 10; ++i) {
				for (auto&& consume : consumers) {
					consume(i);
				}
			}
			print(d);
			print(l);
			print(v);
#endif // functional_polymorph
#ifdef concatinations
			auto twice([](int i) {return i * 2; });
			auto thrice([](int i) {return i * 3; });
			auto combined{
				concat(twice,thrice,std::plus<int>{})
			};
			std::cout << combined(2, 3) << endl;
#endif // concatinations
#ifdef difficult_predicate
			std::ifstream infile("1.txt");
			std::ofstream outfile("2.txt");
			auto a_xxx_b(combine(std::logical_and<>{}, begins_with_a, ends_with_b));
			std::copy_if(std::istream_iterator<string>(infile), {},
				std::ostream_iterator<string>(outfile, ", "), a_xxx_b);
#endif // difficult_predicate
#ifdef unpacking_by_initializer
			auto f(brace_print('(', ')'));
			auto g(brace_print('[', ']'));
			auto h(brace_print('{', '}'));
			auto nl([](auto) {std::cout << endl; });
			auto call_fgh(multicall(f, g, h, nl));
			for_each(call_fgh, 1, 2, 3, 4, 5);
#endif // unpacking_by_initializer
#ifdef transform_if
			std::istream_iterator<int> it{ std::cin };
			std::istream_iterator<int> end_it;
			auto even([](int i) {return i % 2 == 0; });
			auto twice([](int i) {	return i * 2; });
			auto copy_and_advance([](auto it, auto input) {
				*it = input;
				return ++it; });
			std::accumulate(it, end_it,
				std::ostream_iterator<int>{std::cout, ", "},
				filter(even)(
					map(twice)(
						copy_and_advance)
					));
			std::cout << endl;
#endif // transform_if
		}
		return 1;
	}