#define _CRT_SECURE_NO_WARNINGS
#include "FPGrowth.h"

FPGrowth::~FPGrowth() {

}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
	list<pair<int, string>>idxtable = table->getindexTable(); //get indexdata
	for (list<string>::iterator customer_iter = item_array.begin(); customer_iter != item_array.end();) //customer buy list
	{
		for (list<pair<int, string>>::iterator frequence_iter = idxtable.begin(); frequence_iter != idxtable.end(); frequence_iter++) // headertable list
		{
			if (frequence_iter->second == *customer_iter) //if same item
			{
				if (frequence_iter->first < threshold) //if frequency < threshold delete item
				{
					customer_iter = item_array.erase(customer_iter);// delete and return next
				}
				else { customer_iter++; }
				break;
			}

		}
	}
	list<pair<int, string>> sorting_list; //sort list with frequency

	for (list<string>::iterator customer_iter = item_array.begin(); customer_iter != item_array.end(); customer_iter++)//customer buy list
	{
		for (list<pair<int, string>>::iterator frequence_iter = idxtable.begin(); frequence_iter != idxtable.end(); frequence_iter++)
		{
			if (frequence_iter->second == *customer_iter)
			{
				sorting_list.push_back({ frequence_iter->first, frequence_iter->second });
				break;
			}
		}

	}
	sorting_list.sort(greater<pair<int, string>>());//sort frequency greater
	
	FPNode* currNode = root;

	for (list<pair<int, string>>::iterator iter = sorting_list.begin(); iter != sorting_list.end(); iter++) { //make fp tree and connect table , node
		FPNode* child_node = currNode->getChildrenNode(iter->second);//because root is NULL
		if (child_node == NULL) {//item in tree is false
			FPNode* newNode = new FPNode;
			string str = iter->second;
			newNode->setItem(str);
			newNode->setParent(currNode);
			newNode->updateFrequency(1);
			currNode->pushchildren(str, newNode);
			connectNode(table, str, newNode);
			currNode = newNode;
		}
		else {
			currNode = child_node;
			currNode->updateFrequency(1);
		}
	}
}

void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {
	FPNode* currNode;
	map<string, FPNode*> DATA_Table = table->getdataTable();
	for (map<string, FPNode*>::iterator iter = DATA_Table.begin(); iter != DATA_Table.end(); iter++) {
		if (iter->first == item)
		{
			if (iter->second->getFrequency() == 0) //if FPNode is empty
			{
				table->conNode(item, node);
				//DATA_Table.find(item)->second = node; //connect node
				return;
			}
			else
			{
				currNode = iter->second;
				while (1) {
					if (currNode->getNext() == NULL) {
						break;
					}
					currNode = currNode->getNext();
				}
				currNode->setNext(node); //connect next node
				return;
			}
		}
	}
}

bool FPGrowth::contains_single_path(FPNode* pNode) {
	if (pNode->getChildren().size() == 0) return true;
	else if (pNode->getChildren().size() > 1) return false;
	return contains_single_path(pNode->getChildren().begin()->second);
}

