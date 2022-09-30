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
#include <random>
using namespace std;

//#define _gather_
//#define split__
//#define trie_insert
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
//#define calling_some_functions
//#define copy_and_move_
//#define shuffle_sort_partition
//#define remove_copy_if_
//#define transform_
//#define binary_find
//#define transform_clamp
//#define boyer_moore
//#define sample_
//#define permutation_
//#define merge_dicts
#define delete_spaces
#ifdef delete_spaces
template <typename It>
It unique_space(It it, It it_end) {
	auto bin_pred([](const char& first, const char& last) {
		return first == ' ' && last == ' '; });
	return unique(it, it_end, bin_pred);
}
#endif // delete_spaces


namespace self_control {

#ifdef _gather_
	template <typename It, typename OutIt>
	void gather(It it, It end_it, It border, OutIt out) {
		auto is__([](auto a) {
			return a == '_'; });
		stable_partition(it, border, is__);
		stable_partition(border, end_it, not_fn(is__));
		copy(it, end_it, out);
		*out++ = '\n';
	}
#endif // _gather_

#ifdef split__
template <typename It, typename C>
void split(It it, It end_it, C ch) {
	auto split_it(it);
	while (it != end_it) {
		split_it = find(it, end_it, ch);
		if (split_it != end_it) {
			copy(it, split_it, ostream_iterator<char>{cout});
			cout << endl;
			it = next(split_it);
		}
		else {
			copy(it, end_it, ostream_iterator<char>{cout});
			it = end_it;
		}
	}
}
#endif // split__

#ifdef trie_insert
	template <typename T>
	class trie {
		map<T, trie> trie_;
	public:
		template <typename It>
		void insert(It it, It end_it) {
			if (it == end_it) return;
			trie_[*it].insert(next(it), end_it);
		};

		template <typename C>
		void insert(const C& container) {
			insert(begin(C), end(C));
}

		void insert(const initializer_list<T>&& il) {
			insert(begin(il), end(il));
		}

		void print(vector<T>& v) const {
			if (trie_.empty()) {
				copy(begin(v), end(v),
					ostream_iterator<string>{cout, " "});
				cout << endl;
			}
			for (const auto& p : trie_) {
				v.push_back(p.first);
				p.second.print(v);
				v.pop_back();
			}
		}
		void print() const {
			vector<T> v;
			print(v);
		}

		template <typename It>
		const trie subtrie(It it, It end_it) const {
			if (it == end_it) return *this;
			auto if_found(trie_.find(*it));
			if (if_found == end(trie_)) return {};
			return if_found->second.subtrie(next(it), end_it);
		}

		auto subtrie(const initializer_list<T>& il) const {
			return	subtrie(begin(il), end(il));
		}
};
#endif // trie

#ifdef merge_dicts
using dicts = std::pair<string, string>;
namespace std {
	istream& operator>>(istream& is, dicts& d) {
		is >> d.first >> d.second;
		return is;
	}
	ostream& operator<<(ostream& os, const dicts& d) {
		os << d.first << " " << d.second;
		return os;
	}
}
#endif // merge_dicts

#ifdef sample_
namespace std {
	ostream& operator<<(ostream& os, const pair<size_t, size_t>& container) {
		os << container.first << " " << string(container.second, '*') << endl;
		return os;
	}
}
#endif // sample_

#ifdef transform_clamp
static auto trans_clamp_func([](const auto &container, auto &container_norm) {
	return [=](double min, double max, double new_min, double new_max) {
		transform(begin(container), end(container), ostream_iterator<double>{cout,"\t"}, [=](auto i) {
			return (new_max - new_min) / (max - min) * i + new_min; });
	}; });

auto clamp__(double& min, double& max) {
	return [=](double &value) {
		return clamp(value, min, max); };};
#endif // transform_clamp

#ifdef copy_and_move_
namespace std {
	ostream& operator<<(ostream& os, const pair<int,string>& container) {
		os << container.first << " " << container.second << endl;
		return os;
	}
}
#endif // copy_and_move_

#ifdef WORDS_IN_FILE
	string _Trim(string & word) {
		const char* symbols{ ",.:;()-" };
		auto _begin(word.find_first_not_of(symbols));
		auto _end(word.find_last_not_of(symbols));
		return word.substr(_begin, _end - _begin + 1);
	}
#endif // WORDS_IN_FILE

#ifdef ERASE_REMOVE
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
}

