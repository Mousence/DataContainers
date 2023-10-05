#include <iostream>

using namespace std;
using std::cout;

class Element {
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev) {
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element() {
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}

	friend class DoubleLinkedList;
};

class DoubleLinkedList {
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	DoubleLinkedList() {
		this->Head = nullptr;
		if (!(/*count*/size))this->Tail = nullptr;
		else this->Tail = Tail->pNext;
		this->size = 0;
		cout << "DLConstructor:\t" << this << endl;
	}

	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		Tail = new Element(Data);
		Tail->pNext = nullptr;
		Tail->Data = Data;
	}
	void pop_front() {
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_back() {
		if (Tail == nullptr)return;
		Element* Erased = Tail;
		Tail->pPrev = Tail;
		delete Erased;
	}

	~DoubleLinkedList() {
		while (Head) pop_front();
	}

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << this->size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};
void main() {
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	DoubleLinkedList DLList;
	for (int i = 0; i < n; i++) {
		DLList.push_front(rand() % 100);
	}
}