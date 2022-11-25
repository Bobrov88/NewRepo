//#include <iostream>
//#include <chrono>
//#include <ratio>
//#include <cmath>
//#include <iomanip>
//#include <optional>
//
//using namespace std;
//using seconds = chrono::duration<double>;
//using milliseconds = chrono::duration<
//	double, ratio_multiply<seconds::period, milli>>;
//using microseconds = chrono::duration<
//	double, ratio_multiply<seconds::period, micro>>;
//
//static pair<string, seconds> get_input() {
//	string s;
//	const auto tic(chrono::steady_clock::now());
//	if (!(cin >> s)) {
//		return { {},{} };
//	}
//	const auto toc(chrono::steady_clock::now());
//	return { s, toc - tic };
//}
//
//int main() {
//	while (true) {
//		cout << "Please type th eword \"C++17\" as fast as you can \n ";
//		const auto [user_input, diff ] = get_input();
//		if (user_input == "") {
//			break;
//		}
//		if (user_input == "C++17") {
//			cout << "Bravo. You did it in:\n"
//				<< fixed << setprecision(2)
//				<< setw(12) << diff.count()
//				<< " seconds.\n"
//				<< setw(12) << milliseconds(diff).count()
//				<< " milliseconds.\n"
//				<< setw(12) << microseconds(diff).count()
//				<< " microseconds.\n";
//			break;
//		}
//		else {
//			cout << "Sorry, your input doesn't match."
//				" You may try again.\n";
//		}
//	}
//}
 
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <iomanip>
//#include <chrono>
//
//using namespace std;
//
//ostream& operator<<(ostream& os, const chrono::time_point<chrono::system_clock>& t) {
//	const auto tt(chrono::system_clock::to_time_t(t));
//	const auto loct(std::localtime(&tt));
//	return os << put_time(loct, "%c");
//}
//
//using days = chrono::duration <
//	chrono::hours::rep,
//	ratio_multiply<chrono::hours::period, ratio<24>>>;
//
//constexpr days operator""_days(unsigned long long h) {
//	return days{ h };
//}
//
//
//int main() {
//	auto now(chrono::system_clock::now());
//	cout << "The current date and time is " << now << '\n';
//	chrono::hours chrono_12h{ 12 };
//	cout << "In 12 hours, it will be "
//		<< (now + chrono_12h) << '\n';
//	using namespace chrono_literals;
//	cout << "12 hours and 15 minutes ago, it was "
//		<< (now - 12h - 15min) << '\n'
//		<< "1 week ago, it was "
//		<< (now - 7_days) << "\n";
//}

//#include <iostream>
//#include <optional>
//using namespace std;
//
//using oint = optional<int>;
//
//oint read_int() {
//	int i;
//	if (cin >> i) { return { i }; }
//	return {};
//}
//
//oint operator+(oint a, oint b) {
//	if (!a || !b) { return oint{}; }
//	return { *a + *b };
//}
//
//oint operator+(oint a, int b) {
//	if (!a) { return oint{}; }
//	return { *a + b };
//}
//
//int main() {
//	cout << "Please enter 2 interegs" << endl;
//	auto a{ read_int() };
//	auto b{ read_int() };
//	auto sum{ a + b + 10 };
//
//	if (sum) {
//		cout << *a << " + " << *b << " + 10 = " << *sum << "\n";
//	}
//	else {
//		cout << "Sorry" << endl;
//	}
//}

//#include <iostream>
//#include <iomanip>
//#include <tuple>
//#include <functional>
//#include <string>
//#include <list>
//
//using namespace std;
//
//static void print_student(size_t id, const string& name, double gpa) {
//	cout << "Student " << quoted(name)
//		<< ", ID: " << id
//		<< ", GPA: " << gpa << "\n";
//}
//
//int main() {
//	using student = tuple<size_t, string, double>;
//	student john{ 123, "John Doe"s, 3.7 };
//	{
//		const auto& [id, name, gpa] = john;
//		print_student(id, name, gpa);
//	}
//	cout << "------\n";
//	auto arguments_for_later = {
//		make_tuple(234, "John Doe"s, 3.7),
//		make_tuple(345, "Billy Foo"s, 4.0),
//		make_tuple(456, "Cathy Bar"s, 3.5)
//	};
//	for (const auto& [id, name, gpa] : arguments_for_later) {
//		print_student(id, name, gpa);
//	}
//	cout << "------\n";
//
//	apply(print_student, john);
//	cout << "------\n";
//	for (const auto& args : arguments_for_later) {
//		apply(print_student, args);
//	}
//}

#include <iostream>
#include <tuple>
#include <list>
#include <utility>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <any>
#include <variant>

