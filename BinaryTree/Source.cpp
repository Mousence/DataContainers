#include <iostream>
using namespace std;
#define tab "\t"

class Tree 
{
protected:
	class Element 
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight) {
			cout << "EConstructor: " << this << endl;
		}
		~Element() {
			cout << "EDestructor: " << this << endl;
		}
		friend class Tree;
		friend class EniqueTree;
	}*Root;
public:
	Element* get_Root() {
		return Root;
	}
	Tree() :Root(nullptr) {
		cout << "TConstructor: " << this << endl;
	}
	~Tree() {
		clear();
		cout << "TDestructor: " << this << endl;
	}

	void clear() {
		clear(Root);
		Root == nullptr;
	}

	void insert(int Data, Element* Root) {
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == 0)return;
		if (Data < Root->Data) {
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else {
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue() {
		//if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue() {
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		return Root->pRight == nullptr ? maxValue(Root->pRight) : Root->Data;
	}
	int Sum() {
		//if (Root==nullptr)return 0;
		//else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	int Count() {
		//if (Root == nullptr)return 0;
		//else return 1 + Count(Root->pLeft) + Count(Root->pRight);
		return Root ? 1 + Count(Root->pLeft) + Count(Root->pRight) : 0;
	}
	void print() {
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int depth(Element* Root) {
		if (Root == nullptr)return 0;
		
		return 1 + depth(Root->pLeft);
	}
	void erase(Element* Root, int Data) {
		if (Root == nullptr)return;
		erase(Root->pLeft, Data);
		erase(Root->pRight, Data);
		if (Root->Data == Data)clear(Root);
	}
	int minValue(Element* Root) {
		//if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) {
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		return Root->pRight == nullptr ? maxValue(Root->pRight) : Root->Data;
	}
	int Sum(Element* Root) {
		//if (Root==nullptr)return 0;
		//else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	int Count(Element* Root) {
		//if (Root == nullptr)return 0;
		//else return 1 + Count(Root->pLeft) + Count(Root->pRight);
		return Root ? 1 + Count(Root->pLeft) + Count(Root->pRight) : 0;
	}
	double AVG() {
		return (double)Sum(Root) / Count(Root);
	}
	void print(Element* Root) {
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class EniqueTree :public Tree 
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data) 
	{
		insert(Data, Root);
	}
};
int main() 
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	EniqueTree tree;
	for (int i = 0; i < n; i++) {
		tree.insert(rand() % 100);
	}
	tree.print(); cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Количестов элементов дерева: " << tree.Count() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.AVG() << endl;
	cout << tree.depth(tree.get_Root()) << endl;
	tree.erase(tree.get_Root(), 67);
}