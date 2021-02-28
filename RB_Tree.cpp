#include "RB_Tree.h"
#include "RB_Tree_Node.h"
#include <iostream>
#include <queue>
using namespace std;

template<class T>
RB_Tree<T>::RB_Tree():root_node(nullptr) {}

template<class T>
RB_Tree<T>::RB_Tree(T val) {
	root_node = new RB_Tree_Node<T>(val);
	root_node->color_tag = BLACK;
}

/************************************************************************/
/* 函数功能：对当前节点进行左旋操作                                     */
// 入口参数：左旋的当前节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::LeftRotate(RB_Tree_Node<T>* cur_node) {
	RB_Tree_Node<T>* father_node = cur_node->father;
	RB_Tree_Node<T>* left_node = cur_node->left_child;
	RB_Tree_Node<T>* right_node = cur_node->right_child;
	RB_Tree_Node<T>* right_left_node = right_node->left_child;
	cur_node->right_child = right_left_node;
	if(right_left_node != nullptr)
		right_left_node->father = cur_node;
	right_node->left_child = cur_node;
	cur_node->father = right_node;
	right_node->father = father_node;
	if(right_node->father == nullptr)
		root_node = right_node;
	else {
		if(father_node->left_child == cur_node)
			father_node->left_child = right_node;
		else
			father_node->right_child = right_node;
	}
}

/************************************************************************/
/* 函数功能：对当前节点进行右旋操作                                     */
// 入口参数：右旋的当前节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::RightRotate(RB_Tree_Node<T>* cur_node) {
	RB_Tree_Node<T>* father_node = cur_node->father;
	RB_Tree_Node<T>* left_node = cur_node->left_child;
	RB_Tree_Node<T>* right_node = cur_node->right_child;
	RB_Tree_Node<T>* left_right_node = left_node->right_child;
	cur_node->left_child = left_right_node;
	if(left_right_node != nullptr)
		left_right_node->father = cur_node;
	left_node->right_child = cur_node;
	cur_node->father = left_node;
	left_node->father = father_node;
	if(left_node->father == nullptr)
		root_node = left_node;
	else {
		if(father_node->left_child == cur_node)
			father_node->left_child = left_node;
		else
			father_node->right_child = left_node;
	}
}

/************************************************************************/
/* 函数功能：向红黑树中插入一个节点                                     */
// 入口参数：插入的数据
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::InsertNode(T insert_val) {
	RB_Tree_Node<T>* temp_node = root_node;
	while(temp_node != nullptr) {
		if(insert_val < temp_node->value) {
			if(temp_node->left_child != nullptr)
				temp_node = temp_node->left_child;
			else {
				RB_Tree_Node<T>* insert_node = new RB_Tree_Node<T>(insert_val);
				temp_node->left_child = insert_node;
				insert_node->father = temp_node;
				FixTree(insert_node);
				break;
			}
		}
		else {
			if(temp_node->right_child != nullptr)
				temp_node = temp_node->right_child;
			else {
				RB_Tree_Node<T>* insert_node = new RB_Tree_Node<T>(insert_val);
				temp_node->right_child = insert_node;
				insert_node->father = temp_node;
				FixTree(insert_node);
				break;
			}
		}
	}
}

/************************************************************************/
/* 函数功能：插入节点后修整红黑树，保证满足性质                         */
// 入口参数：插入的当前节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::FixTree(RB_Tree_Node<T>* cur_node) {
	RB_Tree_Node<T>* father = cur_node->father;
	if(father == nullptr) {
		cur_node->color_tag = BLACK;
		return;
	}
	if(father->color_tag == BLACK)
		return;
	RB_Tree_Node<T>* grandpa = father->father;
	if(grandpa == nullptr)
		return;
	RB_Tree_Node<T>* uncle;
	if(grandpa->left_child == father)
		uncle = grandpa->right_child;
	else
		uncle = grandpa->left_child;
	if(uncle == nullptr || uncle->color_tag == BLACK) {
		if(father == grandpa->left_child) {
			if(cur_node == father->right_child)
				LeftRotate(father);
			//father->color_tag = BLACK;
			grandpa->left_child->color_tag = BLACK;
			grandpa->color_tag = RED;
			RightRotate(grandpa);
		} else {
			if(cur_node == father->left_child)
				RightRotate(father);
			//father->color_tag = BLACK;
			grandpa->right_child->color_tag = BLACK;
			grandpa->color_tag = RED;
			LeftRotate(grandpa);
		}
		return;
	}
	//uncle->color_tag == RED
	father->color_tag = BLACK;
	uncle->color_tag = BLACK;
	grandpa->color_tag = RED;
	FixTree(grandpa);
}

