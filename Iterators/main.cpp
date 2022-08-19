#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>
#include <iterator>
#include <list>
using namespace std;

//#define simple_iterator
//#define iterator_to_stl
//#define FIBONACCI
//#define iterator_adapters
//#define reverse_iterator
#define iterator_stopper

#ifdef iterator_to_stl
class num_iterator {
	int i;
public:
	explicit num_iterator(int position = 0) :i{ position } {}
	int operator*() const { return i; }
	num_iterator& operator++() {
		++i;
		return *this;
	}
	bool operator!=(const num_iterator& other) const {
		return i != other.i;
	}
	bool operator==(const num_iterator& other) const {
		return !(*this != other);
	}
};

namespace std {
	template<>
	struct iterator_traits<num_iterator> {
		using iterator_category = std::forward_iterator_tag;
		using value_type = int;
	};
}

class num_range {
	int a;
	int b;
public:
	num_range(int from, int to) : a(from), b(to) {}
	num_iterator begin() const { return num_iterator{ a }; }
	num_iterator end() const { return num_iterator{ b }; }
};
#endif // iterator_to_stl

#ifdef simple_iterator
class num_iterator {
	int i;
public:
	explicit num_iterator(int position = 0) : i{ position } {}
	int operator*() const { return i; }
	num_iterator operator++() {
		++i;
		return *this;
	}

	bool operator!=(const num_iterator& other) const {
		return i != other.i;
	}
};

class num_range {
	int a;
	int b;
public:
	num_range(int from, int to) : a{ from }, b{ to } {}
	num_iterator begin() const { return num_iterator{ a }; }
	num_iterator end() const { return num_iterator{ b }; }
};
#endif // simple_iterator

#ifdef FIBONACCI
class fib_it {
	size_t i{ 0 };
	size_t a{ 0 };
	size_t b{ 1 };
public:
	fib_it() = default;
	explicit fib_it(size_t i_) : i(i_) {}
	size_t operator*() const { return b; }
	fib_it& operator++() {
		const size_t old_b{ b };
		b += a;
		a = old_b;
		++i;
		return *this;
	}
	bool operator!=(const fib_it& o) const { return i != o.i; }
};

class fib_range {
	size_t end_n;
public:
	fib_range(size_t end_n_) : end_n(end_n_) {}
	fib_it begin() const { return fib_it{}; }
	fib_it end() const { return fib_it{ end_n }; }
};
#endif // FIBONACCI

#ifdef iterator_stopper
class cstring_iterator_sentinel {};
class cstring_iterator {
	const char* s{ nullptr };
public:
	explicit cstring_iterator(const char* str) :s(str) {}
	char operator*() const { return *s; };
	cstring_iterator& operator++() {
		++s;
		return *this;
	}
	bool operator!=(const cstring_iterator_sentinel) const {
		return s != nullptr && *s != '\0';
	}
};

class cstring_range {
	const char* s{ nullptr };
public:
	cstring_range(const char* str) : s{ str } {}
	cstring_iterator begin() const {
		return cstring_iterator{ s };
	}
	cstring_iterator_sentinel end() const {
		return {};
	}
};
#endif // iterator_stopper


int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "Please provide one parameter!" << endl;
		return 1;
	}
	for (char c : cstring_range(argv[1])) {
		cout << c;
	}

	ifstream file ("3.txt");
	if (!file.is_open()) return -1;
#ifdef simple_iterator
	for (int i : num_range{ 100,110 }) {
		std::cout << i << ", ";
	}
	cout << "\n";
#endif // simple_iterator
#ifdef iterator_to_stl
	num_range r{ 100,110 };
	auto [min_it, max_it] (minmax_element(begin(r), end(r)));
	cout << *min_it << " - " << *max_it << endl;
#endif // iterator_to_stl
#ifdef iterator_adapters
	istream_iterator<int> it_cin{ file };
	istream_iterator<int> end_cin;
	deque<int> v;
	copy(it_cin, end_cin, back_inserter(v));
	istringstream sstr{ "123 456 789" };
	auto deque_middle(next(begin(v), static_cast<int>(v.size()) / 2));
	copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));
	initializer_list<int> il2{ -1,-2,-3 };
	copy(begin(il2), end(il2), front_inserter(v));
	copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
	cout << endl;
#endif // iterator_adapters
#ifdef FIBONACCI
	for (size_t i : fib_range{ 10 }) {
		cout << i << ", ";
	}
	cout << endl;
	return 0;
#endif // FIBONACCI
#ifdef reverse_iterator
	list<int> l{ 1,2,3,4,5 };
	copy(rbegin(l), rend(l), ostream_iterator<int>(cout, ", "));
	cout << endl;
	copy(make_reverse_iterator(end(l)),
		make_reverse_iterator(begin(l)),
		ostream_iterator<int>(cout, ", "));
	cout << endl;
#endif // reverse_iterator

}