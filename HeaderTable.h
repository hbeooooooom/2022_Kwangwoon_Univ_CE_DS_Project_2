#pragma once
#include "FPNode.h"
#include <list>

class HeaderTable
{
private:
	list<pair<int, string> > indexTable;
	map<string, FPNode*> dataTable;
public:
	
	HeaderTable() { }
	~HeaderTable();
	void insertTable(char* item, int frequency); //insert data function
	void insertTable1(char* item, int frequency); //save conditional fp tree list function
	list<pair<int, string>> getindexTable() { return indexTable; } // get indextable function
	map<string, FPNode*> getdataTable() { return dataTable; } // get datatable function
	FPNode* getNode(string item) { return dataTable.find(item)->second; } // get FPNode function
	void descendingIndexTable() { indexTable.sort(greater<pair<int, string>>()); }// descending function
	void ascendingIndexTable() { indexTable.sort(); } //ascending function
	int find_frequency(string item); // find_item function
	void insertDataNode(HeaderTable* table); // insert datanode function
	void conNode(string item, FPNode* no) { dataTable.find(item)->second = no; }
};


