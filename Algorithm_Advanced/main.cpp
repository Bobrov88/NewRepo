#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <complex>
#include <numeric>
#include <valarray>
#include <cmath>
#include <corecrt_math_defines.h>
#include <list>

using namespace std;

//#define substr_search
//#define suggestions
//#define fourier
//#define sum_error
//#define mandelbrot
//#define split_
#define gather_

#ifdef gather_
template <typename It, typename F>
pair<It, It> gather(It first, It last, It gather_pos, F predicate) {
	return {	stable_partition(first,gather_pos,not_fn(predicate)),
				stable_partition(gather_pos,last,predicate) };
}

template <typename It, typename F>
void gather_sort(It first, It last, It gather_pos, F comp_func) {
	//auto inv_comp_func( [&] (const auto &...ps) {
	//	return !comp_func(ps...);});
	stable_sort(first, gather_pos, not_fn(comp_func));
	stable_sort(gather_pos, last, comp_func);
}
#endif // gather_



#ifdef split_
	template <typename InIt, typename OutIt, typename T, typename F>
	InIt split(InIt it, InIt end_it, OutIt out_it, T split_val, F bin_func) {
		while (it != end_it) {
			auto slice_end(find(it, end_it, split_val));
			*out_it++ = bin_func(it, slice_end);
			if (slice_end == end_it) return end_it;
			it = next(slice_end);
		}
		return it;
	}
#endif // split_

#ifdef mandelbrot
using cmplx = complex<double>;

static auto scaler(int min_from, int max_from,
	double min_to, double max_to) {
	const int w_from{ max_from - min_from };
	const double w_to{ max_to - min_to };
	const int mid_from{ w_from / 2 + min_from };
	const double mid_to{ w_to / 2 + min_to };
	return [=](int from) {
		return double(from - mid_from) / w_from * w_to + mid_to;
	};
}

template <typename A, typename B>
static auto scaled_cmplx(A scaler_x, B scaler_y) {
	return [=](int x, int y) {
		return cmplx{ scaler_x(x),scaler_y(y) };
	};
}

static auto mandelbrot_iterations(cmplx c) {
	cmplx z{};
	size_t iterations{ 0 };
	const size_t max_iterations{ 1000 };
	while (abs(z) < 2 && iterations < max_iterations) {
		++iterations;
		z = pow(z, 2) + c;
	}
	return iterations;
}
#endif // mandelbrot

#ifdef fourier
class num_iterator;

namespace std {
	template <>
	struct iterator_traits<num_iterator> {
		using iterator_category = std::forward_iterator_tag;
		using value = size_t;
	};
};

using cmplx = complex<double>;
using csignal = vector<cmplx>;

class num_iterator {
	size_t i;
public:
	explicit num_iterator(size_t position) : i{ position } {}
	size_t operator*() const { return i; }
	num_iterator& operator++() {
		++i;
		return *this;
	}
	bool operator!=(const num_iterator& other) const {
		return i != other.i;
	}
};

csignal fourier_transform(const csignal& s, bool back = false) {
	csignal t(s.size());
	const double pol{ 2.0 * M_PI * (back ? -1.0 : 1.0) };
	const double div{ back ? 1.0 : double(s.size()) };

	auto sum_up([=, &s](size_t j) {
		return [=, &s](cmplx c, size_t k) {
			return c + s[k] *
				polar(1.0, pol * k * j / double(s.size()));
		};
		});
	auto to_ft([=, &s](size_t j) {
		return accumulate(num_iterator{ 0 },
			num_iterator{ s.size() },
			cmplx{},
			sum_up(j)) / div;
		});
	transform(num_iterator{ 0 }, num_iterator{ s.size() },
		begin(t), to_ft);
	return t;
}
static auto gen_cousine(size_t period_len) {
	return[period_len, n{ 0 }]() mutable {
		return cos(double(n++) * 2.0 * M_PI / period_len);
	};
	}

static auto gen_square_wave(size_t period_len) {
	return[period_len, n{ period_len * 7 / 4 }]() mutable {
		return ((n++ * 2 / period_len) % 2) * 2 - 1.0;
	};
}

template <typename F>
static csignal signal_from_generator(size_t len, F gen) {
	csignal r(len);
	generate(begin(r), end(r), gen);
	return r;
}

static void print_signal(const csignal& s) {
	ofstream file("graph.txt", ofstream::out | ofstream::app);
	auto real_val([](cmplx c) {
		return c.real(); });
	transform(begin(s),end(s),
		ostream_iterator<double>{file, "\n"}, real_val);
	file << "\n";
	file << "\n";
	file.close();
	}
#endif // fourier

