#include "DLList.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////
////////////                  List member-functions                 //////////////////////

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right) {
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it) {
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
}

template<typename T> void reverse_print(const List<T>& list) {
	// Когда вот так вызывается it то нужно написать typename
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it) {
		cout << *it << tab;
	}
	cout << endl;
}
//Если возвращается имя типа пишем typename, чтобы избежать ошибок
template<typename T>typename List<T>::ConstIterator List<T>::begin() const {
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end() const {
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin() const {
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend() const {
	return nullptr;
}

template<typename T>typename List<T>::Iterator List<T>::begin() {
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end() {
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin() {
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend() {
	return nullptr;
}
template<typename T> List<T>::List() {
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List() {
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
template<typename T>List<T>::List(const List<T>& other) : List() {
	*this = other;
	//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List() {
	while (Tail) pop_back();
	cout << "LDenstructor:\t" << this << endl;
}
//               Operators:
template<typename T> List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	cout << "LCopyAssignment:\t" << this << "<-" << &other << endl;
	return *this;
}

//               Adding Elements:
template<typename T> void List<T>::push_front(T Data) {
	if (Head == nullptr && Tail == nullptr) {
		Head = Tail = new Element(Data);
	}
	else {
		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T> void List<T>::push_back(T Data) {
	if (Head == nullptr && Tail == nullptr) {
		Head = Tail = new Element(Data);
	}
	else {
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T> void List<T>::insert(T Data, int index) {
	if (index <= 0)return push_front(Data);
	if (index >= size)return push_back(Data);
	Element* Temp;
	if (index < size) {
		Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
	}
	else {
		Temp = Tail;
		for (int i = size; i < index - 1; i--) Temp = Temp->pPrev;
	}
	Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}

//               Deleting Elements:
template<typename T> void List<T>::pop_front() {
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail) {
		delete Head;
		Head = Tail = nullptr;
		return;
		this;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T> void List<T>::pop_back() {
	if (Head == Tail)return pop_front();
	if (Head == Tail) {
		delete Tail;
		Head = Tail = nullptr;
		return;
	}
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T> void List<T>::erase(int index) {
	if (index == 0)return pop_front();
	Element* Temp;

	if (size / 2 > index) {
		Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = size; i < index - 1; i++) Temp = Temp->pPrev;
	}

	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}
//               Methods:
template<typename T> void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Общее количество элементов списка: " << size << endl;
}
template<typename T> void List<T>::reverse_print()const {
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Общее количество элементов списка: " << size << endl;
}
////////////                  List member-functions                 //////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//#define ITERATORSCHECK