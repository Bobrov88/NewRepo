#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <list>
#include <string>
#include <map>
#include <set>
#include <stdexcept>
#include <stack>
#include <queue>
#include <numeric>
#include <functional>
using namespace std;

//#define ERASE_REMOVE
//#define DELETING_O1
//#define QUICK_SAFE_ACCESS
//#define SAFE_IMSERT_INTO_MAP
//#define HINTS
//#define CHANGE_KEYS
//#define SELFMADE_TYPE
//#define INSERT_UNIQUE
//#define OPN
//#define WORDS_IN_FILE 
//#define TEXT_STYLE
//#define PRIORITY_QUEUE
//#define MY_RANGE
//#define COMPATIBLE_ITERATOR
//#define ADAPTORS_OF_ITERATORS
//#define FIBONACCI_ITERATOR
//#define REVERSE_ITERATOR
//#define SENTINEL
//#define ZIP_ITERATOR
//#define lambda_dynamic_definition
//#define wrapped_lambda
//#define concat_by_lambda
//#define logical_concat
#define calling_some_functions

namespace self_control {
#ifdef WORDS_IN_FILE
	string _Trim(string & word) {
		const char* symbols{ ",.:;()-" };
		auto _begin(word.find_first_not_of(symbols));
		auto _end(word.find_last_not_of(symbols));
		return word.substr(_begin, _end - _begin + 1);
	}
#endif // WORDS_IN_FILE

#ifdef  ERASE_REMOVE
	struct coord {
		double x;
		double y;
	};
#endif //  ERASE_REMOVE

#ifdef SAFE_IMSERT_INTO_MAP
	struct birthday {
		string name;
		string month;
		size_t age;
	};
#endif // SAFE_IMSERT_INTO_MAP

#ifdef SELFMADE_TYPE
	struct attribute {
		float temperature;
		float pressure;
		float volume;
	};

	bool operator==(const attribute & l, const attribute & r) {
		return	l.pressure == r.pressure &&
			l.temperature == r.temperature &&
			l.volume == r.volume;
	}
	bool operator<(const attribute & l, const attribute & r) {
		return	l.pressure < r.pressure;
	}

	namespace std {
		template<>
		struct hash<attribute> {
			using argument_type = attribute;
			using result_type = float;
			result_type operator()(const argument_type& obj) const {
				return	static_cast<result_type>(obj.pressure) +
					static_cast<result_type>(obj.temperature) +
					static_cast<result_type>(obj.volume);
			}
		};
	}

#endif // SELFMADE_TYPE

#ifdef TEXT_STYLE

	string _trim_sentence(string & sentence) {
		const char* symbols{ " \r\n\t" };
		auto _begin(sentence.find_first_not_of(symbols));
		auto _end(sentence.find_last_not_of(symbols));
		return sentence.substr(_begin, _end - _begin + 1);
	}