#ifdef suggestions
template <typename T>
class trie {
	map<T, trie> tries;
public:
	template <typename It>
	void insert(It it, It end_it) {
		if (it == end_it) { return; }
		tries[*it].insert(next(it), end_it);
	}
	template <typename C>
	void insert(const C& container) {
		insert(begin(container), end(container));
	}
	void insert(const initializer_list<T>& il) {
		insert(begin(il), end(il));
	}
	void print(vector<T>& v) const {
		if (tries.empty()) {
			copy(begin(v), end(v),
				ostream_iterator<T>{cout, " "});
			cout << endl;
		}
		for (const auto& p : tries) {
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
	optional<reference_wrapper<const trie>>
		subtrie(It it, It end_it) const {
		if (it == end_it) { return ref(*this); }
		auto found(tries.find(*it));
		if (found == end(tries)) { return {}; }
		return found->second.subtrie(next(it), end_it);
	}
	template <typename C>
	auto subtrie(const C& c) {
		return subtrie(begin(c), end(c));
	}
};

static void prompt() {
	cout << "Next input please:\n >";
}
#endif // suggestions

#ifdef substr_search
template <typename T>
class trie {
	map<T, trie> tries;
public:
	template <typename It>
	void insert(It it, It end_it) {
		if (it == end_it) { return; }
		tries[*it].insert(next(it), end_it);
	}
	template <typename C>
	void insert(const C& container) {
		insert(begin(container), end(container));
	}
	void insert(const initializer_list<T>& il) {
		insert(begin(il), end(il));
	}
	void print(vector<T>& v) const {
		if (tries.empty()) {
			copy(begin(v), end(v),
				ostream_iterator<T>{cout, " "});
			cout << endl;
		}
		for (const auto& p : tries) {
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
	optional<reference_wrapper<const trie>>
		subtrie(It it, It end_it) const {
		if (it == end_it) { return ref(*this); }
		auto found(tries.find(*it));
		if (found == end(tries)) { return {}; }
		return found->second.subtrie(next(it), end_it);
	}
	template <typename C>
	auto subtrie(const C& c) {
		return subtrie(begin(c), end(c));
	}
};
#endif // substr_search

int main() {
#ifdef gather_
	auto is_a([](char c) { return c == 'a'; });
	string a{ "a_a_a_a_a_a_a_a_a_a" };
	auto middle(begin(a) + a.size() / 2);
	gather(begin(a), end(a), middle, is_a);
	cout << a<<endl;
	gather(begin(a), end(a), begin(a), is_a);
	cout << a<<endl;
	gather(begin(a), end(a), end(a), is_a);
	cout << a << endl;
	gather(begin(a), end(a), middle, is_a);
	cout << a << endl;
	string b { "_9_2_4_7_3_8_1_6_5_0_" };
	gather_sort(begin(b), end(b), begin(b) + (int)b.size() / 2, std::less<char>{});
	cout << b << endl;
	rotate(begin(a), begin(a) + 1, end(a));
	cout << a << endl;
#endif // gather_


#ifdef split_
	const string s{ "a-b-c-d-e-f-g" };
	auto binfunc([](auto it_a, auto it_b) {
		return string(it_a, it_b); });
	list<string> l;
	split(begin(s), end(s), back_inserter(l), '-', binfunc);
	copy(begin(l), end(l), ostream_iterator<string>{cout, "\n"});
#endif // split_

#ifdef mandelbrot
	const size_t w{ 100 };
	const size_t h{ 40 };
	auto scale(scaled_cmplx(
		scaler(0, w, -2.0, 1.0),
		scaler(0, h, -1.0, 1.0)));
	auto i_to_xy([=](int i) {
		return scale(i % w, i / w);
		});
	auto to_iteration_count([=](int i) {
		return mandelbrot_iterations(i_to_xy(i)); });

	vector<int> v(w * h);
	iota(begin(v), end(v), 0);
	transform(begin(v), end(v),begin(v), to_iteration_count);

	auto binfunc([w, n{ 0 }] (auto output_it, int x) mutable {
		*++output_it = (x > 50 ? '*' : ' ');
		if (++n % w == 0) {
			++output_it = '\n';
		}
		return output_it;
	});
	
	auto bb (accumulate(begin(v), end(v), ostream_iterator<char>{cout}, binfunc));
#endif // DEBUG

#ifdef sum_error
	const size_t sig_len{ 100 };
	vector<double> as( sig_len );
	vector<int> ds( sig_len );
	auto sin_gen([n{ 0 }]() mutable {
		return 5.0 * sin(n++ * 2.0 * M_PI / 100); });
	generate(begin(as), end(as), sin_gen);
	copy(begin(as), end(as), begin(ds));
	copy(begin(as), end(as),
		ostream_iterator<double>{cout, " "});
	cout << endl;
	copy(begin(ds), end(ds),
		ostream_iterator<double>{cout, " "});
	cout << endl;
	cout << inner_product(begin(as), end(as), begin(ds), 0.0, std::plus<double>{},
		[](double a, double b) {
			return pow(a - b, 2); }) << endl;
#endif // sum_error

#ifdef fourier
	const size_t sig_len{ 100 };
	auto cosine(signal_from_generator(sig_len,
		gen_cousine(sig_len / 2)));
	auto square_wave(signal_from_generator(sig_len,
		gen_square_wave(sig_len / 2)));
	auto trans_sqw(fourier_transform(square_wave));
	fill(next(begin(trans_sqw), 10), prev(end(trans_sqw), 10), 0);
	auto mid(fourier_transform(trans_sqw, true));

	print_signal(cosine);
	print_signal(fourier_transform(cosine));
	print_signal(mid);;
	print_signal(trans_sqw);
	print_signal(square_wave);
	print_signal(fourier_transform(square_wave));
#endif // fourier

#ifdef suggestions
	trie<string> t;
	fstream infile{ "db.txt" };
	for (string line; getline(infile, line);) {
		istringstream iss{ line };
		t.insert(istream_iterator<string>{iss}, {});
	}
	prompt();
	for (string line; getline(cin, line);) {
		istringstream iss{ line };
		if (auto st(t.subtrie(istream_iterator<string> {iss}, {})); st) {
			cout << "Suggestions:\n";
			st->get().print();
		}
		else {
			cout << "No suggestions found. \n";
		}
		cout << "---------------------------\n";
		prompt();
	}
#endif // suggestions

#ifdef substr_search
	trie <string> t;
	t.insert({ "hi","how","are","you" });
	t.insert({ "hi","i", "am", "great", "thanks" });
	t.insert({ "what","are","you","doing" });
	t.insert({ "i", "am", "watching","a","movie" });
	cout << "recorded sentences:" << endl;
	t.print();
	cout << "possible suggestions after \"hi:\":\n";
	if (auto st(t.subtrie(initializer_list<string>{"hi"})); st) {
		st->get().print();
	}
#endif // substr_search

}
