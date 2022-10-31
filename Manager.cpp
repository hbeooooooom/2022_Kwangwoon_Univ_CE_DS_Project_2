#include "Manager.h"
#include<iostream>
void Manager::run(const char* command)
{
	fin.open(command);
	if(!fin)//if file not open print
	{
		flog << "File Open Error" << endl;
		return;
	}
	char cmd[100];
	while (!fin.eof())
	{
		fin.getline(cmd, 1000);
		char* command = strtok(cmd, " ");//get command
		if(command ==NULL)
			continue;
		if(strcmp(command, "LOAD")==0){//if command LOAD
			flog<<"========LOAD========"<<endl;
			bool a = LOAD();
			if(a==true){
				flog<<"Success"<<endl;
			}
			else{
				flog<<"ERROR 100"<<endl;
			}
			flog<<"===================="<<endl;
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	ifstream market;
	market.open("market.txt");
	if(!market){
		return false;
	}
	char buf1[1000] = {0};
	char buf2[1000] = {0};
	char* temp = NULL;

	while(!market.eof()){
		market.getline(buf1,1000);
		strcpy(buf2,buf1);
		temp = strtok(buf1,"	");
		if(temp == NULL){
			continue;
		}
		temp = strtok(NULL,"	");
		while(temp != NULL){
			temp = strtok(NULL,"	");
		}
		temp = strtok(buf2,"	");
		while(temp != NULL){
			string string_temp= temp;
			fpgrowth->createTable(temp, fpgrowth->item_frequency(string_temp));//make table
			temp = strtok(NULL, "	");
			if(temp == NULL){
				break;
			}
		}
	}
	market.close();
	temp = NULL;
	market.open("market.txt");
	//fpgrowth->getHeaderTable()->insertDataNode(fpgrowth->getHeaderTable());
	char buf3[1000] ={0};
	char buf4[1000] ={0};
	if(!market){
		return false;
	}
	else{
		while(!market.eof()){
			market.getline(buf3,1000);
			strcpy(buf4,buf3);
			list<string> stringlist;
			temp = strtok(buf3," ");
			if(temp == NULL){
				continue;
			}
			temp = strtok(NULL, "	");
			while(temp !=NULL){
				temp=strtok(NULL,"	");
			}
			temp = strtok(buf4,"	");
			while(temp != NULL){
				string string_temp = temp;
				stringlist.push_back(string_temp);
				temp = strtok(NULL, "	");
			}
			if(temp == NULL){
				continue;
			}
			fpgrowth->createFPtree();
		}
	}
	return true;
}




bool Manager::BTLOAD()
{
	
	return true;
}

bool Manager::PRINT_ITEMLIST() {
	
}

bool Manager::PRINT_FPTREE() {
	
}

bool Manager::PRINT_BPTREE(char* item, int min_frequency) {
	
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
	
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
	
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	//flog << ERROR " << n << " << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

