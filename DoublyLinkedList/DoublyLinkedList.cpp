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
		if (Head == nullptr)return push_front(Data);
		Tail->pNext = new Element(Data);
		Tail->Data = Data;
	}
	void pop_front() {
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_back() {
		Element* Erased = Tail;
		Tail->pPrev = Tail;
		delete Erased;
	}

	~DoubleLinkedList() {
		while (Head) pop_front();
	}
};
void main() {
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	DoubleLinkedList DLList;
	for (int i = 0; i < n; i++) {
		DLList.push_front(rand() % 100);
	}
}