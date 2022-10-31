#include "HeaderTable.h"

HeaderTable::~HeaderTable() {

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
