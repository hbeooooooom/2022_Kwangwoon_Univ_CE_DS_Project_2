#pragma once
#include "FPGrowth.h"
#include "BpTree.h"
#include<iostream>
#include<fstream>
using namespace std;
class Manager
{
private:
	char* cmd;
	FPGrowth* fpgrowth;
	BpTree* bptree;
public:
	Manager(int threshold, int bpOrder)	//constructor
	{
		fout.open(RESULT_LOG_PATH,ios::out);
		fpgrowth = new FPGrowth(&fout,threshold);
		bptree = new BpTree(&fout,bpOrder);
	}


	~Manager()//destructor
	{
		fout.close();
	}

	ifstream fin;
	ofstream fout;
	
	char * RESULT_LOG_PATH = "log.txt";//log file
	void run(const char* command); 
	bool LOAD(); // LOAD function
	bool BTLOAD(); // BTLOAD function 
	
	bool PRINT_ITEMLIST(); // PRINT_ITEMLIST function
	bool PRINT_FPTREE(); // PRINT_FPTREE function

	bool PRINT_RANGE(char* item, int start, int end); // PRINT_RANGE function
	bool PRINT_CONFIDENCE(char* item, double rate); // PRINT_CONFIDENCE function
	bool PRINT_BPTREE(char* item, int min_frequency); // PRINT_BPTREE function
	void EXIT();

	void printErrorCode(int n); // print error code function
	void printSuccessCode(); //print success code

};

