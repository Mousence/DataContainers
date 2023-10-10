#include <iostream>
using namespace std;
#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() {
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size; //size_t - ��� unsigned int
	//��������� ���� ������������� ���� ������ ����� ���:
	//typedef ������������_���_������ �����_���_�����_����;
public:
	class Iterator {
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp) {}
		~Iterator() {}

		Iterator& operator++() {
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator++(int) {
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--() {
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator& operator--(int) {
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const {
			return this->Temp != other.Temp;
		}
		const int& operator*() const {
			return Temp->Data;
		}
		int& operator*() {
			return Temp->Data;
		}
	};
	class ReverseIterator {
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ReverseIterator() {}

		ReverseIterator& operator++() {
			Temp = Temp->pPrev;
			return*this;
		}
		ReverseIterator operator++(int) {
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--() {
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int) {
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReverseIterator& other)const {
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const {
			return this->Temp != other.Temp;
		}

		int operator*() {
			return Temp->Data;
		}
	};
	const Iterator begin() const {
		return Head;
	}
	const Iterator end() const {
		return nullptr;
	}
	const ReverseIterator rbegin() {
		return Tail;
	}
	const ReverseIterator rend() {
		return nullptr;
	}
	List() {
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List() {
		for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
	}
	List(const List& other):List() {
		*this = other;
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~List() {
		while (Tail) pop_back();
		cout << "LDenstructor:\t" << this << endl;
	}
	//               Operators:
	List& operator=(const List& other) {
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		cout << "LCopyAssignment:\t" << this << "<-" << &other << endl;
		return *this;
	}

	//               Adding Elements:
	void push_front(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			Head = Tail = new Element(Data);
		}
		else {
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data) {
		if (Head == nullptr && Tail == nullptr) {
			Head = Tail = new Element(Data);
		}
		else {
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(int Data, int index) {
		if (index <= 0)return push_front(Data);
		if (index >= size)return push_back(Data);
		Element* Temp;
		if (index < size) {
			Temp = Head;
			for (int i = 0; i < index ; i++) Temp = Temp->pNext;
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
	void pop_front() {
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
	void pop_back() {
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
	void erase(int index) {
		if (index == 0)return pop_front();
		Element* Temp;

		if (size/2 > index) {
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
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab <<Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "����� ���������� ��������� ������: " << size << endl;
	}
	void reverse_print()const {
	for(Element*Temp = Tail;Temp;Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "����� ���������� ��������� ������: " << size << endl;
	}
};

List operator+(const List& left, const List& right) {
	List cat = left;
	for (List::Iterator it = right.begin(); it != right.end(); ++it)
		cat.push_back((*it) *= 10);
	return cat;
}

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

	List list1 = { 3,5,8,13,21 };
	List list2 = { 32,55,89 };
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
}