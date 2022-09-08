#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <random>
#include <sstream>
#include <list>
#include <functional>
#include <iomanip>
using namespace std;

//#define copy_n_move
//#define shuffle_mt19937
//#define remove_replace
//#define transform_vector
//#define find_equal_range
//#define minmax_clamp
//#define boyer_moore
//#define sample_
//#define permutation

#ifdef boyer_moore
template <typename Itr>
static void print(Itr it, size_t chars) {
	copy_n(it, chars, ostream_iterator<char>{cout});
	cout << endl;
}
#endif // boyer_moore

#ifdef find_equal_range
struct city {
	string name;
	unsigned population;
};

bool operator==(const city& a, const city& b) {
	return a.name == b.name && a.population == b.population;
}

ostream& operator<<(ostream& os, const city& city) {
	return os << "{" << city.name << ", " << city.population << "}";
}

template <typename C>
static auto opt_print(const C& container)
{
	return[end_it(end(container))](const auto& item) {
		if (item != end_it)
			cout << *item << endl;
		else
			cout << "<end>" << endl;
	};
}
#endif // find_equal_range

#ifdef copy_n_move

namespace std {
	ostream& operator<<(ostream& os, const pair<int, string>& p)
	{
		return os << "(" << p.first << ", " << p.second << ")";
	}
}
#endif // copy_n_move

#ifdef shuffle_mt19937
static void print(const vector<int>& v) {
	copy(begin(v), end(v), ostream_iterator<int>(cout, ", "));
	cout << endl;
}
#endif // shuffle_mt19937

#ifdef remove_replace
static void print(const vector<int>& v) {
	copy(begin(v), end(v), ostream_iterator<int>(cout, ", "));
	cout << endl;
}
#endif // remove_replace

#ifdef minmax_clamp	
static auto norm(int min, int max, int new_max) {
	const double diff(max - min);
	return [=](int val) {
		return int((val - min) / diff * new_max);
	};
}

static auto clampval(int min, int max) {
	return [=](int val) ->int {
		return clamp(val, min, max);
	};
}
#endif // mixmax_clamp

