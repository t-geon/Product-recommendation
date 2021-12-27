#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {
		delete root;
	};
	/* essential */
	bool		Insert(int key, set<string> set);
	bool		excessDataNode(BpTreeNode* pDataNode);//This element is equal to the number and order-1 data node split haeyaham
	bool		excessIndexNode(BpTreeNode* pIndexNode);//If the number of elements and order-1 are the same in the index node, it should be split.
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(int n);//Find datanode with frequency.

	void	printFrequentPatterns(set<string> pFrequentPattern, string item);
	bool	printFrequency(string item, int min_frequency);
	bool	printConfidence(string item, double item_frequency, int min_frequency);
	bool 	printRange(string item, int min, int max);

};

#endif
