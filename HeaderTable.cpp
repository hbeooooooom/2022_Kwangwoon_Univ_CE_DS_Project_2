#include "HeaderTable.h"

HeaderTable::~HeaderTable() {

}

void HeaderTable::insertDataNode(HeaderTable* table){
	list<pair<int,string>> lista = table->getindexTable();
	for(list<pair<int,string>>::iterator iter = lista.begin(); iter!=lista.end(); iter++){
		FPNode* food_ptr = new FPNode;
		dataTable.insert({iter->second,food_ptr});
	}
}
void HeaderTable::insertTable1(char* item, int frequency) {
	string change_item = item;//change string
	
		for (list<pair<int, string>>::iterator iter = indexTable.begin(); iter != indexTable.end(); iter++) {
			if (iter->second == item) {
				iter->first += frequency;
				return;
		}
	}
	indexTable.push_back({ frequency,change_item });
	descendingIndexTable();
}


void HeaderTable::insertTable(char* item, int frequency) {
	string change_item = item;//change string
	if(frequency == 0){
		frequency++;
		indexTable.push_back(make_pair(frequency,change_item));
	}
	else{
		for(list<pair<int,string>>::iterator iter = indexTable.begin();iter!=indexTable.end();iter++){
			if(iter->second == item){
				iter->first++;
			}
		}
	}
	descendingIndexTable();
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
