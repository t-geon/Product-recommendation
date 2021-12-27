#include "BpTree.h"

bool BpTree::Insert(int key, set<string> set) {
	if (set.size() < 2) {
		return false;
	}
	FrequentPatternNode* fnode = new FrequentPatternNode;
	if (root == NULL) {
		BpTreeDataNode* datanode = new BpTreeDataNode;
		fnode->InsertList(set);
		datanode->insertDataMap(key, fnode);//Data Node Initialization
		root = datanode;
	}
	else if(root->getMostLeftChild()==NULL){//There is still root (the place to put data in the root)
		if (root->getDataMap()->find(key) == root->getDataMap()->end()) {//If you do not have the same frequency node
			fnode->InsertList(set);
			root->insertDataMap(key, fnode);
			
			//split
			if (root->getDataMap()->size() == order) {splitDataNode(root);}

		}
		else {//If there are nodes with the same frequency
			root->getDataMap()->find(key)->second->InsertList(set);
		}
	}
	else {//There is root.
		BpTreeNode* temp = root;
		while (temp->getMostLeftChild() != NULL) {temp = temp->getMostLeftChild();}//Go to datanode
		while (temp->getNext() != NULL) { temp = temp->getNext(); }//move to the end of datanode
		
		//When you already have a node, such as frequency
		for (map <int, FrequentPatternNode*>::iterator aa = temp->getDataMap()->begin(); aa != temp->getDataMap()->end(); aa++) {
			if (aa->first == key) {
				temp->getDataMap()->find(key)->second->InsertList(set);
				return true;
			}
		}
		fnode->InsertList(set);
		temp->insertDataMap(key, fnode);

		if (temp->getDataMap()->size() == order) {splitDataNode(temp);}
	}

	return true;
}

//Using a frequency of searches for data node.
BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;
	if (pCur == NULL) { return NULL; }
	while (pCur->getMostLeftChild() != NULL) { pCur = pCur->getMostLeftChild(); }//Go to datanode
	while (pCur->getDataMap()->begin()->first<n) {
		pCur = pCur->getNext();
		if (pCur == NULL) { return NULL; }
	}
	return pCur;
}

//datanode split
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	BpTreeDataNode* p = new BpTreeDataNode;
	BpTreeDataNode* q = new BpTreeDataNode;
	BpTreeIndexNode* one = new BpTreeIndexNode;
	BpTreeNode* newroot = new BpTreeNode;
	int par=0;
	int ord = order % 2;
	if (pDataNode == root) {//The first split root is caused by
		map <int, FrequentPatternNode*>::iterator it=root->getDataMap()->begin();
		//Initialize new nodes
		for (int i = 1; i <= order; i++) {
			if(i< ((order - ord) / 2) + 1){p->insertDataMap(it->first, it->second);}
			else{
				if (i == ((order - ord) / 2) + 1) { par = it->first;}
				q->insertDataMap(it->first, it->second);
			}
			++it;
		}
		one->setMostLeftChild(p);//Connect p to the leftmost element
		one->insertIndexMap(par, q);//Frequency initialized and connected to the node q
		root = one;//root change
		//It makes the relationship of the new node.
		p->setNext(q); p->setParent(root);
		q->setPrev(p); q->setParent(root);
		return;
	}
	else {
		map <int, FrequentPatternNode*>::iterator it = pDataNode->getDataMap()->begin();
		//Initialize new nodes
		for (int i = 1; i <= order; i++) {
			if (i < ((order - ord) / 2) + 1) { p->insertDataMap(it->first, it->second); }
			else {
				if (i == ((order - ord) / 2) + 1) { par = it->first;}
				q->insertDataMap(it->first, it->second);
			}
			++it;
		}

		p->setPrev(pDataNode->getPrev());//prev initialization of p
		pDataNode->getPrev()->setNext(p);//The next of the previous one back to p

		//It makes the relationship of the new node.
		newroot = pDataNode->getParent();
		newroot->insertIndexMap(par, q);
		p->setNext(q); p->setParent(newroot);
		q->setPrev(p); q->setParent(newroot);
		splitIndexNode(newroot);
		return;
	}
}

//indexnode split
void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() != order) { return; }
	BpTreeNode* p = new BpTreeIndexNode;
	BpTreeNode* q = new BpTreeIndexNode;
	BpTreeNode* one = new BpTreeIndexNode;
	int par=0;
	int ord = order % 2;
	if (pIndexNode == root) {//Root split
		map <int, BpTreeNode*>::iterator it = pIndexNode->getIndexMap()->begin();
		for (int i = 1; i <= order; i++) {
			if (i < ((order - ord) / 2) + 1) {
				it->second->setParent(p);//Set the child's parents of what is currently stored as p
				p->insertIndexMap(it->first, it->second);//p's next and data initialization
			}
			else if (i == ((order-ord)/2)+1) {
				par = it->first;
				it->second->setParent(q);//Set the child's parents of what is currently stored as q
				one->insertIndexMap(it->first, it->second);
			}
			else{
				it->second->setParent(q);//Set the child's parents of what is currently stored as q
				q->insertIndexMap(it->first, it->second);//q's next and data initialization
			}
			++it;
		}
		//p,q left,initialize, leftmost parent set
		p->setMostLeftChild(pIndexNode->getMostLeftChild());
		pIndexNode->getMostLeftChild()->setParent(p);
		q->setMostLeftChild(one->getIndexMap()->begin()->second);

		//Initialize rising elements (element, next, left)
		one->deleteMap(par);
		one->insertIndexMap(par, q);
		one->setMostLeftChild(p);
		root = one;

		p->setParent(root);
		q->setParent(root);
		return;
	}
	else {//Non-root split
		map <int, BpTreeNode*>::iterator it = pIndexNode->getIndexMap()->begin();
		for (int i = 1; i <= order; i++) {
			if (i < ((order - ord) / 2) + 1) {
				it->second->setParent(p);//Set the child's parents of what is currently stored as p
				p->insertIndexMap(it->first, it->second);//p's next and data initialization
			}
			else if (i == ((order - ord) / 2) + 1) { 
				par = it->first;
				it->second->setParent(q);//Set the child's parents of what is currently stored as q
				one->insertIndexMap(it->first, it->second);
			}
			else {
				it->second->setParent(q);//Set the child's parents of what is currently stored as q
				q->insertIndexMap(it->first, it->second);//q's next and data initialization
			}
			++it;
		}

		//p,q left,initialize, leftmost parent set
		p->setMostLeftChild(pIndexNode->getMostLeftChild());
		pIndexNode->getMostLeftChild()->setParent(p);
		q->setMostLeftChild(one->getIndexMap()->begin()->second);

		//Initialize rising elements (element, next, left)
		one->deleteMap(par);
		one = pIndexNode->getParent();
		one->insertIndexMap(par, q);

		p->setParent(one);
		q->setParent(one);
		splitIndexNode(one);
		return;
	}
}