	map<string, size_t> get_sentence_statistics(string & sentence) {
		map<string, size_t> m;
		sentence = _trim_sentence(sentence);
		m[sentence] = count(sentence.begin(), sentence.end(), ' ') + 1;
		return m;
	}
#endif // TEXT_STYLE

#ifdef MY_RANGE
class range_iterator {
	size_t __position;
public:
	range_iterator(size_t __p) : __position{ __p } {}
	range_iterator& operator++() {
		++__position;
		return *this;
	}
	size_t operator*() const {
		return __position;
	}
	bool operator!=(const range_iterator& other) const {
		return this->__position != other.__position;
	}
};

class _myrange {
	size_t __begin;
	size_t __end;
public:
	explicit _myrange(size_t __b, size_t __e): __begin { __b },__end{__e} {}
	range_iterator begin() const { return range_iterator{ __begin }; }
	range_iterator end() const { return range_iterator{ __end }; }
};
#endif // MY_RANGE

#ifdef COMPATIBLE_ITERATOR
class range_iterator {
	size_t __position;
public:
	range_iterator(size_t __p) : __position{ __p } {}
	range_iterator& operator++() {
		++__position;
		return *this;
	}
	size_t operator*() const {
		return __position;
	}
	bool operator!=(const range_iterator& other) const {
		return this->__position != other.__position;
	}
	bool operator==(const range_iterator& other) const {
		return !(*this != other);
	}
};

namespace std {
	template<>
	struct iterator_traits<range_iterator> {
		using iterator_category = std::output_iterator_tag;
		using value_type = size_t;
		using reference = range_iterator&;
	};
}

class _myrange {
	size_t __begin;
	size_t __end;
public:
	explicit _myrange(size_t __b, size_t __e) : __begin{ __b }, __end{ __e } {}
	range_iterator begin() const { return range_iterator{ __begin }; }
	range_iterator end() const { return range_iterator{ __end }; }
};
#endif // COMPATIBLE_ITERATOR

#ifdef FIBONACCI_ITERATOR
class Fib_it {
	size_t a{ 0 };
	size_t b{ 1 };
	size_t i{ 0 };
public:
	Fib_it(size_t _i) : i{ _i } {}
	Fib_it& operator++() {
		size_t old_b{ b };
		b += a;
		a = old_b;
		++i;
		return *this;
	}
	bool operator!=(Fib_it& other) {
		return this->i != other.i;
	}
	size_t operator*() const {
		return this->b;
	}
};

class Fib_range {
	size_t _to;
public:
	Fib_range(size_t to) : _to(to) {}
	Fib_it begin() const { return Fib_it{ 0 }; }
	Fib_it end() const { return Fib_it{ _to }; }
};
#endif // FIBONACCI_ITERATOR

#ifdef SENTINEL
class sentinel {};
class cstring_iterator {
	const char* ch;
public:
	explicit cstring_iterator(const char* _ch) : ch(_ch) {}
	char operator*() const {
		return *ch;
	}
	bool operator!=(const sentinel) const {
		return ch != nullptr && *ch != '\0';
	}
	cstring_iterator& operator++() {
		++ch;
		return *this;
	}
};
class cstring {
	const char* c;
public:
	cstring(const char* _c) : c(_c) {}
	cstring_iterator begin() const { return cstring_iterator{ c }; }
	sentinel end() const { return {}; }
};
#endif // SENTINEL

#ifdef ZIP_ITERATOR

class zip_iterator;

namespace std {
	template <>
	struct iterator_traits<zip_iterator> {
		using iterator_category = forward_iterator_tag;
		using value_type = int;
		using reference = zip_iterator&;
	};
}

class zip_iterator {
	using it = vector<int>::iterator;
	it pa;
	it pb;
public:
	zip_iterator(it _pa, it _pb) : pa{ _pa }, pb{ _pb }{}
	zip_iterator& operator++() {
		++pa;
		++pb;
		return *this;
	}
	bool operator!=(const zip_iterator& other) const {
		return pa != other.pa && pb != other.pb;
	}
	pair<int, int> operator*() const {
		return { *pa, *pb };
	}
};

class zip {
	vector<int>& a;
	vector<int>& b;
public:
	zip(vector<int>& _a, vector<int>& _b) :
		a{ _a }, b{ _b } {};
	zip_iterator begin() const { return { a.begin(), b.begin() }; }
	zip_iterator end() const { return { a.end(), b.end() }; }
};
#endif // ZIP_ITERATOR

#ifdef wrapped_lambda
auto consumer([=](auto& container) {
	return [&](int i) {
		container.push_back(i);
	}; });

auto print(const auto& container) {
	for (auto& i : container)
		cout << i << " ";
	cout << endl;
};
#endif // wrapped_lambda

#ifdef concat_by_lambda
template <typename T, typename...Ts>
static auto concat(T t, Ts...ts) {
	if constexpr (sizeof...(ts) > 0) {
		return [=](auto ...parameter) {
			return t(concat(ts...)(parameter...));
		};
	}
	else return t;
}
#endif // concat_by_lambda

#ifdef logical_concat
static bool begin_with_a(const string& word) {
	return word.find('a') == 0;
}
static bool end_with_b(const string& word) {
	return word.rfind('b') == word.length() - 1;
}
template <typename T, typename F1, typename F2>
auto combine(T log_f, F1 f1, F2 f2) {
	return [=](auto& parameters) {
		return log_f(f1(parameters), f2(parameters));
	};
}
#endif // logical_concat
}

#ifdef calling_some_functions
static auto multicall(auto ...functions) {
	return [=](auto x) {
		(void)std::initializer_list<int> {
			((void)functions(x), 0)...
		};
	};
}
static auto for_each(auto F, auto ...xs) {
	(void)initializer_list<int> {
		((void)F(xs), 0)...
	};
}