/************************************************************************/
/* 函数功能：从红黑树中搜寻要删除的数据节点                             */
// 入口参数：删除的数据
// 返回值：true表示删除成功 false表示删除失败
/************************************************************************/
template<class T>
bool RB_Tree<T>::DeleteNode(T delete_val) {
	bool found = false;
	RB_Tree_Node<T>* del_node = nullptr;
	RB_Tree_Node<T>* temp_node = root_node;
	while(temp_node != nullptr) {
		if(delete_val == temp_node->value) {
			del_node = temp_node;
			found = true;
		}
		if(delete_val < temp_node->value)
			temp_node = temp_node->left_child;
		else
			temp_node = temp_node->right_child;
	}
	if(!found)
		return false;

	//如果待删除结点有左右子树，则寻找其中序遍历后续结点
	if(del_node->left_child != nullptr && del_node->right_child != nullptr) {
		RB_Tree_Node<T>* successor_node = FindSuccessorNode(del_node);
		del_node->value = successor_node->value;
		del_node = successor_node;
	}
	//如果待删除结点是红的，那它一定是叶子结点(除去NIL)
	if(del_node->color_tag == RED) {
		if(del_node->left_child != nullptr || del_node->right_child != nullptr)
			throw("the red node is not balanced.");
		EraseNode(del_node);
	} else {
		//待删除结点是黑的
		if(del_node->left_child != nullptr && del_node->right_child != nullptr)
			throw("the black node should not have two children.");
		//待删除结点左子树是红的
		if(del_node->left_child != nullptr) {
			if(del_node->left_child->color_tag == BLACK)
				throw("the black node is not balanced.");
			if(del_node->left_child->left_child != nullptr || del_node->left_child->right_child != nullptr)
				throw("the black node is not balanced.");
			del_node->value = del_node->left_child->value;
			EraseNode(del_node->left_child);
		} else if(del_node->right_child != nullptr) {
			//待删除结点右子树是红的
			if(del_node->right_child->color_tag == BLACK)
				throw("the black node is not balanced.");
			if(del_node->right_child->left_child != nullptr || del_node->right_child->right_child != nullptr)
				throw("the black node is not balanced.");
			del_node->value = del_node->right_child->value;
			EraseNode(del_node->right_child);
		} else {
			//待删除结点是黑的叶子结点
			FixTreeDelete(del_node);
			EraseNode(del_node);
		}
			
	}
	

	return true;
}

/************************************************************************/
/* 函数功能：清除该节点相关的所有信息                                   */
// 入口参数：当前节点
// 返回值：无
/************************************************************************/
template<class T>
void RB_Tree<T>::EraseNode(RB_Tree_Node<T>* erase_node) {
	if(erase_node->father != nullptr) {
		if(erase_node == erase_node->father->left_child)
			erase_node->father->left_child = nullptr;
		else
			erase_node->father->right_child = nullptr;
	}
	erase_node->father = nullptr;
	erase_node->left_child = nullptr;
	erase_node->right_child = nullptr;
	delete erase_node;
}