int main() {
#ifdef delete_spaces
	string s{ "  aaa   a a   a  a a a a " };
	s.erase(unique_space(begin(s),end(s)), end(s));
	cout << s;
#endif // delete_spaces

	{
#ifdef _gather_
	string a{ "ff_fg___Gg_ggggg__df______Dsf_" };
	gather(begin(a),end(a), next(begin(a), size(a)/2),ostream_iterator<char>{cout});
	gather(begin(a), end(a), end(a), ostream_iterator<char>{cout});
	gather(begin(a), end(a), begin(a), ostream_iterator<char>{cout});
	gather(begin(a), end(a), next(begin(a)), ostream_iterator<char>{cout});
#endif // _gather_

#ifdef split__
	string to_split{ "a.d.v.g.d.g.t.e." };
	split(begin(to_split), end(to_split), '.');
#endif // split__

#ifdef trie_insert
	trie<string> t;
	ifstream file("db.txt");
	for (string line; getline(file, line);) {
		istringstream iss{ line };
		t.insert(istream_iterator<string>{iss}, {});
	}
	/*t.insert({"hi","hello","how", "are", "you"});
	t.insert({ "hi", "how", "do", "you", "do" });
	t.insert({ "what", "are", "you", "doing" });
	t.insert({ "what","do","you","think" });
	*/
	t.print();
	cout << endl;
	string line;
	getline(cin, line);
	stringstream iss{ line };
	auto found(t.subtrie(istream_iterator<string>{iss}, {}));
	found.print();

#endif // trie_insert

#ifdef merge_dicts
	ifstream i1{ "d1.txt" };
	ifstream i2{ "d2.txt" };
	deque<dicts> d1{ istream_iterator<dicts>{ i1 }, {} };
	deque<dicts> d2;
	copy(istream_iterator<dicts>{i2}, {}, back_inserter(d2));
	sort(begin(d1), end(d1));
	sort(begin(d2), end(d2));
	merge(begin(d1), end(d1), begin(d2), end(d2),
		ostream_iterator<dicts>{cout, "\n"});
#endif // merge_dicts

#ifdef permutation_	
	vector<int> I{ 1,2,3,4,5 };
	do {
		copy(begin(I), end(I), ostream_iterator<int>{cout});
		cout << endl;
	} while (next_permutation(begin(I),end(I)));
#endif

#ifdef sample_
	const size_t big_vector_size{ 100000 };
	const size_t small_vector_size{ 100 };
	vector<size_t> bigV;
	random_device rd;
	mt19937 mt{ rd() };
	normal_distribution<> nd{ 10,3 };
	bigV.reserve(big_vector_size);
	vector<size_t> V;
	V.reserve(small_vector_size);
	generate_n(back_inserter(bigV), big_vector_size, [&]() {return nd(mt); });
	sample(begin(bigV), end(bigV), back_inserter(V),
		small_vector_size, mt19937{ random_device{}() });
	map<size_t, size_t> M;
	for (auto& i : V) ++M[i];
	copy(begin(M), end(M),
		ostream_iterator<pair<size_t,size_t>>{cout});
	{
#endif // sample_

#ifdef boyer_moore
		const string where_to_search{ "Lorem ipsum voyceg"
			" trepandovskiy aaa bbb ccc fufundrovich" };
		const string what_must_be_searched{ "ccc" };
		copy_n(search(begin(where_to_search), end(where_to_search),
			begin(what_must_be_searched), end(what_must_be_searched)),
			what_must_be_searched.size(),
			ostream_iterator<char>{cout});
		cout << endl;
		copy_n(search(begin(where_to_search), end(where_to_search),
			default_searcher(begin(what_must_be_searched), end(what_must_be_searched))),
			what_must_be_searched.size(),
			ostream_iterator<char>{cout});
		cout << endl;
		copy_n(search(begin(where_to_search), end(where_to_search),
			boyer_moore_searcher(begin(what_must_be_searched), end(what_must_be_searched))),
			what_must_be_searched.size(),
			ostream_iterator<char>{cout});
		cout << endl;
		copy_n(search(begin(where_to_search), end(where_to_search),
			boyer_moore_horspool_searcher(begin(what_must_be_searched), end(what_must_be_searched))),
			what_must_be_searched.size(),
			ostream_iterator<char>{cout});
#endif // boyer_moore

#ifdef transform_clamp
		vector<double> _dv{ 0.5,0.6,2.4,4.6,6.7,5.4 };
		vector<double> _dv_norm;
		_dv_norm.reserve(_dv.size());
		auto before_clamp(trans_clamp_func(_dv, _dv_norm));
		before_clamp(0.0, 8.0, 4.0, 20.0);
		cout << endl;
		copy(begin(_dv), end(_dv), ostream_iterator<double>{cout, "\t"});
		double min{ 1 };
		double max{ 5 };
		transform(begin(_dv), end(_dv), back_inserter(_dv_norm), clamp__(min, max));
		cout << endl;
		copy(begin(_dv_norm), end(_dv_norm), ostream_iterator<double>{cout, "\t"});
#endif // transform_clamp

#ifdef binary_find
		//random_device _rd;
		//mt19937 _mt{ _rd() };
		//vector<int> V;
		//for (size_t i{ 0 }; i < 20 ;(void)++i) V.push_back(_mt());
		//vector<int> VV(V);
		//sort(begin(V), end(V));
		//cout<<std::boolalpha<<binary_search(begin(V), end(V), *begin(V));
		//cout<<*find_first_of(begin(V), next(begin(V),V.size()/2), next(begin(V), V.size() / 2), end(V));
		vector<int> VVV{ 1,2,3,3,3,3,4,5 };
		auto Pair(equal_range(begin(VVV), end(VVV), 3));
		cout << *Pair.first << " " << *Pair.second << endl;
		cout << *upper_bound(begin(VVV), end(VVV), 3);
#endif // binary_find

#ifdef transform_
		vector<int> V(10);
		vector<string> VV;
		iota(begin(V), end(V), 1);
		//copy(begin(V), end(V), ostream_iterator<int>{cout, "-"});
		transform(begin(V), end(V), back_insert_iterator(VV), [](int a) {
			stringstream ss;
			ss << a << "^2=" << a * a;
			return ss.str(); });
		copy(begin(VV), end(VV), ostream_iterator<string>{cout, "\n"});
#endif // transform_

#ifdef remove_copy_if_
		random_device _rd;
		mt19937 _mt{ _rd() };
		vector<int> V;
		for (size_t i{ 0 }; i < 20; ++i)
			V.push_back(_mt() % 3);
		copy(begin(V), end(V), ostream_iterator<int>{cout, "-"});
		replace(begin(V), end(V), 2, 666);
		cout << endl;
		copy(begin(V), end(V), ostream_iterator<int>{cout, "-"});
		vector<int> V1, V2;
		remove_copy_if(begin(V), end(V), back_insert_iterator(V1), [](int a) {
			return a != 666; });
		remove_copy_if(begin(V), end(V), back_insert_iterator(V2), [](int a) {
			return a == 666; });
		cout << endl;
		copy(begin(V1), end(V1), ostream_iterator<int>{cout, "-"});
		cout << endl;
		copy(begin(V2), end(V2), ostream_iterator<int>{cout, "-"});
		cout << endl;
		copy(begin(V), end(V), ostream_iterator<int>{cout, "-"});
		//	auto it = remove(begin(V), end(V), 2);
		//	V.erase(it, V.end());
		//	cout << endl;
		//	copy(begin(V), end(V), ostream_iterator<int>{cout, "-"});
#endif // remove_copy_if

#ifdef shuffle_sort_partition
		random_device _rd;
		mt19937 _mt{ _rd() };
		vector<size_t> V;
		for (size_t i{ 0 }; i < 10000; ++i)
			V.push_back(i);
		cout << std::boolalpha;
		cout << endl;
		cout << std::is_sorted(begin(V), end(V)) << endl;
		shuffle(begin(V), end(V), _mt);
		cout << std::is_sorted(begin(V), end(V)) << endl;
		copy(begin(V), next(begin(V), 30), ostream_iterator<size_t>{cout, "\n"});
		sort(begin(V), end(V));
		copy(begin(V), next(begin(V), 30), ostream_iterator<size_t>{cout, "\n"});
		cout << endl;
		shuffle(begin(V), end(V), _mt);
		partial_sort(begin(V), next(begin(V), 15), end(V));
		copy(begin(V), next(begin(V), 30), ostream_iterator<size_t>{cout, "\n"});
		partition(begin(V), next(begin(V), 10), [](int a) {
			return a % 2 == 0; });
		copy(begin(V), next(begin(V), 30), ostream_iterator<size_t>{cout, "\n"});
#endif // shuffle_sort_partition

#ifdef copy_and_move_
		vector<pair<int, string>> V{
			{1,"one"},
			{2,"two"},
			{3,"three"} };
		vector<pair<int, string>> VV;
		VV.reserve(5);
		copy_n(begin(V), V.size(), back_insert_iterator(VV));
		copy(begin(V), end(V), ostream_iterator<pair<int, string>>{cout, " "});
		cout << endl;
		move(begin(V), end(V), back_insert_iterator(VV));
		map<int, string> M;
		copy(begin(VV), end(VV), inserter(M, begin(M)));
		cout << endl;
		copy(begin(VV), end(VV), ostream_iterator<pair<int, string>>{cout, " "});
		cout << endl;
		copy(begin(V), end(V), ostream_iterator<pair<int, string>>{cout, " "});
		cout << endl;
		copy(begin(M), end(M), ostream_iterator<pair<int, string>>{cout, " "});
		cout << endl;
#endif // copy_and_move_

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
		for (const auto& el : _blist) {
			auto [_it, _is_inserted] = _m.try_emplace(el.month, el, 1);
			if (_is_inserted == false) {
				++_it->second.second;
			}
		}
		for (const auto& el : _m) {
			cout << "In " << el.first << " the youngest man is "
				<< el.second.first.name << " and there are "
				<< el.second.second << " people at all" << endl;
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
		istream_iterator<string> ss{ file };
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
			string word{ *it1 };
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
		string sentence{ iss, end };
		auto it_begin = sentence.begin();
		auto it_dot = find(it_begin, sentence.end(), '.');
		while (it_dot != sentence.end()) {
			string one_sentence({ it_begin, it_dot });
			map<string, size_t> sentences_encounting = get_sentence_statistics(one_sentence);
			cout << one_sentence << " - " << sentences_encounting[one_sentence] << endl;
			it_begin = next(it_dot, 1);
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
		for (const auto& el : _il) _pq.push(el);
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

#ifdef calling_some_functions
		auto brace1([](auto& letter) { cout << "[" << letter << "]"; });
		auto brace2([](auto& letter) { cout << "(" << letter << ")"; });
		auto brace3([](auto& letter) { cout << "{" << letter << "}"; });
		auto nl([](auto) {cout << endl; });
		auto call(multicall(brace1, brace2, brace3, nl));
		for_each(call, 1, 2, 3, 4, 5);
#endif // calling_some_functions
	}

}