#endif // calling_some_functions


int main() {
#ifdef calling_some_functions
	auto brace1([](auto& letter) { cout << "[" << letter << "]"; });
	auto brace2([](auto& letter) { cout << "(" << letter << ")"; });
	auto brace3([](auto& letter) { cout << "{" << letter << "}"; });
	auto nl([](auto) {cout << endl; });
	auto call(multicall(brace1, brace2, brace3, nl));
	for_each(call, 1, 2, 3, 4, 5);
#endif // calling_some_functions

	{
#ifdef COMPATIBLE_ITERATOR
	_myrange Range{ 20,30 };
	auto it(find(begin(Range), end(Range), 21));
	cout << *it;
#endif // COMPATIBLE_ITERATOR

#ifdef MY_RANGE
	_myrange _Range{ 50,60 };
	for (auto el : _Range) {
		cout << el << endl;
	}
	return 0;
#endif // MY_RANGE

#ifdef ERASE_REMOVE
	vector<coord> V{ {1.0,3.2},
		{2.6,3.9},
		{5.2,4.4},
		{0.8,-5.6} };
	assert(V.size() == 4);
	V.erase(remove_if(begin(V), end(V), [](coord& el) { return el.x > 2.0; }), V.end());
	assert(V.size() == 2);
#endif // ERASE_REMOVE

#ifdef DELETING_O1
	vector<int> IV{ 1,2,3,4,5,6,7,8 };
	auto __idx(begin(IV) + 2);
	*__idx = move(IV.back());
	IV.pop_back();
	assert(*__idx == 8);
	assert(IV.size() == 7);
#endif // DELETING_O1

#ifdef QUICK_SAFE_ACCESS
	vector<char> CV{ '1','2', '3', '4','5' };
	assert(CV.at(1) == '2');
	assert(*CV.begin() == '1');
	assert(*(CV.end() - 1) == '5');
	try
	{
		cout << CV[CV.size()];
	}
	catch (const out_of_range& ex) {
		cout << ex.what();
	}
#endif // QUICK_SAFE_ACCESS

#ifdef SAVE_SORTED
	vector<double> _dv{ 1.3,4.2,5.7,-4.6,5.3,1.2,3.3 };
	for (auto& el : _dv) {
		cout << el << "  ";
	}
	cout << endl;
	sort(begin(_dv), end(_dv));
	double inserted_value = 4.3;
	for (auto& el : _dv) {
		cout << el << "  ";
	}
	cout << endl;
	_dv.insert(lower_bound(begin(_dv), end(_dv), inserted_value), inserted_value);
	for (auto& el : _dv) {
		cout << el << "  ";
	}
	cout << endl;
#endif // SAVE_SORTED

#ifdef SAFE_IMSERT_INTO_MAP
	list<birthday> _blist{
		{"Dmitriy", "august", 34},
		{"Victor", "march", 34},
		{"Alina", "march", 27},
		{"Murad", "december", 33},
		{"Leonid", "june", 32},
		{"Timur", "april", 34},
		{"Amaliya", "february", 7},
		{"Albina", "november", 26},
		{"Dobriy", "february", 34},
		{"Veta", "june", 39},
		{"Vlad", "february", 4}
	};
	_blist.sort([](birthday& first, birthday& second) {
		return first.age < second.age;
		});
	map <string, pair <const birthday, size_t>> _m;
	for (const auto&el : _blist) {
		auto [_it, _is_inserted] = _m.try_emplace(el.month, el, 1);
		if (_is_inserted == false) {
			++_it->second.second;
		}
	}
	for (const auto& el : _m) {
		cout << "In " << el.first		<< " the youngest man is " 
			 << el.second.first.name	<< " and there are "
			 << el.second.second		<< " people at all" << endl;
	}
#endif // SAFE_IMSERT_INTO_MAP

#ifdef HINTS
	list<int> _li{ 3,6,2,7,9,3,6,-1,3,7,53,43,5,456,2,54,54,5 };
	map<int, int> _mi;
	auto iterator{ _mi.end() };
	int i{ 0 };
	for (const auto& el : _li) {
		iterator = _mi.insert(iterator, { i++,el });
	}
	for (const auto& el : _mi) {
		cout << "< " << el.first << " : " << el.second << " >" << endl;
	}
#endif // HINTS

#ifdef CHANGE_KEYS
	map<size_t, string> _ms{
		{1,"Moscow"},
		{2,"Kaluga"},
		{3,"Ryazan'"},
		{4,"Tula"},
		{5,"Kozelsk"},
		{6,"Tashkent"},
		{6,"Shimkent"}
	};
	try {
		auto l = _ms.extract(1);
		auto r = _ms.extract(6);
		swap(r.key(), l.key());
		_ms.insert(move(r));
		_ms.insert(move(l));
	}
	catch (const out_of_range& ex) {
		cout << "Out of range!" << ex.what() << endl;
	}
	for (const auto& el : _ms) {
		cout << el.first << " - " << el.second << endl;
	}


#endif // CHANGE_KEYS

#ifdef SELFMADE_TYPE
	map<attribute, size_t> water{
		{{4.5,67.3,20}, 1},
		{{8.2,96.4, 100.4}, 2},
		{{2.5,51.4,3.4}, 3}
	};
	for (const auto& el : water) {
		cout << el.first.pressure <<
			" - " << el.first.temperature <<
			" - " << el.first.volume << endl;
	}
	return 0;
#endif // SELFMADE_TYPE

#ifdef INSERT_UNIQUE
	fstream file("1.txt");
	set<string> listing;
	if (!file.is_open()) return 0;
	istream_iterator<string> ss { file };
	istream_iterator<string> end;
	copy(ss, end, inserter(listing, listing.end()));
	for (const auto& el : listing) {
		cout << el << " ";
	}
	file.close();
	return 0;
#endif // INSERT_UNIQUE

#ifdef OPN
	map<string, double (*)(const double, const double)> operations{
		{"+", [](const double l, const double r) {return l + r; }},
		{"-", [](const double l, const double r) {return l - r; }},
		{"*", [](const double l, const double r) {return l * r; }},
		{"/", [](const double l, const double r) {return l / r; }},
		{"^", [](const double l, const double r) {return pow(l,r); }},
		{"%", [](const double l, const double r) {return fmod(l,r); }}
	};

	ifstream file("2.txt");
	if (!file.is_open()) return 0;
	stack<double> vars;
	istream_iterator<string> IT{ file };
	istream_iterator<string> end{ };
	for (; IT != end; IT++) {
		stringstream ss{ *IT };
		if (double var; ss >> var) {
			vars.push(var);
		}
		else {
			const auto r{ vars.top() };
			vars.pop();
			const auto l{ vars.top() };
			vars.pop();
			vars.push(operations.at(*IT)(l, r));
		}
	}
	cout << "Result: " << vars.top();
	return 0;
#endif // OPN

#ifdef WORDS_IN_FILE
ifstream file("1.txt");
if (!file.is_open()) return -2;
map <string, size_t> words;
istream_iterator<string> it1{ file };
istream_iterator<string> end;
for (; it1 != end; ++it1) {
	string word{*it1};
	++words[_Trim(word)];
}

vector<pair<string, size_t>> v;
v.reserve(words.size());
move(begin(words), std::end(words), back_inserter(v));
sort(begin(v), std::end(v), [](auto& a, auto& b) {
	return a.second > b.second;
	});
for (auto& el : v) {
	cout << el.first << " - " << el.second << endl;
}
file.close();
return 0;
#endif // WORDS_IN_FILE

#ifdef TEXT_STYLE
ifstream file("1.txt");
if (!file.is_open()) return -2;
file.unsetf(ios::skipws);
istream_iterator<char> iss{ file };
istream_iterator<char> end;
string sentence {iss, end};
auto it_begin = sentence.begin();
auto it_dot = find(it_begin, sentence.end(), '.');
while (it_dot != sentence.end()) {
	string one_sentence({ it_begin, it_dot });
	map<string, size_t> sentences_encounting = get_sentence_statistics(one_sentence);
	cout << one_sentence << " - " << sentences_encounting[one_sentence] << endl;
	it_begin = next(it_dot,1);
	it_dot = find(it_begin, sentence.end(), '.');
}

file.close();
#endif // TEXT_STYLE

#ifdef PRIORITY_QUEUE
initializer_list<pair<size_t, string>> _il{
	{0,"Serik"},
	{0, "Leonid"},
	{2, "Latypov"},
	{1, "Dobriy"},
	{3, "Labazan"}
};
priority_queue<pair<size_t, string>> _pq;
for (const auto &el : _il) _pq.push(el);
while (!_pq.empty()) {
	cout << _pq.top().first << " - " << _pq.top().second << endl;
	_pq.pop();
}
#endif // PRIORITY_QUEUE

#ifdef ADAPTORS_OF_ITERATORS
ifstream file("3.txt");
istream_iterator<size_t> begin{ file };
istream_iterator<size_t> end;
deque<size_t> d;
std::copy(begin, end, back_inserter(d));
list<size_t> l{ 2, 64, 888 };
std::copy(std::begin(l), std::end(l), front_inserter(d));
initializer_list<int> I{ 1,3,56 };
auto middle(next(std::begin(d), static_cast<size_t>(d.size() / 2)));
std::copy(std::begin(I), std::end(I), inserter(d, middle));
std::copy(std::begin(d), std::end(d), ostream_iterator<size_t>(cout, " "));
#endif // ADAPTORS_OF_ITERATORS

#ifdef FIBONACCI_ITERATOR
for (const auto&& el : Fib_range{ 10 }) {
	cout << el << endl;
}
#endif // FIBONACCI_ITERATOR

#ifdef REVERSE_ITERATOR
list<size_t> _l{ 1,2,3,4,5 };
std::copy(make_reverse_iterator(end(_l)),
	make_reverse_iterator(begin(_l)),
		ostream_iterator<size_t>(std::cout, "-"));
std::copy(rbegin(_l), rend(_l),
	ostream_iterator<size_t>(std::cout, "-"));
#endif // REVERSE_ITERATOR

#ifdef SENTINEL
cstring s("Sentinel");
for (char c : s) {
	cout << c;
}
cout << endl;
#endif // SENTINEL

#ifdef ITERATOR_DEBUG_LEVEL
vector<int> v{ 1,2,3,4,5 };
cout << v.capacity() << endl;
auto _begin{ v.begin() };
cout << *_begin << endl;
v.push_back(123);
v.shrink_to_fit();
cout << v.capacity() << endl;
cout << *_begin;
#endif // ITERATOR_DEBUG_LEVEL

#ifdef ZIP_ITERATOR
vector<int> a{ 1,2,3 };
vector<int> b{ 4,5,6 };
zip __zip(a, b);
auto _sum([](int sum, pair<int, int> p) {
	return sum + p.first * p.second;
	});
const auto add_pr(accumulate(begin(__zip), end(__zip), 0, _sum));
cout << add_pr;
#endif // ZIP_ITERATOR

#ifdef lambda_dynamic_definition
auto _sum([](int x, int y) {return x + y; });
cout << _sum(1, 4) << endl;
auto _product_added([](const function<int(int, int)>& f) { return f(3, 4) * 4; });
cout << _product_added(_sum) << endl;
auto _product_advanced(
	[=](int x, int y, int z) {
		return _sum(x, y) * z;
	});
auto no_brackets([] {return "no brackets"; });
auto param_at_once([](int x, int y) constexpr { return x * y; }(3, 2));
cout << _product_advanced(3, 5, 7) << endl;
cout << no_brackets() << endl;
cout << param_at_once << endl;
auto counter([count = 0]() mutable {return ++count; });
cout << counter() << endl;
cout << counter() << endl;
cout << counter() << endl;
#endif // lambda_dynamic_definition

#ifdef wrapped_lambda
list<int> l;
vector<int> v;
deque<int> d;
initializer_list<function<void(int)>> consumers{
	consumer(l), consumer(v),consumer(d) };
for (int i{ 0 }; i < 5; ++i) {
	for (auto&& el : consumers) {
		el(i);
	}
}
print(v);
print(l);
print(d);
#endif // wrapped_lambda

#ifdef concat_by_lambda
auto twice([](int i) { return i * 2; });
auto thrice([](int i) {return i * 3; });
auto combined(concat(twice, thrice, std::plus<int>{}));
std::cout << combined(2, 3) << endl;
#endif // concat_by_lambda

#ifdef logical_concat
istream_iterator<string> it{ cin };
istream_iterator<string> end;
auto revise_word(combine(std::logical_and<>{}, begin_with_a, end_with_b));
copy_if(it, end, ostream_iterator<string>{cout, ", "}, revise_word);
#endif // logical_concat
}
}