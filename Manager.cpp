#include "Manager.h"
#include<iostream>
void Manager::run(const char* command)
{
	fin.open(command);
	if(!fin)//if file not open print
	{
		fout << "File Open Error" << endl;
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
			fout<<"========LOAD========"<<endl;
			bool a = LOAD();//check true or false
			if(a==true){
				printSuccessCode();
			}
			else{
				printErrorCode(100);
			}
			
		}
		else if(strcmp(command,"BTLOAD")==0){
			fout<<"========BTLOAD========"<<endl;
			bool a = BTLOAD();
			if(a==true){
				printSuccessCode();
			}
			else
				printErrorCode(200);

		}
		else if(strcmp(command,"PRINT_ITEMLIST")==0){// if command PRINT_ITEMLIST
			bool a = PRINT_ITEMLIST();
			if(a == false){
				printErrorCode(300);
			}
			else{
				fout<<"=================="<<endl;
			}
		}
		else if(strcmp(command,"PRINT_FPTREE")==0){
			fout<<"========PRINT_FPTREE======="<<endl;
			bool a = PRINT_FPTREE();
			if(a== true){
				fout<<"============================"<<endl;
			}
			else 
				printErrorCode(400);
		}
		else if(strcmp(command,"PRINT_BPTREE")==0){

			fout<<"=======PRINT_BPTREE======="<<endl;

			char* cmd2 = strtok(NULL," ");
			char* cmd3 = strtok(NULL,"\n");
			int k = atoi(cmd3);
			bool a = PRINT_BPTREE(cmd2,k);
			if(a == false)
			{
				printErrorCode(500);
			}
			else{
				fout<<"========================="<<endl;
			}
		}
		else if(strcmp(command,"SAVE")==0){
			fout<<"========SAVE========="<<endl;
			fpgrowth->frequenctPatternSetting();
			bool a = fpgrowth->printPatern();
			if(a == true){
				printSuccessCode();
			}
			else printErrorCode(800);
		}
	}
	fin.close();
	return;
}
bool Manager::PRINT_ITEMLIST(){
	fout<<"=======PRINT_ITEMLIST======="<<endl;
	bool a = fpgrowth->printList();
	if(a){ // if not empty Header Table
		return true;
	}
	else//if empty
		return false;
	
}

bool Manager::LOAD()
{
	list<string> data_list;
	
	ifstream market;
	market.open("market.txt");
	if(!market){
		return false;
	}
	char buf1[10000] = {0};
	char buf2[10000] = {0};
	char* temp = NULL;

	while(!market.eof()){
		market.getline(buf1,10000);
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
	fpgrowth->getHeaderTable()->insertDataNode(fpgrowth->getHeaderTable()); //make data table
	temp = NULL;
	market.open("market.txt");
	while(!market.eof()){
		market.getline(buf1, 10000);
		strcpy(buf2,buf1);
		list<string>buylist;
		temp = strtok(buf1, "	");
		if(temp == NULL){
			continue;
		}
		temp = strtok(NULL,"	");
		while (temp != NULL) {
			temp = strtok(NULL, "	");
		}
		temp = strtok(buf2, "	");
		while(temp!=NULL){
			string string_temp = temp;
			buylist.push_back(string_temp);
			temp = strtok(NULL, "	");
			if(temp == NULL){
				continue;
			}
		}
		fpgrowth->createFPtree(fpgrowth->getTree(), fpgrowth->getHeaderTable(), buylist, 1);//make fptree
	}
	market.close();
	return true;
}
bool Manager::BTLOAD()
{
	ifstream fin;
	char buf[3000] = { 0 };
	char buf2[3000] = { 0 };
	char* temp = NULL;
	fin.open("result.txt");
	if (!fin) {//file open error
		return false;
	}

	while (!fin.eof())
	{
		fin.getline(buf, 150);
		set<string> tempset;
		int tempkey = 0;
		strcpy(buf2, buf);
		temp = strtok(buf, "	");
		if (temp == NULL)continue;
		temp = strtok(NULL, "	");
		while (temp != NULL)
		{
			temp = strtok(NULL, "	");
		}
		temp = strtok(buf2, "	");
		tempkey = (atoi(temp));//get frequency
		temp = strtok(NULL, "	");
		while (temp != NULL)
		{
			string tempstring(temp);
			tempset.insert(tempstring);
			temp = strtok(NULL, "	");
		}
		bptree->Insert(tempkey, tempset);//insert to bptree
	}
	return true;
}


bool Manager::PRINT_FPTREE() {
	bool a = fpgrowth->printTree();
	if( a==true){
		return true;
	}
	else
		return false;
}
bool Manager::PRINT_BPTREE(char* item, int min_frequency)
{
	bool a = bptree->printFrequency(item, min_frequency);
	return a;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	fout << "ERROR " << n << endl;
	fout << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	fout << "Success" << endl;
	fout << "=======================" << endl << endl;
}

