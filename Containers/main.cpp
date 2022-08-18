#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <list>
#include <map>
#include <functional>
#include <unordered_map>
#include <set>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <queue>
#include <tuple>
using namespace std;

//void insert_sorted(vector<string>& v, const string& word) {
//	const auto insert_pos(lower_bound(begin(v), end(v), word));
//	v.insert(insert_pos, word);
//}

//template <typename IT>
//double evaluate_rpn(IT it, IT end) {
//	stack<double> val_stack;
//	auto pop_stack([&]() {
//		auto r(val_stack.top());
//		val_stack.pop();
//		return r;
//		});
//	map < string, double(*)(double, double)> ops{
//		{ "+", [](double a, double b) {return a + b; } },
//		{ "-", [](double a, double b) {return a - b; } },
//		{ "*", [](double a, double b) {return a * b; } },
//		{ "/", [](double a, double b) {return a / b; } },
//		{ "^", [](double a, double b) {return pow(a,b); } },
//		{ "%", [](double a, double b) {return fmod(a,b); } }
//			};
//	for (; it != end; ++it) {
//		stringstream ss{ *it };
//		if (double val; ss >> val) {
//			val_stack.push(val);
//		}
//		else {
//			const auto r{ pop_stack() };
//			const auto l{ pop_stack() };
//			try {
//				const auto& op(ops.at(*it));
//				//cout << typeid(op).name();
//				const double result(op(l, r));
//				val_stack.push(result);
//			}
//			catch (const out_of_range&) {
//				throw invalid_argument(*it);
//			}
//		}
//	}
//	return val_stack.top();
//}

//struct billionaire {
//	string name;
//	double dollars;
//	string country;
//};

//template <typename M>
//void print(const M& m) {
//	cout << "Race replacement:\n";
//	for (const auto& [placement, driver] : m) {
//		cout << placement << ": " << driver << "\n";
//	}
//}

//struct coord {
//	int x;
//	int y;
//};

//bool operator==(const coord& l, const coord& r) {
//	return l.x == r.x && l.y == r.y;
//}

//namespace std {
//	template <>
//	struct hash<coord> {
//		using argument_type = coord;
//		using result_type = size_t;
//		result_type operator()(const argument_type& c) const {
//			return static_cast<result_type>(c.x)
//				+ static_cast<result_type>(c.y);
//		}
//	};
//}

//string filter_punctuation(const string &s) {
//	const char* forbidden{ ".,:; " };
//	const auto idx_start(s.find_first_not_of(forbidden));
//	const auto idx_end(s.find_last_not_of(forbidden));
//	return s.substr(idx_start, idx_end - idx_start + 1);
//	}

string filter_ws(const string& s) {
	const char* ws{ " \r\n\t" };
	const auto a(s.find_first_not_of(ws));
	const auto b(s.find_last_not_of(ws));
	if (a == string::npos) { return {}; }
	return s.substr(a, b - a + 1);
}

multimap<size_t, string> get_sentence_stats(const string& content) {
	multimap<size_t, string> ret;
	const auto end_it(end(content));
	auto it1(begin(content));
	auto it2(find(it1, end_it, '.'));
	while (it1 != end_it && distance(it1, it2) > 0) {
		string s{ filter_ws({it1,it2}) };
		if (s.length() > 0) {
			const auto words(count(begin(s), end(s), ' ') + 1);
			ret.emplace(make_pair(words, move(s)));
		}
		if (it2 == end_it) break;
		it1 = next(it2, 1);
		it2 = find(it1, end_it, '.');
	}
	return ret;
}

