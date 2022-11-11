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
	void createTable(char* item, int frequency) { table->insertTable(item, frequency); } //create Table function
	void createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency); //create fptree function
	void connectNode(HeaderTable* table, string item, FPNode* node); // connection data table and fp tree node
	
	void frequenctPatternSetting() { //set frequenctPatternset
		table->ascendingIndexTable();
		frequenctPatterns = getFrequentPatterns(table, fpTree);
	}
	
	bool printPatern(); //printPatern
	map<set<string>, int> getFrequentPatterns(HeaderTable* Table, FPNode* Tree); //get FrequenctPattern function
	void powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* flag, int depth); //Power set output function
	bool contains_single_path(FPNode* pNode); 
	int item_frequency(string item) {return table->find_frequency(item);} //get frequency for an item function
	FPNode* getTree() { return fpTree; } // get fptree function
	HeaderTable* getHeaderTable() { return table; } //get Header table function

	bool printList(); //print index list function
	bool printTree(); // print tree function
	void saveFrequentPatterns(); // save frequentPatterns

	};


