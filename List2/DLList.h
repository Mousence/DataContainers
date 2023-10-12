#pragma once
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
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
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
	class ConstIterator :public ConstBaseIterator {
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
	class ConstReverseIterator : public ConstBaseIterator {
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