#include <iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;	//объявление статической переменной
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) {
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element() {
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList {
	Element* Head;
public:
	ForwardList() {
		this->Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList() {
		//initializer_list - это контейнер.
		//Контейнер - это объект, который организует хранение других объектов в памяти.
		//Как и у любого другого контейнера, у initializer_list есть методы begin() и end()
		//begin() - возвращает итератор на начало контейнера;
		//end()   - возвращает итератор на конец контейнера;
	}
	ForwardList(const ForwardList& other) : Head(nullptr) {
		Element* otherTemp = other.Head;
		Element* Temp = nullptr;

		while (otherTemp) {
			if (!this->Head) {
				this->Head = new Element(otherTemp->Data);
				Temp = this->Head;
			}
			else {
				Temp->pNext = new Element(otherTemp->Data);
				Temp = Temp->pNext;
			}

			otherTemp = otherTemp->pNext;
		}
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) : Head(other.Head)
	{
		other.Head = nullptr;
		cout << "MoveConstructor:\t" << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data, Temp->pNext);
	}

	//					Removing elements:
	void pop_front() {
		Element* Erased = Head;	
		Head = Head->pNext;
		delete Erased;	
	}
	void pop_back() {
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//                  Operators:
	ForwardList& operator=(const ForwardList&& other) {
		if (this == &other)
		{
			return *this;
		}

		while (Head)pop_front();

		Element* otherTemp = other.Head;
		Element* thisTemp = nullptr;

		while (otherTemp) {
			if (!this->Head) {
				this->Head = new Element(otherTemp->Data);
				thisTemp = this->Head;
			}
			else {
				thisTemp->pNext = new Element(otherTemp->Data);
				thisTemp = thisTemp->pNext;
			}

			otherTemp = otherTemp->pNext;
		}
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) {
		if (this == &other) return *this;

		while (Head)
		{
			pop_front();
		}

		Head = other.Head;
		other.Head = nullptr;

		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << Element::count << endl;
	}
};

//#define BASE_CHECK
//#define INSERT_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	/*list.push_front(123);
	list.print();
	list.pop_front();
	list.pop_back();*/
	list.print();

#ifdef INSERT_CHECK
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif // INSERT_CHECK

#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	ForwardList list2 = list;
}