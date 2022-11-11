#include "HeaderTable.h"

HeaderTable::~HeaderTable() {
}

void HeaderTable::insertDataNode(HeaderTable* table){// insert datatable
	list<pair<int,string>> lista = table->getindexTable(); // get indextable
	for(list<pair<int,string>>::iterator iter = lista.begin(); iter!=lista.end(); iter++){
		FPNode* food_ptr = new FPNode; //make pointer
		dataTable.insert({iter->second,food_ptr});// insert
	}
}
void HeaderTable::insertTable1(char* item, int frequency) { //save conditional fp tree list function
	string change_item = item;//change string
	
		for (list<pair<int, string>>::iterator iter = indexTable.begin(); iter != indexTable.end(); iter++) {
			if (iter->second == item) { // if exist item
				iter->first += frequency; // frequency ++
				return;
		}
	}
	indexTable.push_back({ frequency,change_item }); // not exist item make table
	descendingIndexTable();
}


void HeaderTable::insertTable(char* item, int frequency) {
	string change_item = item;//change string
	if(frequency == 0){ //if not exist node
		frequency++; // frequency ++
		indexTable.push_back(make_pair(frequency,change_item)); //make table
	}
	else{
		for(list<pair<int,string>>::iterator iter = indexTable.begin();iter!=indexTable.end();iter++){
			if(iter->second == item){
				iter->first++;// if exist table frequency ++
			}
		}
	}
	descendingIndexTable(); //descending table
}
int HeaderTable::find_frequency(string item){
	int frequency = 0;
	for(list<pair<int,string>>::iterator iter = indexTable.begin(); iter!=indexTable.end();iter++){
		if(iter->second == item){//if find same item list
			frequency = iter->first;
			return frequency;//list frequency return
		}
	}
	return frequency;
}
