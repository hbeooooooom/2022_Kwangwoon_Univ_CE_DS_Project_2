#pragma once
#include "HeaderTable.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

class FPGrowth
{
private:
	int threshold;
	FPNode* fpTree; //this is root
	HeaderTable* table; //headerTable
	map<set<string>, int> frequenctPatterns;
	ofstream* fout;
	ofstream flog;
public:
	FPGrowth(ofstream *fout, int threshold) {
		this->threshold = threshold;
		flog.open("result.txt", ios::app);
		flog.setf(ios::fixed);
		fpTree = new FPNode;  table = new HeaderTable;
		this->fout = fout;
	}
	~FPGrowth();
	void createTable(char* item, int frequency) { table->insertTable(item, frequency); }
	void createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency);
	void connectNode(HeaderTable* table, string item, FPNode* node);
	
	void frequenctPatternSetting() {
		table->ascendingIndexTable();
		frequenctPatterns = getFrequentPatterns(table, fpTree);
	}
	
	bool printPatern();
	map<set<string>, int> getFrequentPatterns(HeaderTable* Table, FPNode* Tree);
	void powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* flag, int depth);
	bool contains_single_path(FPNode* pNode);
	int item_frequency(string item) {return table->find_frequency(item);}
	FPNode* getTree() { return fpTree; }
	HeaderTable* getHeaderTable() { return table; }

	bool printList();
	bool printTree();
	void saveFrequentPatterns();

	};


