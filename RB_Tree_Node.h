#pragma once

enum color { RED, BLACK };

template<class T>
class RB_Tree_Node {
public:
	RB_Tree_Node(T val);
	T value;
	RB_Tree_Node* left_child;
	RB_Tree_Node* right_child;
	RB_Tree_Node* father;
	color color_tag;
};