/************************************************************************/
/* 函数功能：清除该节点相关的所有信息                                   */
// 入口参数：当前节点
// 返回值：无
/************************************************************************/
template<class T>
void RB_Tree<T>::FixTreeDelete(RB_Tree_Node<T>* cur_node) {
	if(cur_node == root_node)
		return;
	//该结点是黑的
	RB_Tree_Node<T>* father = cur_node->father;
	RB_Tree_Node<T>* brother;
	if(cur_node == father->left_child) {
		brother = father->right_child;
		if(brother->color_tag == RED) {
			father->color_tag = RED;
			brother->color_tag = BLACK;
			LeftRotate(father);
			father = cur_node->father;
			brother = father->right_child;
		}
		if(brother->right_child == nullptr && brother->left_child != nullptr) {
			if(brother->right_child != nullptr)
				throw("brother->right should be null.");
			if(brother->left_child->left_child != nullptr || brother->left_child->right_child != nullptr)
				throw("brother->left should be a leaf.");
			if(brother->left_child->color_tag == BLACK)
				throw("father is not balanced.");
			brother->left_child->color_tag = BLACK;
			brother->color_tag = RED;
			RightRotate(brother);
			brother = father->right_child;
			brother->color_tag = father->color_tag;
			brother->right_child->color_tag = BLACK;
			father->color_tag = BLACK;
			LeftRotate(father);
		} else if(brother->right_child != nullptr) {
			brother->color_tag = father->color_tag;
			brother->right_child->color_tag = BLACK;
			father->color_tag = BLACK;
			LeftRotate(father);
		} else {
			//brother是叶子结点
			if(father->color_tag == RED) {
				father->color_tag = BLACK;
				brother->color_tag = RED;
			} else {
				FixTreeDelete(father);
			}
		}
	} else {
		brother = father->left_child;
		if(brother->color_tag == RED) {
			father->color_tag = RED;
			brother->color_tag = BLACK;
			RightRotate(father);
			father = cur_node->father;
			brother = father->left_child;
		}
		if(brother->left_child == nullptr && brother->right_child != nullptr) {
			if(brother->left_child != nullptr)
				throw("brother->left should be null.");
			if(brother->right_child->left_child != nullptr || brother->right_child->right_child != nullptr)
				throw("brother->right should be a leaf.");
			if(brother->right_child->color_tag == BLACK)
				throw("father is not balanced.");
			brother->right_child->color_tag = BLACK;
			brother->color_tag = RED;
			LeftRotate(brother);
			brother = father->left_child;
			brother->color_tag = father->color_tag;
			brother->left_child->color_tag = BLACK;
			father->color_tag = BLACK;
			RightRotate(father);
		} else if(brother->left_child != nullptr) {
			brother->color_tag = father->color_tag;
			brother->left_child->color_tag = BLACK;
			father->color_tag = BLACK;
			RightRotate(father);
		} else {
			//brother是叶子结点
			if(father->color_tag == RED) {
				father->color_tag = BLACK;
				brother->color_tag = RED;
			} else {
				FixTreeDelete(father);
			}
		}
	}
}

/************************************************************************/
/* 函数功能：找寻当前节点的中序后继节点                                 */
// 入口参数：当前节点
// 返回值：当前节点的中序后继节点
/************************************************************************/
template<class T>
RB_Tree_Node<T>* RB_Tree<T>::FindSuccessorNode(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* temp_node = node->right_child;
	while(temp_node->left_child != nullptr)
		temp_node = temp_node->left_child;
	return temp_node;
}

template<class T>
void RB_Tree<T>::ShowTree() {
	if(root_node == nullptr)
		return;
	queue<RB_Tree_Node<T>*> q;
	q.push(root_node);
	while(!q.empty()) {
		RB_Tree_Node<T>* temp = q.front();
		q.pop();
		if(temp->left_child) {
			cout << temp->value;
			if(temp->color_tag == RED)
				cout << "(red) left:";
			else
				cout << "(black) left:";
			cout << temp->left_child->value;
			if(temp->left_child->color_tag == RED)
				cout << "(red)" << endl;
			else
				cout << "(black)" << endl;
			q.push(temp->left_child);
		}
		if(temp->right_child) {
			cout << temp->value;
			if(temp->color_tag == RED)
				cout << "(red) right:";
			else
				cout << "(black) right:";
			cout << temp->right_child->value;
			if(temp->right_child->color_tag == RED)
				cout << "(red)" << endl;
			else
				cout << "(black)" << endl;
			q.push(temp->right_child);
		}
	}
}