//using namespace std;
//
//class cat {
//	string name;
//public:
//	cat(string n) : name{ n } {}
//	void meow() const {
//		cout << name << " says Meow!\n";
//	}
//};
//
//class dog {
//	string name;
//public:
//	dog(string n) : name{ n } {}
//	void woof() const {
//		cout << name << " says Woof!\n";
//	}
//};
//
//using animal = variant<dog, cat>;
//
//template <typename T>
//bool is_type(const animal& a) {
//	return holds_alternative<T>(a);
//}
//
//struct animal_voice {
//	void operator()(const dog& d) const { d.woof(); }
//	void operator()(const cat& c) const { c.meow(); }
//};
//
//int main() {
//	list<animal> l{ cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"} };
//	for (const animal& a : l) {
//		switch (a.index()) {
//		case 0: get<dog>(a).woof(); break;
//		case 1: get<cat>(a).meow(); break;
//		}
//	}
//	cout << "-----\n";
//	for (const animal& a : l) {
//		if (const auto d(get_if<dog>(&a)); d) { d->woof(); }
//		else if (const auto c(get_if<cat>(&a)); c) { c->meow(); }
//	}
//	cout << "-----\n";
//
//	for (const animal& a : l) {
//		visit(animal_voice{}, a);
//	}
//	cout << "----\n";
//
//	cout << "There are "
//		<< count_if(begin(l), end(l), is_type<cat>)
//		<< " cats and "
//		<< count_if(begin(l), end(l), is_type<dog>)
//		<< " dogs in the list.\n";
//}

//using int_list = list<int>;
//
//void print_anything(const any& a) {
//	if (!a.has_value())
//		cout << "Nothing. \n";
//	else if (a.type() == typeid(string)) {
//		cout << "It's a string: "
//			<< quoted(any_cast<const string&>(a)) << '\n';
//	}
//	else if (a.type() == typeid(int)) {
//		cout << "It's an integer: "
//			<< any_cast<int>(a) << '\n';
//	}
//	else if (a.type() == typeid(int_list)) {
//		const auto& l(any_cast<const int_list&>(a));
//		cout << "It's a list: ";
//		copy(begin(l), end(l),
//			ostream_iterator<int>{cout, ", "});
//		cout << '\n';
//	}
//	else {
//		cout << "Can't handle this item.\n";
//	}
//}
//
//int main() {
//	print_anything({});
//	print_anything("abc"s);
//	print_anything(123);
//	print_anything(int_list{1,2,3});
//	print_anything(any(in_place_type_t<int_list>{}, { 1,2,3 }));
//}

#include <iostream>
#include <memory>
#include <iomanip>
using namespace std;

//class Foo {
//public:
//	string name;
//	Foo(string n) : name {move(n)}
//	{
//		cout << "CTOR " << name << endl;
//	}
//	~Foo() { cout << "DTOR " << name << endl; }
//};
//
//void process_item(unique_ptr<Foo> p) {
//	if (!p) { return; }
//	cout << "Processing " << p->name;
//}
//
//int main() {
//	{
//		unique_ptr<Foo> p1{ new Foo{"foo"} };
//		auto p2{ make_unique<Foo>("bar") };
//	}
//	process_item(make_unique<Foo>("foo1"));
//	auto p1(make_unique<Foo>("foo2"));
//	auto p2(make_unique<Foo>("foo3"));
//	process_item(move(p1));
//	cout << "End of main()" << endl;
//}

//class Foo {
//public:
//	string name;
//	Foo(string n) : name {move(n)}
//	{
//		cout << "CTOR " << name << endl;
//	}
//	~Foo() { cout << "DTOR " << name << endl; }
//};
//
//void process_item(unique_ptr<Foo> p) {
//	if (!p) { return; }
//	cout << "Processing " << p->name;
//}
//
//void f(shared_ptr<Foo> sp) {
//	cout << "f: use counter at "
//		<< sp.use_count() << endl;
//}
//
//int main() {
//	shared_ptr<Foo> fa;
//	{
//		shared_ptr<Foo> p1{ new Foo{"foo"} };
//		auto p2{ make_shared<Foo>("bar") };
//		cout << "p1 " << p1.use_count() << endl;
//		fa = p1;
//		cout << "p1 " << p1.use_count() << endl;
//	}
//	cout << "Back to outer scope" << endl;
//	cout << fa.use_count() << endl;
//	cout << "first f() call" << endl;
//	f(fa);
//	cout << "second f() call" << endl;
//	f(move(fa));
//	cout << "end";
//}

struct Foo {
	int value;
	Foo(int i) : value{ i } {}
	~Foo() { cout << "DTOR Foo " << value << endl; }
};

void weak_ptr_info(const weak_ptr<Foo>& p) {
	cout << endl << boolalpha << "expired: " << p.expired()
		<< " use_count: " << p.use_count()
		<< " content: ";

	if (const auto sp(p.lock()); sp) {
		cout << sp->value << endl;
	}
	else {
		cout << "<null>" << endl;
	}
}

int main() {
	weak_ptr<Foo> weak_foo;
	weak_ptr_info(weak_foo);
	{
		auto shared_foo(make_shared<Foo>(1337));
		weak_foo = shared_foo;
		weak_ptr_info(weak_foo);
	}
	weak_ptr_info(weak_foo);

}