//Check the element number of datanode if not full
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

//Check the element number of indexnode if not full
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

//Set output above the standard confidence
bool BpTree::printConfidence(string item, double item_frequency, int min_frequency)
{
	if (root == NULL) { return false; }
	BpTreeNode* data = searchDataNode(min_frequency);//Datanode first delivery is at least the frequency data
	if (data == NULL) { return false; }
	cout << "StandardItem  SubSet  Frequency  Confidence" << endl;
	*fout<< "StandardItem  SubSet  Frequency  Confidence" << endl;

	while (1) {
		string a(item);
		map <int, FrequentPatternNode*>::iterator it = data->getDataMap()->begin();
		for (; it != data->getDataMap()->end(); it++) {//Turn repeatedly to set.
			multimap<int, set<string>> qq = it->second->getList();
			for (multimap<int, set<string>>::iterator sit = qq.begin(); sit != qq.end(); sit++) {
				if (sit->second.find(a) != sit->second.end()) {
					cout << a << " -> ";
					*fout << a << " -> ";
					printFrequentPatterns(sit->second, a);
					cout << " " << it->first << " ";
					*fout << " " << it->first << " ";
					double confidence = (it->first) / double(item_frequency);
					cout << fixed;
					*fout << fixed;
					cout.precision(2);
					fout->precision(2);
					cout << confidence << endl;
					*fout << confidence << endl;
				}
			}
		}
		if (data->getNext() != NULL) { data = data->getNext(); }
		else { break; }
	}

	cout << "=========================" << endl;
	*fout<< "=========================" << endl;
	return true;
}

//Set output that exceeds the minimum frequency
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	if (root == NULL) { return false; }
	BpTreeNode* data = searchDataNode(min_frequency);//Deliver the first datanode that is more than the minimum frequency to data
	if (data == NULL) { return false; }
	cout << "StandardItem  SubSet  Frequency" << endl;
	*fout<< "StandardItem  SubSet  Frequency" << endl;

	while (1) {
		string a(item);
		map <int, FrequentPatternNode*>::iterator it = data->getDataMap()->begin();
		for (; it != data->getDataMap()->end(); it++) {//Turn repeatedly to set.
			multimap<int, set<string>> qq = it->second->getList();
			for (multimap<int, set<string>>::iterator sit = qq.begin(); sit != qq.end(); sit++) {
				if (sit->second.find(a) != sit->second.end()) {
					cout << a << " -> ";
					*fout<< a << " -> ";
					printFrequentPatterns(sit->second, a);
					cout << " " << it->first << endl;
					*fout<< " " << it->first << endl;
				}
			}
		}
		if (data->getNext() != NULL) { data = data->getNext(); }
		else { break; }
	}
	cout << "==========================" << endl;
	*fout<< "==========================" << endl;
	return true;
}

//set output in range
bool BpTree::printRange(string item, int min, int max) {

	if (root== NULL) { return false; }
	BpTreeNode* data = searchDataNode(min);//Deliver the first datanode that is more than the minimum frequency to data
	if (data == NULL) { return false; }
	cout << "StandardItem  SubSet  Frequency" << endl;
	*fout<< "StandardItem  SubSet  Frequency" << endl;
	while (1) {
		string a(item);
		map <int, FrequentPatternNode*>::iterator it = data->getDataMap()->begin();
		for (; it != data->getDataMap()->end(); it++) {//Turn repeatedly to set.
			if (it->first > max) { cout << "==============================" << endl;*fout<< "==============================" << endl; return true; }
			multimap<int, set<string>> qq = it->second->getList();
			for (multimap<int, set<string>>::iterator sit = qq.begin(); sit != qq.end(); sit++) {
				if (sit->second.find(a) != sit->second.end()) {
					cout << a << " -> ";
					*fout<< a << " -> ";
					printFrequentPatterns(sit->second, a);
					cout << " " << it->first << endl;
					*fout<< " " << it->first << endl;
				}
			}
		}
		if (data->getNext() != NULL) { data = data->getNext(); }
		else { break; }
	}
	cout << "==============================" << endl;
	*fout<< "==============================" << endl;
	return true;
}


void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item) {
	*fout << "{";
	cout << "{";
	set<string> curPattern = pFrequentPattern;
	curPattern.erase(item);
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) {
		string temp = *it++;
		if (temp != item) { *fout << temp; cout << temp; }
		if (it == curPattern.end()) {
			*fout << "} ";
			cout << "}";
			break;
		}
		*fout << ", ";
		cout << ", ";
	}
}
