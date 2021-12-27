#include "HeaderTable.h"

HeaderTable::~HeaderTable() {
}


void HeaderTable::insertTable(char* item, int frequency) {
	string str(item);
	pair<int, string> i = make_pair(frequency, str);
	
	list<pair<int, string>>::iterator it = indexTable.begin();//Initialize the iterator front indexTable

	while (it != indexTable.end()) {//Repeat until the end of the indexTable
		if (!str.compare(it->second)) {//If the item is already in the header
			it->first += 1;
			return;
		}
		it++;//Move back 1 space
	}
	//If there is no same product
	if (indexTable.size() == 0) { indexTable.push_front(i); }//Insert before list if empty
	else { indexTable.push_back(i); }
	FPNode* empty = new FPNode;
	dataTable.insert({ str,empty });
}

int HeaderTable::find_frequency(string item){
	int frequency = 0;

	if (indexTable.size() == 0) { return 0; }//When the table is empty
	else {//When the elements in the table
		for (list<pair<int, string>>::iterator tt = indexTable.begin(); tt != indexTable.end(); tt++) {
			if (tt->second == item) { frequency = tt->first; break; }
		}
	}
	return frequency;
}
