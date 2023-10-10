#include <iostream>
using namespace std;
#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() {
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}*Head, * Tail;
	size_t size; //size_t - это unsigned int
	//Директива дает существующему типу данных новое имя:
	//typedef существующий_тип_данных новое_имя_этого_типа;
	class ConstBaseIterator 
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element*Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		
		bool operator==(const ConstBaseIterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const {
			return this->Temp != other.Temp;
		}

		const T& operator*() const {
			return Temp->Data;
		}
	};
public:
	class ConstIterator:public ConstBaseIterator {
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++() {
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator& operator++(int) {
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--() {
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator& operator--(int) {
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator: public ConstBaseIterator {
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator& operator++() {
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return*this;
		}
		ConstReverseIterator operator++(int) {
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--() {
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int) {
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator 
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*() {
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator {
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*() {
			return ConstBaseIterator::Temp->Data;
		}
	};
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstReverseIterator rbegin() const;
    ConstReverseIterator rend() const;

	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//               Operators:
	List<T>& operator=(const List<T>& other);

	//               Adding Elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int index);

	//               Deleting Elements:
	void pop_front();
	void pop_back();
	void erase(int index);
	//               Methods:
	void print()const;
	void reverse_print()const;
};

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
template<typename T>List<T>::List(const List<T>& other) :List() {
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