#include <iostream>
#include <vector>	
#include <list>
using namespace std;

class A {
public:
	A() {};
	/*explicit*/ A(int a) : a_{a} {};
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

	vector<int> I{ 1,2,3,4,5,6,7,8,9 };
	vector<bool> B{ true, true, false, false, true, true };
	for (auto &&i : I) cout << i << " ";
	cout << endl;
	for (auto &&i : B) cout << i << " ";
	int F[] = { 1,2,3,4,5,6,7,8 };
	cout << endl;
	for (auto i : F) cout << i << " ";
	cout << endl;
	list<int> L{ 1,2,3,4,5,6,7,8 };
	for (auto &&i : L) cout << i << " ";
	cout << endl;
	return 0;
}
