#include "FPGrowth.h"


FPGrowth::~FPGrowth() {

}

//Functions that make the fptree
void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
	table->descendingIndexTable();//indextable descending order
	list<pair<int, string>> ind = table->getindexTable();//indextable copied to ind
	FPNode* cur = root;//After inserting a child, use cur to move to that child
	//It turns down from above the index table in order of size
	for (list<pair<int, string>>::iterator tt = ind.begin(); tt != ind.end()&& tt->first>=threshold; tt++) {
		for (list<string> ::iterator itemm = item_array.begin(); itemm != item_array.end(); itemm++) {
			string name(itemm->c_str());
			if (tt->second == name) {//If the node already exists
				if (cur->getChildrenNode(name)) {
					cur->getChildrenNode(name)->updateFrequency(1);//1 increase in frequency
				}
				else {//If there is no node
					FPNode* newnode = new FPNode;//Create a new node for insertion
					newnode->setParent(cur);//Put parent's cur
					newnode->updateFrequency(1);
					char q[100]; strcpy(q, name.c_str());
					newnode->setItem(q);
					cur->pushchildren(name, newnode);

					connectNode(table, name, newnode);
				}
				cur = cur->getChildrenNode(name);
				break;
			}
		}
	}
}

//A function that forms a relationship for each node
void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {
	map<string, FPNode*> dat = table->getdataTable();
	FPNode* daa = dat.find(item)->second;
	while (daa->getNext() != NULL) {
		daa = daa->getNext();
	}//Save the best place to end daa1 of the things associated with it.
	daa->setNext(node);
}

bool FPGrowth::contains_single_path(FPNode* pNode) {
	if (pNode->getChildren().size() == 0) return true;//No child
	else if (pNode->getChildren().size() > 1) return false;//1 or more children
	return contains_single_path(pNode->getChildren().begin()->second);//When there is 1 child, return the child value
}

//A function followed brought frequentpatterns in result.txt
map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {
	
	ifstream fi;
	char t[200];
	char* tn, * tm;
	fi.open("result.txt");

	if (!fi)
	{
		flog << "File Open Error" << endl;
	}//Output when file open fails


	//Reads from market.txt Add to headertable
	while (!fi.eof()) {
		fi.getline(t, 200);
		if (t[0] == 0) { continue; }//If the transactions can insert end
		tm = strtok_s(t, "\t", &tn);
		int b = stoi(tm);
		set<string> ss;
		while (tn[0] != 0) {
			tm = strtok_s(NULL, "\t", &tn);
			ss.insert(tm);
		}
		frequenctPatterns.insert({ ss,b });
	}

	return frequenctPatterns;
}

void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}

//Function to print index table
bool FPGrowth::printList() {
	table->descendingIndexTable();//Sort by Frequency Descending
	list<pair<int, string>> ind = table->getindexTable();

	if (ind.size() == 0) { return false; }//When the table is empty
	else {//When the elements in the table
		cout << "Item  Frequency" << endl;
		*fout<< "Item  Frequency" << endl;
		for (list<pair<int, string>>::iterator tt = ind.begin(); tt != ind.end(); tt++) {
			cout << tt->second << " " << tt->first << endl;
			*fout<< tt->second << " " << tt->first << endl;
		}
	}
	cout << "==============================" << endl;
	*fout<< "==============================" << endl;
	return true;
}

//Function to print fptree
bool FPGrowth::printTree() {
	
	list<pair<int, string>> ind = table->getindexTable();
	if (ind.size() == 0) {return false;}//If the tree is empty
	else {
		cout << "{StandardItem,Frequency} (Path_Item,Frequency)" << endl;
		*fout<< "{StandardItem,Frequency} (Path_Item,Frequency)" << endl;
		for (list<pair<int, string>>::iterator tt = ind.begin(); tt != ind.end(); tt++) {
			if (tt->first >= threshold) {//Only products that exceed the threshold
				string a = tt->second;//Product names stored in a
				FPNode* s = table->getdataTable().find(a)->second;
				FPNode* pa = new FPNode;
				cout << "{" << tt->second << "," << tt->first << "}" << endl;//Header table output node
				*fout<< "{" << tt->second << "," << tt->first << "}" << endl;
				while (s->getNext() != NULL && s->getNext()->getFrequency() != 0) {
					s = s->getNext();
					pa = s;
					while (pa->getFrequency() != 0) {
						cout << "(" << pa->getItem() << "," << pa->getFrequency() << ") ";
						*fout<< "(" << pa->getItem() << "," << pa->getFrequency() << ") ";
						pa = pa->getParent();
					}
					cout << endl;
					*fout << endl;
				}
			}
		}
		cout << "==========================" << endl;
		*fout<< "==========================" << endl;
	}
	return true;
}


void FPGrowth::saveFrequentPatterns() {

}

