#include <iostream>
#include <vector>
#include <cassert>

template<typename Iterator>
int Distance(Iterator begin, Iterator end) {
	int sum = 0;
	for (auto it = begin; it != end; ++it) {
		sum += 1;
		}
	return sum;
}

template<>
int Distance(int* begin, int* end) {
	return end - begin;
}

template<typename Iterator, typename Predicate>
int count_if(Iterator begin, Iterator end, Predicate pred) {
	int sum = 0;
	for (auto it = begin; it != end; ++it) {
		if (pred(*it)) {
			sum += 1;
		}
	}
	return sum;
}

template <class Iterator>
void double_each_element(Iterator begin, Iterator end) {
	for (auto it = begin; it != end; ++it) {
		*it *= 2;
		std::cout << *it << " ";
	}
	std::cout<<std::endl;
}

class putc_iterator {
	struct proxy {
		void operator=(char ch) { putc(ch, stdout); }
	};
public:
	proxy operator*() const { return proxy{}; }
	auto& operator++(int) { return *this; }
};

int main() {
	putc_iterator it;
	for (char ch : {'h', 'e', 'l', 'l', 'o', '\n'}) {
		*it++ = ch;
	}
	//std::vector<int> v{ 3,1,4,1,5,9,2,6 };
	//int number_above = count_if(v.begin(), v.end(), [](int e) { return e > 5; });
	//int number_below = count_if(v.begin(), v.end(), [](int e) { return e < 5; });

	//int total = Distance(v.begin(), v.end());
	//std::cout << total << std::endl;
	//assert(number_above == 2);
	//assert(number_below == 5);
	//assert(total == 8);

	/*double_each_element(v.begin(), v.end());
	double_each_element(v.begin(), v.begin()+3);
	double_each_element(&v[0], &v[3]);*/

	return 0;
}