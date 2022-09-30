#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;

//#define ostringstream_
//#define trim_spaces
//#define stringview 
//#define user_entering_data
#define words_in_sentences

#ifdef words_in_sentences
template <typename T>
size_t wordcount(T& is) {
	return distance(istream_iterator<string> {is}, {});
}
#endif // words_in_sentences


#ifdef stringview
void print(string_view v) {
	const auto words_begin(v.find_first_not_of(" \t\n"));
	v.remove_prefix(min(words_begin, v.size()));
	const auto words_end(v.find_last_not_of(" \t\n"));
	if (words_end != string_view::npos) {
		v.remove_suffix(v.size() - words_end - 1);
	}
	cout << "length: " << v.length()
		<< " [" << v << "]\n";
}
#endif // stringview

#ifdef trim_spaces
string trim_whitespaces_surrounding(const string& s) {
	const char whitespace[]{ " \t\n" };
	const size_t first(s.find_first_not_of(whitespace));
	if (string::npos == first) { return {}; }
	const size_t last(s.find_last_not_of(whitespace));
	return s.substr(first, last - first + 1);
}
#endif // trim_spaces

//int main() {

#ifdef words_in_sentences
int main(int argc, char** argv) {
	size_t wc;
	if (argc == 2) {
		ifstream ifs{ argv[1] };
		wc = wordcount(ifs);
	}
	else {
		wc = wordcount(cin);
	}
	cout << "There are " << wc << " words\n";
#endif // words_in_sentences


#ifdef user_entering_data
		cout << "Please enter two numbers:\n";
	int x;
	double y;
	if (cin >> x >> y) {
		cout << "You entered: " << x
			<< " and " << y << '\n';
	}
	else {
		cout << "Oh no, that did not go well!\n";
		cin.clear();
		cin.ignore(
			std::numeric_limits<std::streamsize>::max(),
			'\n');
	}
	cout << "now please enter some "
		"comma-separated names:\n";
	for (string s; getline(cin >> ws, s, ',');) {
		if (s.empty()) {
			break;
		}
		cout << "name: \"" << s << "\"\n";
	}
#endif // user_entering_data

#ifdef stringview
	int main(int argc, char* argv[]) {
		print(argv[0]);
		print({});
		print("a const char * array");
		print("an std::string_view literal"sv);
		print("an std::string instance"s);
		print(" \t\n foobar \n\t  ");
		char cstr[]{ 'a','b','c' };
		print(string_view(cstr, sizeof(cstr)));
	}
#endif // stringview

#ifdef trim_spaces
	string s{ " \t\n string surrounded be ugly"
				" whitespaces \t\n " };
	cout << "{" << s << "}" << endl;
	cout << "{"
		<< trim_whitespaces_surrounding(s)
		<< "}\n";
#endif // trim_spaces

#ifdef ostringstream_
	string a{ "a" };
	auto b("b"s);

	string_view c{ "c" };
	auto d{ "d"sv };
	cout << a << ", " << b << '\n';
	cout << c << ", " << d << '\n';
	cout << a + b << '\n';
	cout << a + string{ c } << '\n';
	ostringstream o;
	o << a << " " << b << " " << c << " " << d;
	auto concatenated(o.str());
	transform(begin(concatenated), end(concatenated),
		begin(concatenated), toupper);
	cout << concatenated << endl;
#endif // ostringstream_

};