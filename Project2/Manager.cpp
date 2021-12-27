#include "Manager.h"
#include<cctype>

void Manager::run(const char* command)
{
	fin.open(command);
    flog.open("log.txt", ios::app);
	if (!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
    char cmd[32];
	while (!fin.eof())
	{
        fin.getline(cmd, 32);//Read 1 line of command.txt
        if (!strcmp(cmd, "")) { continue; }//Code to repeat the number of lines
        char* tmp,*tmm;
        strtok_s(cmd, " ", &tmp);//Saved in the character cmd in front of the "" standard, and the remaining characters in the address of tmp
        if (!strcmp(cmd, "LOAD"))
        {
            cout << "========LOAD========" << endl;
            flog<< "========LOAD========" << endl;
            if (LOAD()) { printSuccessCode(); }//If successful, print success
            else { printErrorCode(100); }//If it fails error output
            cout << endl<<endl;
            flog<< endl << endl;
        }

        else if (!strcmp(cmd, "BTLOAD")) {
            cout << "========BTLOAD========" << endl;
            flog << "========BTLOAD========" << endl;
            if (BTLOAD()) { printSuccessCode(); }//If successful, print success
            else { printErrorCode(200); }//If it fails error output
            cout << endl << endl;
            flog << endl << endl;
        }

        else if (!strcmp(cmd, "PRINT_ITEMLIST")) {
            cout << "========PRINT_ITEMLIST========" << endl;
            flog << "========PRINT_ITEMLIST========" << endl;
            if (!PRINT_ITEMLIST()){ printErrorCode(300); }//If it fails error output
            cout << endl << endl;
            flog << endl << endl;
        }

        else if (!strcmp(cmd, "PRINT_FPTREE")) {
            cout << "========PRINT_FPTREE========" << endl;
            flog << "========PRINT_FPTREE========" << endl;
            if (!PRINT_FPTREE()){ printErrorCode(400); }//If it fails error output
            cout << endl << endl;
            flog << endl << endl;
        }

        //Error code output when there are few or many parameters
        else if (!strcmp(cmd, "PRINT_MIN")) {
            cout << "========PRINT_MIN========" << endl;
            flog<< "========PRINT_MIN========" << endl;
            tmm = strtok_s(tmp, " ", &tmp);
            char* t1 = tmm;
            if (tmp[0] == NULL) { printErrorCode(500); cout << endl << endl;flog << endl << endl; continue; }
            tmm = strtok_s(tmp, " ", &tmp);
            char* t2 = tmm;
            if (tmp[0] != NULL) { printErrorCode(500); cout << endl << endl; flog << endl << endl; continue; }
            if (!PRINT_MIN(t1, stoi(t2))){ printErrorCode(500); }//If it fails error output
            cout << endl << endl;
            flog << endl << endl;
        }

        //Error code output when there are few or many parameters
        else if (!strcmp(cmd, "PRINT_CONFIDENCE")) {
            cout << "========PRINT_CONFIDENCE========" << endl;
            flog<< "========PRINT_CONFIDENCE========" << endl;
            tmm = strtok_s(tmp, " ", &tmp);
            char* t1 = tmm;
            if (tmp[0] == NULL) { printErrorCode(600); cout << endl << endl;flog << endl << endl; continue; }
            tmm = strtok_s(tmp, " ", &tmp);
            char* t2 = tmm;
            if (tmp[0] != NULL) { printErrorCode(600); cout << endl << endl; flog << endl << endl; continue; }
            if(!PRINT_CONFIDENCE(t1, stod(t2))){ printErrorCode(600); }//If it fails error output
            cout << endl << endl;
            flog << endl << endl;
        }

        //Error code output when there are few or many parameters
        else if (!strcmp(cmd, "PRINT_RANGE")) {
            cout << "========PRINT_RANGE========" << endl;
            flog<< "========PRINT_RANGE========" << endl;
            tmm = strtok_s(tmp, " ", &tmp);
            char* t1 = tmm;
            if (tmp[0] == NULL|| isdigit(t1[0])) { printErrorCode(700); cout << endl << endl; flog << endl << endl; continue; }
            tmm = strtok_s(tmp, " ", &tmp);
            char* t2 = tmm;
            if (tmp[0] == NULL || !isdigit(t2[0])) { printErrorCode(700); cout << endl << endl; flog << endl << endl; continue; }
            tmm = strtok_s(tmp, " ", &tmp);
            if(tmp[0]!=NULL){ printErrorCode(700); cout << endl << endl; flog << endl << endl; continue; }
            char* t3 = tmm;
            if(!PRINT_RANGE(t1, stoi(t2),stoi(t3)) || !isdigit(t3[0])){ printErrorCode(700); }//If it fails error output
            cout << endl << endl;
            flog << endl << endl;
        }

        else if (!strcmp(cmd, "SAVE")) {
            cout << "가산점 부분은 구현하지 않았습니다" << endl;
            flog<< "가산점 부분은 구현하지 않았습니다" << endl;
            cout << endl << endl;
            flog << endl << endl;
        }

        else if (!strcmp(cmd, "EXIT"))
        {
            cout << "========EXIT========" << endl;
            flog<< "========EXIT========" << endl;
            printSuccessCode();//If successful, print success
            cout << endl << endl;
            flog << endl << endl;
            break;
        }

        else
        {
            cout << "========== ERROR ==========" << endl;
            cout << "Command Error" << endl;
            cout << "===========================" << endl << endl;

            flog << "========== ERROR ==========" << endl;
            flog << "Command Error" << endl;
            flog << "===========================" << endl << endl;
        }
	}
    fin.close();
    return;
}

//Import transaction details from market.txt and create fptree and headertable
bool Manager::LOAD()
{
    
    ifstream f;
    if (fpgrowth->getHeaderTable()->getindexTable().size()!= 0) {return false; }
    char t[200];
    char* tn, * tm;
    f.open("market.txt");

    if (!f)
    {
        flog << "File Open Error" << endl;
        return false;
    }//Output when file open fails


    //Reads from market.txt Add to headertable
    while (!f.eof()) {
        f.getline(t, 200);
        if (t[0] == 0) { continue; }//End if there is no transaction to insert
        tm = strtok_s(t, "\t", &tn);
        fpgrowth->createTable(tm, 1);
        while (tn[0] != 0) {
            tm = strtok_s(NULL, "\t", &tn);
            fpgrowth->createTable(tm, 1);
        }
    }

    //Creating fp tree
    f.close();
    f.open("market.txt");

    if (!f)
    {
        flog << "File Open Error" << endl;
        return false;
    }//Output when file open fails

    //Save the list by one line transactions
    while (!f.eof()) {
        f.getline(t, 200);
        if (t[0] == 0) { continue; }
        tm = strtok_s(t, "\t", &tn);
        list<string> item_array;
        item_array.push_back(t);
        
        while (tn[0] != 0) {
            tm = strtok_s(NULL, "\t", &tn);
            item_array.push_back(tm);
        }
        //Insertion function (receive a list and do it if it is above the threshold.
        fpgrowth->createFPtree(fpgrowth->getTree(), fpgrowth->getHeaderTable(), item_array, 1);
    }
	return true;
}

//Bring in result.txt frequentitemset bptreeg created
bool Manager::BTLOAD()
{
    if (bptree->getRoot() != NULL) {return false;}
    //Initialize frequentparttern in fpgrowth and output / map (set <string>, int) Type
    map<set<string>, int> fs = fpgrowth->getFrequentPatterns(fpgrowth->getHeaderTable(), fpgrowth->getTree());
    
    //After converting a map into a vector value in ascending order based on the map
    vector< pair<set<string>,int>> vec;
    for (auto it = fs.begin(); it != fs.end(); it++) { vec.push_back(*it); }
    sort(vec.begin(), vec.end(),[](const pair<set<string>, int>& l, const pair<set<string>, int>& r) {
        if (l.second != r.second) { return l.second < r.second; }
            return l.first < r.first;
        });

    //Insertion (frequency, set) transfer into data, bptree creation
    for (int i = 0; i < vec.size(); i++) { bptree->Insert(vec[i].second, vec[i].first); }
    
    return true;
}

//Item list print
bool Manager::PRINT_ITEMLIST() {
    if (fpgrowth->printList()) {return true; }
	return false;
}

//fptree print
bool Manager::PRINT_FPTREE() {
    fpgrowth->getHeaderTable()->ascendingIndexTable();//Sort by Frequency Ascending
    if (!fpgrowth->printTree()) {return false;}
    return true;
}


bool Manager::PRINT_MIN(char* item, int min_frequency) {
    if (bptree->printFrequency(string(item), min_frequency)) { return true; }
    else { return false; }
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
    int frequenct= fpgrowth->item_frequency(item);
    double fre = rate * frequenct, confidence=0;
    int fi = ceil(fre);//By rounding up fre and changing it to an int type, it makes it possible to find the minimum datanode with a frequency that is more than rate*total frequency.
    
    if (bptree->printConfidence(string(item), frequenct, fi)) { return true; }
    else { return false; }
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
    if (bptree->printRange(string(item), start, end)) { return true; }
    else { return false; }
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "======== ERROR " << n << " ========" << endl;
	flog << "=======================" << endl << endl;
   
    cout << "======== ERROR " << n << " ========" << endl;
    cout << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
    cout << "Success" << endl;
    cout << "=======================" << endl << endl;
}
