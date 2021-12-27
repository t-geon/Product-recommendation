#include "FPNode.h"
FPNode::FPNode()	//constructor
{
	parent = NULL;
	next = NULL;
	item = new char[40]; memset(item, 0, 40);//This item is initialized to zero point as where 40 bytes
	frequency = 0;
}


FPNode::~FPNode()//destructor
{
}

//Iterators are visited in key value order.
FPNode* FPNode::getChildrenNode(string item) {
	map<string, FPNode*>::iterator it = children.find(item);//return the node found in it
	if (it == children.end()) return NULL;//it == children.end () will not seek value
	FPNode* findNode = it->second;//If you are looking to save present value finNode
	return findNode;
}

