#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>
using namespace std;

//#define simple_iterator
//#define iterator_to_stl
#define iterator_adapters
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


int main()
{
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

}