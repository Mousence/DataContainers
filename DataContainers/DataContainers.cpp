#include <iostream>

using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	//Forward - �����������, ����������������
	Element* Head;
public:
	ForwardList() {
		//����������� �� ��������� ������� ������ ������.
		this->Head = nullptr;	//���� ������ ����, ��� ������ ��������� �� 0.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList() {
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data) {
		//1) ������� ������� ��� ������������ ��������:
		Element* New = new Element(Data);
		//2) �������������� ������� � ������:
		New->pNext = Head;
		//3) ������ ����� ������� �������� ��������� ��������� ������:
		Head = New;
	}
	void push_back(int Data) {
		if (Head == nullptr)return push_front(Data);

		//1) ������� ����� �������:
		Element* New = new Element(Data);

		//2) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		// ������ 'Temp' ��������� �� ��������� �������.

		//3) ��������� ����� ������� � ����� ������:
		Temp->pNext = New;
	}

	//					Methods:
	void print()const {
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
	}
	void pop_front() {
		Element* Temp = Head;
		Element* New = new Element(0);
		New->pNext = Head;
		Head = New;

		while (Temp->pNext) {
			*New = *Temp;
			New = New->pNext;
		}

		delete Temp;
	}
	void pop_back() {
		Element* Temp = Head;
		while (Temp->pNext) {
			Temp = Temp->pNext;
		}
		delete Temp;
	}
	void insert(int Data, int index) {
		Element* New = new Element(Data);
		Element* Temp = Head;

		while (index) {
			Temp = Temp->pNext;
			index--;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}
	void erase(int index) {
		Element* Temp = Head;

		while (index) {
			Temp = Temp->pNext;
			index--;
		}
		Element* New = new Element(*Temp);
		Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		delete Temp;
		Temp = New->pNext;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++) {
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.erase(2);
	list.print();
}