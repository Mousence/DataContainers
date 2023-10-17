#include <iostream>
using namespace std;
using std::cout;
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
#ifdef DEBUG
			cout << "EConstructor: " << this << endl;
#endif // DEBUG
		}
		~Element() {
#ifdef DEBUG
			cout << "EDestructor: " << this << endl;
#endif // DEBUG
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
	Tree(const std::initializer_list<int>& il) :Tree() {
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree() {
		clear();
		cout << "TDestructor: " << this << endl;
	}

	void erase(int Data) {
		return erase(Data,Root);
	}

	void insert(int Data) {
		return insert(Data, Root);
	}

	void clear() const {
		clear(Root);
		Root == nullptr;
	}
	int minValue() const {
		//if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		return minValue(Root);
	}
	int maxValue() const {
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		return maxValue(Root);
	}
	int sum() const {
		//if (Root==nullptr)return 0;
		//else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);
		return sum(Root);
	}
	int count() const {
		//if (Root == nullptr)return 0;
		//else return 1 + Count(Root->pLeft) + Count(Root->pRight);
		return count(Root);
	}
	double avg() const {
		return (double)sum(Root) / count(Root);
	}
	int depth() const{
		return depth(Root);
	}
	void print() const {
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

private:
	void insert(int Data, Element* Root) {
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data) {
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else {
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void clear(Element* Root) const {
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int depth(Element* Root) const{
		if (Root == nullptr)return 0;
		
		return 1 + depth(Root->pLeft);
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root) const {
		//if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		return Root == nullptr ? 0 : 1 ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root) const {
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		return Root == nullptr ? 0 : 1 ? maxValue(Root->pRight): Root->Data;
	}
	int sum(Element* Root) const {
		//if (Root==nullptr)return 0;
		//else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int count(Element* Root) const {
		//if (Root == nullptr)return 0;
		//else return 1 + Count(Root->pLeft) + Count(Root->pRight);
		return Root ? 1 + count(Root->pLeft) + count(Root->pRight) : 0;
	}
	void print(Element* Root) const {
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

#define BASE_CHECK
//#define ERASE_CHECK

int main() 
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++) {
		tree.insert(rand() % 10);
	}
	//tree.clear();
	tree.print(); cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Количестов элементов дерева: " << tree.count() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.avg() << endl;
#endif // 

#ifdef ERASE_CHECK
	Tree tree = { 5,8,2,6,7,9,10,1,3 };
	tree.print();
#endif
	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print(); cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Количестов элементов дерева: " << tree.count() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.avg() << endl;
}