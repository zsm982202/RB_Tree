#include "RB_Tree_Node.h"

template<class T>
RB_Tree_Node<T>::RB_Tree_Node(T val):value(val), color_tag(RED),
left_child(nullptr), right_child(nullptr), father(nullptr) {}