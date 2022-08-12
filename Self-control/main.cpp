#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <list>
#include <string>
#include <map>
using namespace std;

//#define ERASE_REMOVE
//#define DELETING_O1
//#define QUICK_SAFE_ACCESS
//#define SAVE_SORTED
//#define SAFE_IMSERT_INTO_MAP
//#define HINTS
//#define CHANGE_KEYS

#ifdef  ERASE_REMOVE
struct coord {
	double x;
	double y;
};
#endif //  ERASE_REMOVE

#ifdef SAFE_IMSERT_INTO_MAP
struct birthday {
	string name;
	string month;
	size_t age;
};
#endif // SAFE_IMSERT_INTO_MAP


int main() {
#ifdef ERASE_REMOVE
	vector<coord> V{ {1.0,3.2},
		{2.6,3.9},
		{5.2,4.4},
		{0.8,-5.6} };
	assert(V.size() == 4);
	V.erase(remove_if(begin(V), end(V), [](coord& el) { return el.x > 2.0; }), V.end());
	assert(V.size() == 2);
#endif // ERASE_REMOVE

#ifdef DELETING_O1
	vector<int> IV{ 1,2,3,4,5,6,7,8 };
	auto __idx(begin(IV) + 2);
	*__idx = move(IV.back());
	IV.pop_back();
	assert(*__idx == 8);
	assert(IV.size() == 7);
#endif // DELETING_O1

#ifdef QUICK_SAFE_ACCESS
	vector<char> CV{ '1','2', '3', '4','5' };
	assert(CV.at(1) == '2');
	assert(*CV.begin() == '1');
	assert(*(CV.end() - 1) == '5');
	try
	{
		cout << CV[CV.size()];
	}
	catch (const out_of_range& ex) {
		cout << ex.what();
	}
#endif // QUICK_SAFE_ACCESS

#ifdef SAVE_SORTED
	vector<double> _dv{ 1.3,4.2,5.7,-4.6,5.3,1.2,3.3 };
	for (auto& el : _dv) {
		cout << el << "  ";
	}
	cout << endl;
	sort(begin(_dv), end(_dv));
	double inserted_value = 4.3;
	for (auto& el : _dv) {
		cout << el << "  ";
	}
	cout << endl;
	_dv.insert(lower_bound(begin(_dv), end(_dv), inserted_value), inserted_value);
	for (auto& el : _dv) {
		cout << el << "  ";
	}
	cout << endl;
#endif // SAVE_SORTED

#ifdef SAFE_IMSERT_INTO_MAP
	list<birthday> _blist{
		{"Dmitriy", "august", 34},
		{"Victor", "march", 34},
		{"Alina", "march", 27},
		{"Murad", "december", 33},
		{"Leonid", "june", 32},
		{"Timur", "april", 34},
		{"Amaliya", "february", 7},
		{"Albina", "november", 26},
		{"Dobriy", "february", 34},
		{"Veta", "june", 39},
		{"Vlad", "february", 4}
	};
	_blist.sort([](birthday& first, birthday& second) {
		return first.age < second.age;
		});
	map <string, pair <const birthday, size_t>> _m;
	for (const auto&el : _blist) {
		auto [_it, _is_inserted] = _m.try_emplace(el.month, el, 1);
		if (_is_inserted == false) {
			++_it->second.second;
		}
	}
	for (const auto& el : _m) {
		cout << "In " << el.first		<< " the youngest man is " 
			 << el.second.first.name	<< " and there are "
			 << el.second.second		<< " people at all" << endl;
	}
#endif // SAFE_IMSERT_INTO_MAP

#ifdef HINTS
	list<int> _li{ 3,6,2,7,9,3,6,-1,3,7,53,43,5,456,2,54,54,5 };
	map<int, int> _mi;
	auto iterator{ _mi.end() };
	int i{ 0 };
	for (const auto& el : _li) {
		iterator = _mi.insert(iterator, { i++,el });
	}
	for (const auto& el : _mi) {
		cout << "< " << el.first << " : " << el.second << " >" << endl;
	}
#endif // HINTS

#ifdef CHANGE_KEYS
	map<size_t, string> _ms{
		{1,"Moscow"},
		{2,"Kaluga"},
		{3,"Ryazan'"},
		{4,"Tula"},
		{5,"Kozelsk"},
		{6,"Tashkent"},
		{6,"Shimkent"}
	};
	try {
		auto l = _ms.extract(1);
		auto r = _ms.extract(6);
		swap(r.key(), l.key());
		_ms.insert(move(r));
		_ms.insert(move(l));
	}
	catch (const out_of_range& ex) {
		cout << "Out of range!" << ex.what() << endl;
	}
	for (const auto& el : _ms) {
		cout << el.first << " - " << el.second << endl;
	}


#endif // CHANGE_KEYS


	return 0;
}