int main()
{

#ifdef permutation
	ifstream file("1.txt");
	vector<string> v{ istream_iterator<string> {file}, {} };
	sort(begin(v), end(v));
	do {
		copy(begin(v), end(v),
			ostream_iterator<string>{cout, ", "});
		cout << endl;
	} while (next_permutation(begin(v), end(v)));
#endif // permutation

#ifdef sample_
	const size_t data_points{ 100000 };
	const size_t sample_points{ 100 };
	const int mean{ 10 };
	const int dev{ 3 };
	random_device rd;
	mt19937 gen{ rd() };
	normal_distribution<> d{ mean,dev };
	vector<int> v;
	v.reserve(data_points);
	generate_n(back_inserter(v), data_points, [&] {return d(gen); });
	vector<int> samples;
	v.reserve(sample_points);
	sample(begin(v), end(v), back_inserter(samples), sample_points, mt19937{ random_device{}()});
	map<int, size_t> hist;
	for (int i : samples) {++hist[i];}
	for (const auto& [value, count] : hist) {
		cout << setw(2) << value << " " << string( count, 'x') << endl;
	}
#endif // sample_

#ifdef boyer_moore
	const string long_string{
		"Lorem ipsum dolor sit amet, consetetur"
		" sadipscing elitr, set diam nonumy eirmod" };
	const string needle{ "elitr" };
	{
		auto match(search(begin(long_string), end(long_string), begin(needle), end(needle)));
		print(match, 5);
	}
	{
		auto match(search(begin(long_string), end(long_string), default_searcher(begin(needle), end(needle))));
		print(match, 5);
	}
	{
		auto match(search(begin(long_string), end(long_string), boyer_moore_searcher(begin(needle), end(needle))));
		print(match, 5);
	}
	{
		auto match(search(begin(long_string), end(long_string), boyer_moore_horspool_searcher(begin(needle), end(needle))));
		print(match, 5);
	}
#endif // boyer_moore

#ifdef minmax_clamp
	vector<int> v{ 0,1000,5,250,300,800,900,321 };
	const auto [min_it, max_it](
		minmax_element(begin(v), end(v)));
	vector<int> v_norm;
	v_norm.reserve(v.size());
	transform(begin(v), end(v),
		back_inserter(v_norm),
		norm(*min_it, *max_it, 255));
	copy(begin(v_norm), end(v_norm),
		ostream_iterator<int>{cout, ", "});
	cout << endl;
	transform(begin(v), end(v), begin(v_norm), clampval(0, 255));
	copy(begin(v_norm), end(v_norm), ostream_iterator<int>{cout, ", "});
	cout << endl;
#endif // minmax_clamp

#ifdef find_equal_range
	const vector<city> c {
		{"Aachen", 246000},
		{ "Berlin", 3502000 },
		{ "Braunscweig", 251000 },
		{ "Cologne", 1060000 }};
	auto print_city(opt_print(c));
	{
		auto found_cologne(find(begin(c), end(c),
			city{ "Cologne",1060000 }));
		print_city(found_cologne);
	}
	{
		auto found_cologne(find_if(begin(c), end(c),
			[](const auto& item) {
				return item.name == "Cologne";
			}));
		print_city(found_cologne);
	}
	{
		auto population_more_than([](unsigned i) {
			return [=](const city& item) {
				return item.population > i;
			};
			});
		auto found_large(find_if(begin(c), end(c), population_more_than(2000000)));
		print_city(found_large);
	}
	const vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	auto print_int{ opt_print(v) };
	bool contains_7{ binary_search(begin(v),end(v),7) };
	cout << contains_7 << endl;
	auto [lower_it, upper_it] {
		equal_range(begin(v), end(v), 7)
	};
	print_int(lower_it);
	print_int(upper_it);
	print_int(lower_bound(begin(v), end(v), 7));
	print_int(upper_bound(begin(v), end(v), 7));
#endif // find_equal_range

#ifdef tranform_vector
	vector<int> v{ 1,2,3,4,5 };
	transform(begin(v), end(v), ostream_iterator<int>{cout, ", "}, [](int i) {
		return i * i; });
	cout << endl;
	auto int_to_string([](int i) {
		stringstream ss;
		ss << i << "^2 = " << i * i;
		return ss.str();
		});
	vector<string> vs;
	transform(begin(v), end(v), back_inserter(vs), int_to_string);
	copy(begin(vs), end(vs), ostream_iterator<string>{cout, "\n"});
#endif // tranform_vector

#ifdef remove_replace
	vector<int> v{ 1,2,3,4,5,6 };
	print(v);
	{
		const auto new_end(remove(begin(v), end(v), 2));
		v.erase(new_end, end(v));
	}
	print(v);
	{
		auto odd_number([](int i) { return i % 2 != 0; });
		const auto new_end(remove_if(begin(v), end(v), odd_number));
		v.erase(new_end, end(v));
	}
	print(v);
	replace(begin(v), end(v), 4, 123);
	print(v);
	v = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v2;
	vector<int> v3;
	auto oddnumber([](int i) { return i % 2 != 0; });
	auto evennumber([](int i) { return i % 2 == 0; });
	remove_copy_if(begin(v), end(v), back_inserter(v2), oddnumber);
	copy_if(begin(v), end(v), back_inserter(v3), evennumber);
	print(v2);
	print(v3);
#endif // remove_replace

#ifdef shuffle_mt19937
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	random_device rd;
	mt19937 g{ rd() };
	cout << g << endl;
	cout << is_sorted(begin(v), end(v)) << endl;
	shuffle(begin(v), end(v), g);
	cout << is_sorted(begin(v), end(v)) << endl;
	print(v);
	sort(begin(v), end(v));
	cout << is_sorted(begin(v), end(v)) << endl;
	print(v);
	shuffle(begin(v), end(v), g);
	partition(begin(v), end(v), [](int i) {
		return i < 5;
		});
	print(v);
	shuffle(begin(v), end(v), g);
	auto middle(next(begin(v), int(v.size() / 2)));
	partial_sort(begin(v), middle, end(v));
	print(v);
	struct myStruct {
		int _a;
		int _b;
	};
	vector<myStruct> mv{
		{5,100},
		{1,50},
		{-123,1000},
		{3,70},
		{-10,20} };
	sort(begin(mv), end(mv),
		[](const myStruct& lhs, const myStruct& rhs) {
			return lhs._b < rhs._b;
		});
	for (const auto&a: mv) {
		cout << "{" << a._a << ", " << a._b << "}";
	}
	cout << endl;
#endif // shuffle_mt19937

#ifdef copy_n
	vector<pair<int, string>> v{
		{1,"one"},
		{2,"two"},
		{3,"three"},
		{4,"four"},
		{5,"five"}
	};
	map<int, string> m;
	copy_n(begin(v), 3, inserter(m, begin(m)));
	auto shell_it(ostream_iterator<pair<int, string>>{cout, ", "});
	copy(begin(m), end(m), shell_it);
	cout << endl;
	m.clear();
	move(begin(v), end(v), inserter(m, begin(m)));
	copy(begin(m), end(m), shell_it);
	cout << endl;
	copy(begin(v), end(v), shell_it);
	cout << endl;
#endif // copy_n

	return 1;
}