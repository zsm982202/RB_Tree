#pragma once
#include "RB_Tree_Node.h"
#include "RB_Tree_Node.cpp"

template <class T>
class RB_Tree {
public:
	RB_Tree();
	RB_Tree(T val);
	void LeftRotate(RB_Tree_Node<T>* cur_node);
	void RightRotate(RB_Tree_Node<T>* cur_node);
	void InsertNode(T insert_val);
	void FixTree(RB_Tree_Node<T>* cur_node);
	bool DeleteNode(T delete_val);
	void EraseNode(RB_Tree_Node<T>* erase_node);
	void FixTreeDelete(RB_Tree_Node<T>* cur_node);
	void ShowTree();
	RB_Tree_Node<T>* FindSuccessorNode(RB_Tree_Node<T>* node);
private:
	RB_Tree_Node<T>* root_node;
	RB_Tree_Node<T>* del_node;
};