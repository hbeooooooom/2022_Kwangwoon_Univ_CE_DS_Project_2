#include "BpTree.h"
#include<cstring>
#include<list>
bool BpTree::Insert(int key, set<string> set) { //make b+-tree
	FrequentPatternNode* new_frequentpatternNode = new FrequentPatternNode; // make FrequentPatternNode
	new_frequentpatternNode->InsertList(set); // push item list
	new_frequentpatternNode->setFrequency(key); // push frequency
	if (getRoot() == NULL) //if first push data
	{
		BpTreeNode* tree_big_node = new BpTreeDataNode; // make data node
		tree_big_node->insertDataMap(key, new_frequentpatternNode); //insert data frequency, frequentpatternnode
		root = tree_big_node; // set root 
		return true;
	}
	BpTreeNode* currNode = searchDataNode(key); //find node datanode->frequency < key < datanode->frequency

	if (currNode->getDataMap()->find(key) == currNode->getDataMap()->end()) {//If the value does not exist
		currNode->insertDataMap(key, new_frequentpatternNode); // make node
		if (excessDataNode(currNode))// if the number of data nodes is exceeded
		{
			splitDataNode(currNode); //split data node
			currNode = currNode->getParent();//get parent node
			while (excessIndexNode(currNode))//if the number of index nodes is exceded
			{
				splitIndexNode(currNode); //split index node
				currNode = currNode->getParent();//get parent node
			}

		}
	}
	else {
		currNode->getDataMap()->find(key)->second->InsertList(set); // if the value exist
	}

	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;

	if (pCur == NULL) return pCur;
	if (pCur->getMostLeftChild() == NULL) return pCur;
	while (1) {
		while (pCur->getMostLeftChild() != NULL) { pCur = pCur->getMostLeftChild(); } //go to datanode

		map<int, FrequentPatternNode*>::iterator iter_search = pCur->getDataMap()->begin();
		while (1) {
			if (n > iter_search->first) { // if n > frequency 
				if (pCur->getNext() == NULL) return pCur; // if last data node
				pCur = pCur->getNext();
				iter_search = pCur->getDataMap()->begin(); 
				if (n < iter_search->first) { // if next node frequency > n
					pCur = pCur->getPrev();
					return pCur;
				}
				for (; iter_search != pCur->getDataMap()->end(); iter_search++) { 
					if (n <= iter_search->first) { return pCur; } // if n < first frequency return datanode
				}
				if (pCur->getNext() == NULL) { return pCur; }
				iter_search = pCur->getDataMap()->begin(); // if last datanode return
			}
			else if (n <= iter_search->first) { return pCur; }
		}
	}
	return pCur;
}


