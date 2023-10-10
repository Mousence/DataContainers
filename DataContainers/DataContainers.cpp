#include <iostream>
#include <ctime>
using namespace std;
using std::cout;
#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;	//объявление статической переменной
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) {
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
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator {
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp) {
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator(){
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	Iterator& operator++() {
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int) {
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const {
		return this->Temp == other.Temp ? 1 : 0;
	}
	bool operator!=(const Iterator& other)const {
		return this->Temp != other.Temp ? 1 : 0;
	}
	int operator*() {
		return Temp->Data;
	}
};

class ForwardList {
	Element* Head;
	unsigned int size;
public:
	const Iterator begin() const {
		return Head;
	}
	const Iterator end() const {
		return nullptr;
	}
	ForwardList() {
		this->Head = nullptr;
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList() {
		//initializer_list - это контейнер.
		//Контейнер - это объект, который организует хранение других объектов в памяти.
		//Как и у любого другого контейнера, у initializer_list есть методы begin() и end()
		//begin() - возвращает итератор на начало контейнера;
		//end()   - возвращает итератор на конец контейнера;

		for (int const* it = il.begin(); it != il.end(); it++) {
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) : ForwardList() {
		*this = other;
#ifdef DEBUG
		cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);
#ifdef DEBUG
		cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~ForwardList()
	{
		while (Head)pop_front();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
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
		if (Index <= 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data, Temp->pNext);
	}
	void erase(int index) {
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();
		if (index >= size)return;
		Element* Temp = Head;
		while (index-1) {
			if (Temp == nullptr)return;
			Temp = Temp->pNext;
			index--;
		}
		delete Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
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
	ForwardList& operator=(const ForwardList& other) {
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment:\t" << this << "<-" << &other << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) {
		if (this == &other) return *this;
		while (Head) pop_front();
		Head = other.Head;
		other.Head = nullptr;

		cout << "LMoveAssignment:\t" << this << "<-" << &other << endl;
		return *this;
	}
	/*ForwardList operator+(const ForwardList& other) const {
		ForwardList result = *this;
		Element* Temp = other.Head;

		while (Temp) {
			result.push_back(Temp->Data);
			Temp = Temp->pNext;
		}

		return result;
	}*/
	//					Methods:
	void reverse() {
		ForwardList reverse;
		while (Head) {
			reverse.push_front(Head->Data);
			this->pop_front();
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << this->size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};
ForwardList operator+(const ForwardList& left, const ForwardList& right) {
	ForwardList result = left;
	for (Iterator it = right.begin(); it != right.end(); ++it)
		result.push_back(*it);
	return result;
}
//#define BASE_CHECK
//#define INSERT_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define FORWARD_LIST_PERFORMANCE_TEST

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
	list.print();
	list.erase(3);
	list.print();

#ifdef INSERT_CHECK
		int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	erase(3);
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

	for (Iterator it = list.begin(); it != list.end(); ++it) {
		cout << *it << tab;
	}
#endif // RANGE_BASED_FOR_LIST
	
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		list.push_front(rand() % 100);
	}
	clock_t end = clock();

	cout << "Data loaded for " << double(end-start)/CLOCKS_PER_SEC << endl;
	cout << "Copying list..." << endl;
	start = clock();
	ForwardList list2 = list;
	end = clock();
	cout << "Data copyed for " << double(end - start) / CLOCKS_PER_SEC << endl;
}