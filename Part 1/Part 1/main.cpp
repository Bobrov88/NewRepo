#include <iostream>
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

void double_each_element(container_of_ints& arr) {
	for (int i = 0; i < arr.size(); i++) {
		arr.at(i) *= 2;
	}
}

void main() {
	array_of_ints arr;
	double_each_element(arr);
	list_if_ints lst;
	double_each_element(lst);
}