int main()
{
	/*vector<int> v{1,2,3,2,5,2,6,2,4,8};
	const auto new_end(remove(begin(v), end(v), 2));
	v.erase(new_end, end(v));
	for (auto& i : v) cout << i << " ";
	v.shrink_to_fit();*/

	//auto idx = find(begin(v), end(v), 2);
	//if (idx < v.end()) {
	//	*idx = move(v.back());
	//	v.pop_back();
	//}
	//else cout << "Out of range!" << endl;

	//vector<string>  v{ "some","random","words","without","order","aaa","yyy" };
	//assert(false == is_sorted(begin(v), end(v)));
	//sort(begin(v), end(v));
	//assert(true == is_sorted(begin(v), end(v)));
	//insert_sorted(v, "foobar");
	//insert_sorted(v, "zzz");
	//for (auto& i : v) {
	//	cout << i << "\t";
	//}

	/*list<billionaire> billionaires{
		{"Warren Buffet", 75.6, "USA"},
		{"Bill Gates", 86.0, "USA"},
		{"Jeff Bezos", 72.8, "USA"},
		{"Mark Zuckerberg", 56.0, "USA"},
		{"Amancio Ortega", 71.3, "Spain"},
		{"Bernard Arnault", 41.5, "France"},
		{"Carlos Slim", 54.5, "Mexico"},
		{"Wang Jianlin", 31.3, "China"},
		{"Lilliane Bettencourt", 39.5,"France"},
		{"Li Ka-Shing", 31.2, "Hong Kong"}
	};
	billionaires.sort([](billionaire& first, billionaire& second) {
		return first.dollars > second.dollars;
		});
	map<string, pair<const billionaire, size_t>> m;
	for (const auto& b : billionaires) {
		auto [iterator, success] = m.try_emplace(b.country, b, 1);
		if (!success) {
			iterator->second.second += 1;
		}
	}
	for (const auto& [key, value] : m) {
		const auto& [b, count] = value;
		cout << b.country << " : " << count
			<< " billionaires. Richest is "
			<< b.name << " with " << b.dollars
			<< "B$\n";
	}*/

	//std::map<string, size_t> m{ {"b", 1}, {"c",2}, {"d",3} };
	//auto insert_it(std::end(m));
	//for (const auto& s : { "z","y","x","w" }) {
	//	insert_it = m.insert(insert_it, { s,1 });
	//}
	//return 0;

	//map<int, string> race_placement{
	//	{1, "Mario"}, {2,"Luigi"}, {3, "Bowser"},
	//	{4, "Peach"}, {5,"Yoshi"}, {6, "Koopa"},
	//	{7, "Toad"},{8,"Donkey Kong Jr."}
	//};
	//print(race_placement);
	//{
	//	auto a(race_placement.extract(3));
	//	auto b(race_placement.extract(8));
	//	swap(a.key(), b.key());
	//	race_placement.insert(move(a));
	//	race_placement.insert(move(b));
	//}
	//print(race_placement);

	//std::unordered_map<coord, int> m{
	//	{{0,0},1},
	//	{{0,1},2},
	//	{{2,1},3}
	//};
	//for (const auto& [key, value] : m) {
	//	std::cout << "((" << key.x << "," << key.y << "):" << value << ") ";
	//}
	
	//set<string> s;
	ifstream file("1.txt");
	if (!file.is_open()) return -5;
	////{
	////	istream_iterator<string> it{ file };
	////	istream_iterator<string> end;
	////	copy(it, end, inserter(s, s.end()));
	////}
	////else cout << "File not found!" << endl;
	////for (const auto &word : s) {
	////	cout << word << " ";
	////}
	////cout << "\n";
	//	//try {
	////	cout << evaluate_rpn(istream_iterator<string> {file}, {}) << endl;
	////}
	////catch (const invalid_argument& e) {
	////	cout << "Invalid argument: " << e.what() << "\n";
	////}
	//using item_type = std::pair<int, std::string>;
	//priority_queue<item_type> q;
	//initializer_list<item_type> il{
	//	{1, "dishes"},
	//	{0, "watch TV"},
	//	{0, "read comics"},
	//	{2, "do homework"}
	//};
	//for (auto & el : il) {
	//	q.push(el);
	//}
	//while (!q.empty()) {
	//	cout << q.top().first << ": " << q.top().second << endl;
	//	q.pop();
	//}
	//cout << endl;

	file.unsetf(ios::skipws);
	string content(istream_iterator<char>{file}, {});
	for (const auto& [word_count, sentence] : get_sentence_stats(content)) {
		cout << word_count << " words: " << sentence << ".\n";
	}

	file.close();

	//ifstream file("1.txt");
	//if (!file.is_open()) return 0;
	//map<string, size_t> words;
	//int max_word_len{ 0 };
	//string s;
	//while (file >> s) {
	//	auto filtered(filter_punctuation(s));
	//	max_word_len = max<int>(max_word_len, filtered.length());
	//	++words[filtered];
	//}
	//vector < pair<string, size_t>> word_counts;
	//word_counts.reserve(words.size());
	//move(begin(words), end(words), back_inserter(word_counts));
	//sort(begin(word_counts), end(word_counts), [](const auto& a, const auto& b) {
	//	return a.second > b.second;
	//	});
	//cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
	//for (const auto& [word, count] : word_counts) {
	//	cout << setw(static_cast<streamsize>(max_word_len + 2)) << word << " #" << count << "\n";
	//}
	//file.close();

	return 0;
}