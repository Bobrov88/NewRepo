#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <locale>
#include <iomanip>
#include <vector>
#include <map>
#include <numeric>
using namespace std;

//#define ostringstream_
//#define trim_spaces
//#define stringview 
//#define user_entering_data
//#define words_in_sentences
//#define output_formatting

//#define output_overload
#define istream_into_map

#ifdef istream_into_map
struct meme {
	string description;
	size_t year;
};

istream& operator>>(istream& is, meme& m) {
	return is >> quoted(m.description) >> m.year;
}

istream& operator>>(istream& is,
	pair<string, meme>& p) {
	return is >> quoted(p.first) >> p.second;
}
#endif // istream_into_map


#ifdef output_overload
struct city {
	string name;
	size_t population;
	double latitude;
	double longitude;
};

istream& operator>>(istream&, city&);

istream& operator++(istream& is) {
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max());
//	is.ignore(std::numeric_limits<std::streamsize>::max());
	return is;
}

istream& operator>>(istream& is, city& c) {
	is >> ws;
	getline(is, c.name);
	is >> c.population
		>> c.latitude
		>> c.longitude;
	if (!is && !is.eof()) ++is;
	return is;
}

#endif // output_overload

#ifdef output_formatting
void print_aligned_demo(int val,
						size_t width,
						char fill_char = ' ')
{
	cout << "=================\n";
	cout << setfill(fill_char);
	cout << left << setw(width) << val << '\n';
	cout << right << setw(width) << val << '\n';
	cout << internal << setw(width) << val << '\n';
}
#endif // output_formatting

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

int main() {

#ifdef istream_into_map
	ifstream file{ "2.txt" };
	map<string, meme> m;
	copy(istream_iterator<pair<string, meme>> {file},
		{},
		inserter(m, end(m)));

	auto max_func([](size_t old_max,
		const auto& b) {
			return max(old_max, b.first.length());
		});
	size_t width{ accumulate(begin(m),end(m),
		0u, max_func) };

	for (const auto& [meme_name, meme_desc] : m) {
		const auto& [desc, year] = meme_desc;
		cout << left << setw(width) << meme_name
			<< " : " << desc
			<< " , " << year << '\n';
	}
#endif // istream_into_map


#ifdef output_overload
	vector<city> l;
	ifstream file{ "1.txt" };
	copy(istream_iterator<city> {file}, {}, back_inserter(l));
	for (const auto& [name, pop, lat, lon] : l) {
		cout << left << setw(20) << name
			<< " population=" << pop <<'\t'
			<< " lat=" << lat << '\t'
			<< " lon=" << lon << '\n';
	}
#endif // output_overload

#ifdef output_formatting
	print_aligned_demo(123456, 15);
	print_aligned_demo(123456, 15, '_');

	cout << hex << showbase;
	print_aligned_demo(0x123abc, 15);
	cout << oct;
	print_aligned_demo(0123456, 15);

	cout << "A hex number with upper case letters: "
		<< hex << uppercase << 0x12abc << '\n';
	cout << "A number: " << 100 << '\n';
	cout << dec;
	cout << "Oops. now in decimal again: " << 100 << '\n';
	cout << "doubles: " << 12.3 << " " << 12.0 << ", " << showpoint << 12.0 << '\n';
	cout << "scientific double: " << hexfloat
		<< 12300000000.123 << '\n';
	cout << "fised      double " << fixed
		<< 12300000000.123 << '\n';
	cout << "Very precise double: "
		<< setprecision(10) << 0.000000001 << '\n';
	cout << "Less precise double: "
		<< setprecision(1) << showpos<<0.000000001 << '\n';
#endif // output_formatting

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