map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* Table, FPNode* Tree) {
	Table->ascendingIndexTable();
	map<string, FPNode*> dataTable = Table->getdataTable();
	list<pair<int, string>> idxTable = Table->getindexTable();
	

	int k;
	for (list<pair<int, string>>::iterator iter = idxTable.begin(); iter != idxTable.end(); iter++)
	{
		if (iter->first >= threshold)// if indexNode frequency > threshold
		{
			for (map<string, FPNode*>::iterator iter2 = dataTable.begin(); iter2 != dataTable.end(); iter2++)
			{
				if (iter2->first.compare(iter->second) == 0)
				{
					list<list<string>> save_freqeunt_list;
					FPNode* currNode = iter2->second;//찾은걸 노드로 연결

					HeaderTable* frequent_fptree = new HeaderTable;//새로 연결할 list와 map들 만들기

					while (1) 
					{
						list<string> frequent_buy_list;
						FPNode* tempNode = currNode;
						if (currNode == NULL) { break; }
						int get_f = currNode->getFrequency();
						while (1)
						{
							if (currNode->getParent() == NULL) { break; }
							string a = currNode->getItem();
							char aa[100];
							strcpy(aa, a.c_str());
							frequent_fptree->insertTable1(aa, get_f); // 전체다 저장 index 테이블 만드는거 
							frequent_buy_list.push_back(currNode->getItem());//한라인 저장
							//cout << currNode->getItem() << "	" << currNode->getFrequency() << endl;
							currNode = currNode->getParent();
						}
						currNode = tempNode->getNext();
						save_freqeunt_list.push_back(frequent_buy_list);			
					}
					frequent_fptree->descendingIndexTable();
					frequent_fptree->insertDataNode(frequent_fptree);// 새로딴거 데이터 테이블까지
					FPNode* frequent_root = new FPNode;
					for (list<list<string>>::iterator i = save_freqeunt_list.begin(); i != save_freqeunt_list.end(); i++)
					{
						createFPtree(frequent_root, frequent_fptree, *i, 1);
					}
					//트리르 만듬 그럼 이제? 추출을 해야함
					//for문으로 index 테이블에서 ~에 대한 conditional fp-tree인지 찾고
					//datatable 위에 한칸보고 

				}
			}
		}
	}
	return  frequenctPatterns;
}

bool FPGrowth::printPatern()
{
	if (frequenctPatterns.begin() == frequenctPatterns.end())
		return false;
	for (map<set<string>, int>::iterator iter = frequenctPatterns.begin(); iter != frequenctPatterns.end(); iter++)
	{
		flog << iter->second << "	";
		set<string>temp = iter->first;
		for (set<string>::iterator iter2 = temp.begin(); iter2 != temp.end(); iter2++)
		{
			flog << *iter2 << "	";
		}
		flog << endl;
	}
	return true;
}

void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}

bool FPGrowth::printList() {
	list<pair<int, string>> li = table->getindexTable();
	if (li.begin() != li.end()) *fout << "Item		Frequency" << endl;
	else return false;
	for (list<pair<int, string>>::iterator it = li.begin(); it != li.end(); it++) {
		*fout << it->second << "	  " << it->first << endl;
	}
	return true;
}
bool FPGrowth::printTree() {

	table->ascendingIndexTable(); // ascending index table
	list<pair<int, string>> idxTable = table->getindexTable();
	if (idxTable.empty() == 1) { return false; }

	*fout << "{StandardItem.Frequency}		(Path_Item.Frequency)" << endl;
	FPNode* curFP_Node;
	FPNode* up;
	FPNode* next;
	for (list<pair<int, string>>::iterator iter = idxTable.begin(); iter != idxTable.end(); iter++)
	{
		if (iter->first >= threshold) // small threshold is not print
		{
			*fout << "{" << iter->second << ", " << iter->first << "}" << endl; //print item
			curFP_Node = table->getNode(iter->second);
			*fout << "(" << curFP_Node->getItem() << "," << curFP_Node->getFrequency() << ")  ";
			up = curFP_Node->getParent();
			while (1)
			{
				if (up->getFrequency() == 0) break; //if Frequency 0 is root
				else
				{
					*fout << "(" << up->getItem() << "," << up->getFrequency() << ")  ";
					up = up->getParent(); //move parent node
				}
			}

			*fout << endl;
			if (curFP_Node->getNext() != NULL)
			{
				next = curFP_Node->getNext();
				while (1)
				{
					*fout << "(" << next->getItem() << "," << next->getFrequency() << ")" << "  ";
					up = next->getParent();//up to paraent
					while (1)
					{
						if (up->getFrequency() == 0)// frequency 0 is root
							break;
						else {
							*fout << "(" << up->getItem() << "," << up->getFrequency() << ")" << "  ";
							up = up->getParent();
						}
					}
					if (next->getNext() == NULL) {
						break;
					}
					else {
						next = next->getNext();// next item
						*fout << endl;
					}
				}
				*fout << endl;
			}
		}
	}
	table->descendingIndexTable();
	return true;
}
void FPGrowth::saveFrequentPatterns() {



}
