#include <iostream>
#include <ctime>
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
	void tree_print() const{
		return tree_print(0, this->depth()*8);
	}
	void depth_print(int depth)const {
		return depth_print(Root, depth);
	}
	void balance() {
		return balance(this->Root);
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
		//if (Root == nullptr)return 0;
		//if (depth(Root->pLeft) + 1 > depth(Root->pRight))return depth(Root->pLeft) + 1;
		//else return depth(Root->pRight) + 1;

		//return Root==nullptr ? 0 : depth(Root->pLeft) + 1 > depth(Root->pRight) ? depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
		if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;
	}
	void erase(int Data, Element*& Root) {
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data) {
			if (Root->pLeft == Root->pRight) {
				delete Root;
				Root = nullptr;
			}
			else {
				if (count(Root->pLeft) > count(Root->pRight)) {
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else {
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root) const {
		//if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const {
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		if (Root == nullptr)return 0;
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
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
	void depth_print(Element* Root, int depth, int width = 8) const {
		if (Root == nullptr)
		{
			cout.width(width * 2); cout << "";
			return;
		}
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data;
			return;
		}
		depth_print(Root->pLeft, depth - 1, width);
		cout.width(width); cout << "";
		depth_print(Root->pRight, depth - 1, width);
	}
	void tree_print( int depth, int width)const {
		if (depth == this->depth())return;
		depth_print(this->Root, depth, width);
		cout << endl;
		cout << endl;
		cout << endl;
		tree_print(depth + 1, width/2);
	}
	void balance(Element* Root) {
		if (Root == nullptr)return;
		if (abs(count(Root->pLeft) - count(Root->pRight) < 2))return;
		
	    if (count(Root->pLeft) > count(Root->pRight)) {
				if (Root->pRight == nullptr)Root->pRight = new Element(Root->Data);
				else insert(Root->Data, Root->pRight);
				Root->Data = maxValue(Root->pLeft);
				erase(maxValue(Root->pLeft), Root->pLeft);
			}
		else {
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Root->Data);
			else insert(Root->Data, Root->pLeft);
			Root->Data = minValue(Root->pRight);
			erase(minValue(Root->pRight), Root->pRight);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
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

template<typename T> void measure(const char msg[], T(Tree::* function)()const, const Tree& tree) {
	cout << msg;
	clock_t start = clock();
	T result = (tree.*function)();
	clock_t end = clock();
	cout << result << ", вычислено за " << double(end - start) / CLOCKS_PER_SEC << " секунд." << endl;
}

#define BASE_CHECK
//#define ERASE_CHECK
#define DEPTH_CHECK
int main() 
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	Tree tree = {89,55,34,21,13,8,5,3};
	//tree.clear();
	//tree.print(); cout << endl;
	measure("Минимальное значение в дереве : ", &Tree::minValue, tree);
	measure("Максимальное значение в дереве: ", &Tree::maxValue, tree);
	measure("Сумма элементов дерева: ", &Tree::sum, tree);
	measure("Количестов элементов дерева: ", &Tree::count, tree);
	measure("Среднее арифметическое элементов дерева: ", &Tree::avg, tree);
	measure("Глубина дерева: ", &Tree::depth, tree);
	//cout << "Введите глубину дерева: "; cin >> n;
	//tree.depth_print(n);
	tree.tree_print();
	tree.balance();
	tree.tree_print();
#endif // 

#ifdef ERASE_CHECK
	Tree tree = { 5,8,2,6,7,9,10,1,3 };
	tree.print();
	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print(); cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Количестов элементов дерева: " << tree.count() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.avg() << endl;
	cout << "Глубина дерева: " << tree.depth() << endl;
#endif
}