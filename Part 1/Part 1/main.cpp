#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class container_of_ints {
public:
	virtual int size() const = 0;
	virtual int& at(int i) = 0;
};

class array_of_ints : public container_of_ints {
	int data[10]{};
public:
	int size() const override {
		return 10;
	}
	int& at(int i) override { return data[i]; }
};

class list_if_ints : public container_of_ints {
	int _size{ 0 };
	struct node {
		int data;
		node* pnext;
	};
	node* head_ = nullptr;
public:
	int size() const override { return _size; }
	int& at(int i) {
		if (i > _size) throw std::out_of_range("at");
		node* p = head_;
		for (int j = 0; j < i; j++) p = p->pnext;
		return p->data;
	}
	~list_if_ints() {};
};

template<class ContainerModel>
void double_each_element(ContainerModel& arr) {
	for (int i = 0; i < arr.size(); i++) {
		arr.at(i) *= 2;
	}
}

template<class Container>
int count(const Container& container) {
	int sum = 0;
	for (auto& elt : container) {
		sum += 1;
	}
	return sum;
}

template<class Container, class Predicate>
int count_if(const Container& container, Predicate pred) {
	int sum = 0;
	for (auto&& elt : container) {
		if (pred(elt)) {
			sum += 1;
		}
	}
	return sum;
}

int main() {
	array_of_ints arr;
	double_each_element(arr);
	list_if_ints lst;
	double_each_element(lst);
	std::vector<int> vec = { 1,2,3 };
	double_each_element(vec);
	std::vector<double> vecd = { 1.0,2.0,3.0 };
	double_each_element(vecd);
	std::vector<int> v = { 3,1,4,1,5,9,2,6 };
	assert(count(v) == 8);
	int number_above =
		count_if(v, [](int e) { return e > 5; });
	int number_below = 
		count_if(v, [](int e) { return e < 5; });
	assert(number_above == 2);
	assert(number_below == 5);	
}