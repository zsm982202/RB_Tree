#include "RB_Tree.h"
#include "RB_Tree.cpp"

int main() {
	/*RB_Tree<double>* m_RB_Tree = new RB_Tree<double>(1.0);
	for(int i = 2; i < 10; i++) {
		double a = i;
		m_RB_Tree->InsertNode(a);
	}*/
	RB_Tree<int>* m_RB_Tree = new RB_Tree<int>(10);
	m_RB_Tree->InsertNode(4);
	m_RB_Tree->InsertNode(2);
	m_RB_Tree->InsertNode(1);
	m_RB_Tree->InsertNode(0);
	m_RB_Tree->InsertNode(5);
	m_RB_Tree->InsertNode(8);
	m_RB_Tree->InsertNode(7);
	m_RB_Tree->InsertNode(9);
	m_RB_Tree->ShowTree();

	cout << endl;
	m_RB_Tree->DeleteNode(7);
	m_RB_Tree->DeleteNode(10);
	m_RB_Tree->DeleteNode(4);
	m_RB_Tree->DeleteNode(8);
	m_RB_Tree->DeleteNode(9);
	m_RB_Tree->ShowTree();

	return 0;
}