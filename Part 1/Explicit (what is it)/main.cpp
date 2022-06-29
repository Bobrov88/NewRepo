#include <iostream>
using namespace std;

class A {
public:
	A() {};
	A(int a) : a_{ a } {};
	int& GetA() { return a_; };
	int a_;
private:
};

void print(A a) {
	cout << a.a_ << endl;
}

int main()
{
	A a1;
	A a2(6);
	A a3(4);
	print(a2);
	print(a3);
	print(41); // This line throws with ctor(int) being declared explicit
	return 0;
}
