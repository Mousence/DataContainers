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
	size_t size; //size_t - это unsigned int
	//Директива дает существующему типу данных новое имя:
	//typedef существующий_тип_данных новое_имя_этого_типа;
public:
	List() {
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List() {
		while (Head) pop_front();
		cout << "LDenstructor:\t" << this << endl;
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
	//               Deleting Elements:
	void pop_front() {
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail) {
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	//               Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab <<Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Общее количество элементов списка: " << size << endl;
	}
	void reverse_print()const {
	for(Element*Temp = Tail;Temp;Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Общее количество элементов списка: " << size << endl;
	}
};

int main() {
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++) {
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print(); 
	list.print();
}