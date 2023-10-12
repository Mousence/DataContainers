#include <iostream>
#include "DLList.h"
#include "DLList.cpp"
using namespace std;
#define tab "\t"

//#define ITERATORSCHECK
int main() {
	setlocale(LC_ALL, "");
#ifdef ITERATORSCHECK
	List list = {3,5,7,8,13,21};
	list.print();
	for (int i : list)
		cout << i << tab; cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it) {
		cout << *it << tab;
	}
	cout << endl;
#endif // IteratorsCheck

	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 32,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	
	reverse_print(list3);
	for (List<int>::Iterator it = list3.begin(); it != list3.end(); ++it) {
		*it *= 10;
	}
	
	List<double> d_list = { 2.7,3.14,5.3,8.1 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "No", "money", "no", "honey" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}