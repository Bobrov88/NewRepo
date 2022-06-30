#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include <forward_list>
using namespace std;

//class container_of_ints {
//public:
//	virtual int size() const = 0;
//	virtual int& at(int i) = 0;
//};
//
//class array_of_ints : public container_of_ints {
//	int data[10]{};
//public:
//	int size() const override {
//		return 10;
//	}
//	int& at(int i) override { return data[i]; }
//};

	struct list_node {
		int data;
		list_node* pnext;
	};

	template <bool Const>
	class list_of_ints_iterator {
		friend class list_of_ints;
		friend class list_of_ints_iterator<!Const>;

		using node_pointer = std::conditional_t<Const, const list_node*, list_node*>;
		node_pointer ptr_;

		explicit list_of_ints_iterator(node_pointer p) : ptr_(p) { }

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = int;
		using pointer = std::conditional_t<Const, const int*, int*>;
		using reference = std::conditional_t <Const, const int&, int&>;
		using iterator_category = std::forward_iterator_tag;

		reference operator*() const { return ptr_->data; };
		auto& operator++() { ptr_ = ptr_->pnext; return *this; }
		auto operator++(int) { auto it = *this; ++* this; return it; }

		template <bool R>
		bool operator==(const list_of_ints_iterator<R>& rhs) const {
			return ptr_ == rhs.ptr_;
		}

		template <bool R>
		bool operator!=(const list_of_ints_iterator<R>& rhs) const {
			return ptr_ != rhs.ptr_;
		}

		operator list_of_ints_iterator<true>() const
		{
			return list_of_ints_iterator<true>(ptr_);
		}
	};

	class list_of_ints /*:public container_of_ints */ {
		int _size{ 0 };
		list_node* head_ = nullptr;
		list_node* tail_ = nullptr;
	public:
		using const_iterator = list_of_ints_iterator<true>;
		using iterator = list_of_ints_iterator<false>;
		iterator begin() { return iterator{ head_ }; }
		iterator end() { return iterator{ nullptr }; }
		const_iterator begin() const { return const_iterator{ head_ }; }
		const_iterator end() const { return const_iterator{ nullptr }; }
		int size() const /*override*/ { return _size; }
		int& at(int i) {
			cout << "List at entered" << endl;
			if (i > _size) throw std::out_of_range("at");
			list_node* p = head_;
			for (int j = 0; j < i; j++) p = p->pnext;
			return p->data;
		}
		void push_back(int value) {
			list_node* new_tail = new list_node{ value, nullptr };
			if (tail_) {
				tail_->pnext = new_tail;
			}
			else {
				head_ = new_tail;
			}
			tail_ = new_tail;
			_size += 1;
		}

		~list_of_ints() {
			for (list_node* next, *p = head_; p != nullptr; p = next) {
				next = p->pnext;
				delete p;
			}
		};
	};

template<class ContainerModel>
void double_each_element(ContainerModel& arr) {
	for (int i = 0; i < arr.size(); i++) {
		arr.at(i) *= 2;
	}
}

template<class Container>
int count(Container& container) {
	int sum = 0;
	for (auto& elt : container) {
		sum += 1;
	}
	return sum;
}

template<class Container, class Predicate>
int count_if(Container& ctr, Predicate pred) {
	int sum = 0;
	//for (auto&& elt : container) {
	for (auto it = ctr.begin(); it != ctr.end(); ++it) {
		if (pred(*it)) {
			sum += 1;
		}
	}
	return sum;
}

void foo(std::bidirectional_iterator_tag t [[maybe_unused]] )
{
	puts("std::vector's iterators are indeed bidirectional...");
}

void bar(std::random_access_iterator_tag)
{
	puts("...and random-access, too");
}

void bar(std::forward_iterator_tag)
{
	puts("forward_iterator_tag is not as good a match");
}

int main() {
	using it = std::vector<int>::iterator;
	foo(it::iterator_category{});
	bar(it::iterator_category{});
	//array_of_ints arr;
	//double_each_element(arr);
	//list_of_ints lst;
	/*lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(-2);
	lst.push_back(0);*/
	//double_each_element(lst);
	//cout << count_if(lst, [](int a) { return a > 0; });
	/*std::vector<int> vec = { 1,2,3 };
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
	assert(number_below == 5);	*/
}