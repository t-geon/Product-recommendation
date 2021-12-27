#pragma once
#include "FPNode.h"
#include <list>

class HeaderTable
{
private:
	list<pair<int, string> > indexTable;//Sort by frequency (frequency, product)
	map<string, FPNode*> dataTable;//Product and product connection (product, node of the same next product fptree)
public:
	HeaderTable() { }
	~HeaderTable();

	void insertTable(char* item, int frequency);//Regardless of the storage threshold

	//Obtaining an index, data, nodes
	list<pair<int, string>> getindexTable() { return indexTable; }
	map<string, FPNode*> getdataTable() { return dataTable; }
	FPNode* getNode(string item) { return dataTable.find(item)->second; }//Returns the starting node of the same item in data

	//Sort
	void descendingIndexTable() { indexTable.sort(greater<pair<int,string>>()); }
	void ascendingIndexTable() { indexTable.sort(); }

	int find_frequency(string item);
};