void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	int a = ceil((order - 1) / 2.0) + 1; // cut node
	int count = 1;
	list<int> save_delete_frequency;
	map<int, FrequentPatternNode*> cutNode;
	int cut_frequent = 0;
	for (map <int, FrequentPatternNode*>::iterator iter = pDataNode->getDataMap()->end(); iter != pDataNode->getDataMap()->begin(); ) {//cut front, back up node get
		--iter;
		if (count == a) { // if list is center
			cut_frequent = iter->first;  // up indexnode get frequent
			cutNode.insert({ iter->first,iter->second }); // cut node
			save_delete_frequency.push_back(iter->first); // save node
			break;
		}
		cutNode.insert({ iter->first, iter->second }); // Divide existing nodes
		save_delete_frequency.push_back(iter->first); // Save node information to delete
		count++;
	}
	for (list<int>::iterator iter = save_delete_frequency.begin(); iter != save_delete_frequency.end(); iter++)
	{
		pDataNode->deleteMap(*iter); // Delete from existing node
	}
	BpTreeNode* cut_dataNode = new BpTreeDataNode;
	for (map<int, FrequentPatternNode*>::iterator iter = cutNode.begin(); iter != cutNode.end(); iter++)
	{
		cut_dataNode->insertDataMap(iter->first, iter->second); //make new data node
	}

	if (pDataNode->getParent() == NULL) //if no index node
	{
		BpTreeNode* newidx_node = new BpTreeIndexNode; //make new index node
		root = newidx_node; //root is index node change
		newidx_node->insertIndexMap(cut_frequent, cut_dataNode);// push data index node
		cut_dataNode->setParent(newidx_node); // Associate split nodes
		newidx_node->setMostLeftChild(pDataNode); // index node left child set
		pDataNode->setParent(newidx_node); // Parent connection of existing nodes
		pDataNode->setNext(cut_dataNode); // connection next node 
		cut_dataNode->setPrev(pDataNode); // connection prev node
	}
	else
	{
		BpTreeNode* getindex = pDataNode->getParent(); // get parent node
		getindex->insertIndexMap(cut_frequent, cut_dataNode); // insert parent node
		cut_dataNode->setNext(pDataNode->getNext());
		cut_dataNode->setParent(getindex);// connection new data node
		cut_dataNode->setPrev(pDataNode); //  connection existing node
		pDataNode->setNext(cut_dataNode); // connection new data node

	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	int a = ceil((order - 1) / 2.0) + 1;
	int count = 1;
	list<int> save_delete_frequency;
	map<int, BpTreeNode*> cutNode;
	int cut_frequent = 0;
	for (map <int, BpTreeNode*>::iterator iter = pIndexNode->getIndexMap()->end(); iter != pIndexNode->getIndexMap()->begin(); ) {
		--iter;
		if (count == a) {// if list is center
			cut_frequent = iter->first; // cut indexnode get frequent
			cutNode.insert({ iter->first,iter->second });// cut node
			save_delete_frequency.push_back(iter->first);// save node
			break;
		}
		cutNode.insert({ iter->first, iter->second });// Divide existing nodes
		save_delete_frequency.push_back(iter->first);// Save node information to delete
		count++;
	}
	for (list<int>::iterator iter = save_delete_frequency.begin(); iter != save_delete_frequency.end(); iter++)
	{
		pIndexNode->deleteMap(*iter); //delete existing node
	}
	BpTreeNode* cut_idxNode = new BpTreeIndexNode;
	for (map<int, BpTreeNode*>::iterator iter = cutNode.begin(); iter != cutNode.end(); iter++)
	{
		cut_idxNode->insertIndexMap(iter->first, iter->second); //make new data node
	}
	cut_idxNode->setMostLeftChild(cut_idxNode->getIndexMap()->begin()->second);
	if (pIndexNode->getParent() == NULL) {
		BpTreeNode* new_idxNode = new BpTreeIndexNode;
		new_idxNode->insertIndexMap(cut_idxNode->getIndexMap()->begin()->first, cut_idxNode);//make up node and connection right index node
		cut_idxNode->deleteMap(cut_idxNode->getIndexMap()->begin()->first);//now delete new_idxNode frequency
		cut_idxNode->setParent(new_idxNode);// new index node set parent
		new_idxNode->setMostLeftChild(pIndexNode); // new index node set most left child
		pIndexNode->setParent(new_idxNode); // exist node set parent
	}
	else
	{
		BpTreeNode* parent_idxNode = pIndexNode->getParent(); // get parent index node
		parent_idxNode->insertIndexMap(cut_idxNode->getIndexMap()->begin()->first, cut_idxNode); // insert data
		cut_idxNode->deleteMap(cut_idxNode->getIndexMap()->begin()->first);//delete data
		cut_idxNode->setParent(parent_idxNode); // set parent

	}
	return;
}
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}


