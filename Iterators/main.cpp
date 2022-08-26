#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>
#include <iterator>
#include <list>
#include <vector>
#include <numeric>	
#include <valarray>
#define _ITERATOR_DEBUG_LEVEL 2
using namespace std;

//#define simple_iterator
//#define iterator_to_stl
//#define FIBONACCI
//#define iterator_adapters
//#define reverse_iterator
//#define iterator_stopper
//#define code_revise
#define ZIP_iterator

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

#ifdef ZIP_iterator
class zip_iterator {
	using it_type = std::vector<double>::iterator;
	it_type it1;
	it_type it2;
public:
	zip_iterator(it_type iterator1, it_type iterator2)
		: it1{ iterator1 }, it2{ iterator2 } {};
	zip_iterator& operator++() {
		++it1;
		++it2;
		return *this;
	}
	bool operator!=(const zip_iterator& other) const {
		return it1 != other.it1 && it2 != other.it2;
	}
	bool operator==(const zip_iterator& other) const {
		return !operator!=(other);
	}
	pair<double, double> operator*() {
		return { *it1,*it2 };
	}
	};

namespace std {
	template<>
	struct iterator_traits<zip_iterator> {
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::pair<double, double>;
		using reference = zip_iterator&;
		using difference_type = long int;
	};
}

class zipper {
	using vec_type = std::vector<double>;
	vec_type& vec1;
	vec_type& vec2;
public:
	zipper(vec_type &va, vec_type &vb) 
		: vec1{ va }, vec2{ vb } {}
	zip_iterator begin() const {
		return { std::begin(vec1), std::begin(vec2) };
	}
	zip_iterator end() const {
		return { std::end(vec1), std::end(vec2) };
	}

};
#endif // ZIP-iterator


int main(/*int argc, char** argv*/)
{
	{
#ifdef iterator_stopper
		if (argc < 2) {
			cout << "Please provide one parameter!" << endl;
			return 1;
		}
		for (char c : cstring_range(argv[1])) {
			cout << c;
		}
#endif // iterator_stopper
#ifdef simple_iterator
		for (int i : num_range{ 100,110 }) {
			std::cout << i << ", ";
		}
		cout << "\n";
#endif // simple_iterator
#ifdef iterator_to_stl
		num_range r{ 100,110 };
		auto [min_it, max_it](minmax_element(begin(r), end(r)));
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
#ifdef code_revise
		vector<int> v{ 1,2,3 };
		v.shrink_to_fit();
		const auto it(begin(v));
		cout << *it << endl;
		v.push_back(123);
		cout << *it << endl;
#endif // code_revise

#ifdef ZIP_iterator	
	using namespace std;
	vector<double> a{ 1.0,2.0,3.0 };
	vector<double> b{ 4.0,5.0,6.0 };
	zipper zipped{ a,b };
	const auto add_product([](double sum, const auto& p) {
		return sum + p.first * p.second;
		});
	const auto dot_product(std::accumulate(begin(zipped), end(zipped), 0.0, add_product));
	cout << dot_product << "\n";

	valarray<double> aa{ 1.0,2.0,3.0 };
	valarray<double> bb{ 4.0,5.0,6.0 };
	cout << (aa * bb).sum() << endl;
#endif // ZIP_iterator
	}

}