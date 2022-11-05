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
		/* You must fill here */
	}

	ifstream fin;
	ofstream fout;
	
	char * RESULT_LOG_PATH = "log.txt";//log file
	void run(const char* command);
	bool LOAD();
	bool BTLOAD();
	
	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_BPTREE(char* item, int min_frequency);
	

	void printErrorCode(int n);
	void printSuccessCode();

};

