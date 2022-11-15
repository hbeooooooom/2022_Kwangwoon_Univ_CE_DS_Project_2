#define _CRT_SECURE_NO_WARNINGS
#include "FPGrowth.h"
#include <algorithm> 
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
				sorting_list.push_back({ frequence_iter->first, frequence_iter->second }); //push data
				break;
			}
		}

	}
	sorting_list.sort(greater<pair<int, string>>());//sort frequency greater

	FPNode* currNode = root;

	for (list<pair<int, string>>::iterator iter = sorting_list.begin(); iter != sorting_list.end(); iter++) { //make fp tree and connect table , node
		FPNode* child_node = currNode->getChildrenNode(iter->second);//because root is NULL
		if (child_node == NULL) {//item in tree is false
			FPNode* newNode = new FPNode; // create node
			string str = iter->second;
			newNode->setParent(currNode); //set parent
			newNode->setItem(str); //set item
			newNode->updateFrequency(1); //update frequency
			currNode->pushchildren(str, newNode); // set children node
			connectNode(table, str, newNode); // connect fp node data table
			currNode = newNode;
		}
		else {
			currNode = child_node; //go child node
			currNode->updateFrequency(1);//update frequency +1
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
				table->conNode(item, node); // connect node
				return;
			}
			else
			{
				currNode = iter->second;
				while (1) {
					if (currNode->getNext() == NULL) { //if next node NULL
						break;
					}
					currNode = currNode->getNext(); //go next node
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
	map<string, FPNode*> dataTable = Table->getdataTable(); //get table
	list<pair<int, string>> idxTable = Table->getindexTable(); // get table

	for (list<pair<int, string>>::iterator iter = idxTable.begin(); iter != idxTable.end(); iter++) 
	{
		if (iter->first >= threshold) // if frequent >= threshold
		{
			HeaderTable* new_header_table = new HeaderTable; //make new headertable
			for (map<string, FPNode*>::iterator iter1 = dataTable.begin(); iter1 != dataTable.end(); iter1++) 
			{
				if (iter1->first == iter->second) //find data table list
				{

					string get_item = iter->second;
					multimap<set<string>, int> first_map;
					multimap<set<string>, int> second_map;
					
					
					map<set<string>, int> fre_map;

					FPNode* currNode = iter1->second;
					while (1)
					{
						if (currNode == NULL)break;
						int get_frequency = currNode->getFrequency();
						FPNode* tempNode = currNode;
						set<string>set_list;
						while (1)
						{
							if (currNode->getParent() == NULL) break;
							string get_item = currNode->getItem(); //get item
							new_header_table->insertTable1(get_item, get_frequency); // make index table
							set_list.insert(get_item);  //save item list

							currNode = currNode->getParent();
						}
						first_map.insert({ set_list, get_frequency });
						currNode = tempNode->getNext();
					}
					new_header_table->ascendingIndexTable();
					
					for (multimap<set<string>, int>::iterator iter3 = first_map.begin(); iter3 != first_map.end(); iter3++)
					{
						set<string>save_list;
						int save_frequent = iter3->second;
						set<string>get_list = iter3->first;
						for (set<string>::iterator iter4 = get_list.begin(); iter4 != get_list.end(); iter4++)
						{
							list< pair<int, string>> get_table_list = new_header_table->getindexTable();
							for (list<pair<int, string>>::iterator iter2 = get_table_list.begin();iter2 != get_table_list.end(); iter2++)
							{
								if (iter2->second == *iter4 && iter2->first >= threshold)
								{
									save_list.insert(*iter4); // save   item frequency > threshold
								}
							}
						}
						if (second_map.find(save_list) == second_map.end()) 
						{
							second_map.insert({ save_list, save_frequent});// if not exist items
						}
						else
						{
							int k = second_map.find(save_list)->second;
							second_map.erase(save_list);
							second_map.insert({ save_list,k + save_frequent }); // if exist items
						}

					}
					for (map<set<string>,int>::iterator it1 = second_map.begin(); it1 != second_map.end(); it1++)
					{
						vector<string>item_list;
						for (set<string>::iterator it2 = it1->first.begin(); it2 != it1->first.end(); it2++)
						{
							item_list.push_back(*it2); //make item list vector
						}
						int* ptr = new int(item_list.size());
						powerSet(&frequenctPatterns, item_list, get_item, it1->second, ptr, 0); // instance powerset function
						delete[] ptr;
					}
				}
			}
		}
	}


	return  frequenctPatterns;
}

bool FPGrowth::printPatern()
{
	
	if (frequenctPatterns.begin() == frequenctPatterns.end()) // if no pattern
		return false;
	for (map<set<string>, int>::iterator iter = frequenctPatterns.begin(); iter != frequenctPatterns.end(); iter++)
	{
		if (iter->first.size() < 2 || iter->second < 2) { continue; }
		flog << iter->second<<"	";
		for (set<string>::iterator iter2 = iter->first.begin(); iter2 != iter->first.end(); iter2++) //print pattern
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
	else return false; //not exist indextable
	for (list<pair<int, string>>::iterator it = li.begin(); it != li.end(); it++) { //print indexnode
		*fout << it->second << "	  " << it->first << endl;
	}
	return true;
}
bool FPGrowth::printTree() {

	table->ascendingIndexTable(); // ascending index table
	list<pair<int, string>> idxTable = table->getindexTable(); //get indextable
	if (idxTable.empty() == 1) { return false; } // if not exist indexTable

	*fout << "{StandardItem.Frequency}		(Path_Item.Frequency)" << endl;
	FPNode* curFP_Node;
	FPNode* up_node;
	FPNode* next;
	for (list<pair<int, string>>::iterator iter = idxTable.begin(); iter != idxTable.end(); iter++)
	{
		if (iter->first >= threshold) // small threshold is not print
		{
			*fout << "{" << iter->second << ", " << iter->first << "}" << endl; //print item list
			curFP_Node = table->getNode(iter->second);
			*fout << "(" << curFP_Node->getItem() << "," << curFP_Node->getFrequency() << ")  ";
			up_node = curFP_Node->getParent(); //up_node get current fpnode parent node
			while (1)
			{
				if (up_node->getFrequency() == 0) break; //if Frequency 0 is root
				else
				{
					*fout << "(" << up_node->getItem() << "," << up_node->getFrequency() << ")  ";
					up_node = up_node->getParent(); //move parent node
				}
			}

			*fout << endl;
			if (curFP_Node->getNext() != NULL)
			{
				next = curFP_Node->getNext();
				while (1)
				{
					*fout << "(" << next->getItem() << "," << next->getFrequency() << ")" << "  ";
					up_node = next->getParent();//up to paraent
					while (1)
					{
						if (up_node->getFrequency() == 0)// frequency 0 is root
							break;
						else {
							*fout << "(" << up_node->getItem() << "," << up_node->getFrequency() << ")" << "  ";
							up_node = up_node->getParent(); // get parent node for up_node
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
	table->descendingIndexTable(); // descending indextable
	return true;
}
void FPGrowth::saveFrequentPatterns() {



}
