#pragma once
#pragma warning(disable:4996)

#include <cstring>
#include <map>
#include <cmath>

#include <string>//비주얼 스튜디오에서만 사용

using namespace std;
class FPNode
{
private:
	char* item;
	int frequency;
	FPNode* parent;//Parent pointing node
	FPNode* next;//Node pointing to the same product
	map<string, FPNode*> children;
public:
	FPNode();
	~FPNode();

	//Save parents
	void setParent(FPNode* node) { this->parent = node; }

	void setNext(FPNode* node) { next = node; }

	//insert child
	void pushchildren(string item, FPNode* node) { children.insert(map<string, FPNode*>::value_type(item, node)); }

	//The name of the item save
	void setItem(char* item) { strcpy(this->item, item); }

	//Additional frequency
	void updateFrequency(int frequency) { this->frequency += frequency; }

	//Return each element
	char* getItem() { return item; }
	int getFrequency() { return frequency; }
	FPNode* getParent() { return parent; }
	FPNode* getNext() { return next; }

	//Find and return by looking for child name
	FPNode* getChildrenNode(string item);
	map<string, FPNode*> getChildren() { return children; }
};