bool BpTree::printConfidence(string item, double item_frequency, double min_confidence)
{
	if (root == NULL) return false;
	double k = min_confidence * item_frequency; // Subset frequency divided by total frequency of the corresponding
	BpTreeNode* currNode = searchDataNode(k); //go to data node
	map <int, FrequentPatternNode*>* datNode = currNode->getDataMap();
	map <int, FrequentPatternNode*>::iterator iter1;

	multimap<int, set<string>> list = datNode->begin()->second->getList();
	multimap<int, set<string>>::iterator iter2;

	double kk;
	*fout << "FrequentPattern		Frequency" << endl;
	double ka;
	while (1) {
		if (currNode == NULL) break;
		for (iter1 = datNode->begin(); iter1 != datNode->end(); iter1++)
		{
			list = iter1->second->getList();
			for (iter2 = list.begin(); iter2 != list.end(); iter2++)
			{
				ka = iter1->second->getFrequency(); //get frequency
				kk = ka / item_frequency;
				for (set<string>::iterator li = iter2->second.begin(); li != iter2->second.end(); li++)
				{
					if (*li == item)
					{
						if (min_confidence < ka / item_frequency)
						{
							printFrequentPatterns(iter2->second, item, ka, kk);//print
						}
					}
				}
			}

		}
		currNode = currNode->getNext();
		if (currNode == NULL)break;
		datNode = currNode->getDataMap();

	}

	return true;
}
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	*fout << "FrequentPattern		Frequency" << endl;
	if (root == NULL) return false;
	BpTreeNode* currNode = searchDataNode(min_frequency);// find frequency > min_frequency data node
	map <int, FrequentPatternNode*>* datNode = currNode->getDataMap();
	map <int, FrequentPatternNode*>::iterator iter1;
	multimap<int, set<string>> list = datNode->begin()->second->getList();
	multimap<int, set<string>>::iterator iter2;

	int k;
	while (1) {
		if (currNode == NULL) break;
		for (iter1 = datNode->begin(); iter1 != datNode->end(); iter1++)
		{
			list = iter1->second->getList();
			for (iter2 = list.begin(); iter2 != list.end(); iter2++)
			{
				k = iter1->second->getFrequency(); //get frequency
				for (set<string>::iterator li = iter2->second.begin(); li != iter2->second.end(); li++)
				{
					if (*li == item)
					{
						if (k >= min_frequency)
						{
							printFrequentPatterns(iter2->second, item, k);//print
						}
					}
				}
			}

		}
		currNode = currNode->getNext();
		if (currNode == NULL)break;
		datNode = currNode->getDataMap();

	}
	return true;
}
bool BpTree::printRange(string item, int min, int max) {
	if (root == NULL) return false;
	*fout << "FrequentPattern		Frequency" << endl;
	BpTreeNode* currNode = searchDataNode(min);// find min frequency < frequency data node
	map <int, FrequentPatternNode*>* datNode = currNode->getDataMap();
	map <int, FrequentPatternNode*>::iterator iter1;
	multimap<int, set<string>> list = datNode->begin()->second->getList();
	multimap<int, set<string>>::iterator iter2;

	int k;
	while (1) {
		if (currNode == NULL) break;
		for (iter1 = datNode->begin(); iter1 != datNode->end(); iter1++)
		{
			list = iter1->second->getList();
			for (iter2 = list.begin(); iter2 != list.end(); iter2++)
			{
				k = iter1->second->getFrequency(); //get frequency
				for (set<string>::iterator li = iter2->second.begin(); li != iter2->second.end(); li++)
				{
					if (*li == item)
					{
						if (k >= min && k <= max) // if min <= frequency <= max
							printFrequentPatterns(iter2->second, item, k); //print
					}
				}
			}

		}
		currNode = currNode->getNext();
		if (currNode == NULL)break;
		datNode = currNode->getDataMap();

	}
	return true;
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item, int k) {

	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) { //print data node items
		string temp = *it++;
		*fout << temp << ", ";
		if (it == curPattern.end()) {
			*fout <<  "}    " << k << endl;
			break;
		}
	}
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item, double k, double kk) {

	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) { //print data node items
		string temp = *it++;
		*fout << temp;
		if (it == curPattern.end()) {
			*fout <<  "}    " << k << "  " << kk << endl;
			break;
		}
		*fout<<", ";
	}
}