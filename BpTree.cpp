#include "BpTree.h"
#include<cstring>
#include<list>
bool BpTree::Insert(int key, set<string> set) {
	FrequentPatternNode* new_frequentpatternNode = new FrequentPatternNode;
	new_frequentpatternNode->InsertList(set);
	new_frequentpatternNode->setFrequency(key);
	if (getRoot() == NULL)
	{
		BpTreeNode* tree_big_node = new BpTreeDataNode;
		tree_big_node->insertDataMap(key, new_frequentpatternNode);
		root = tree_big_node;
		return true;
	}
	BpTreeNode* currNode = searchDataNode(key); //노드따라 내려가야함 그냥 맨 밑으로 가는 작업


	if (currNode->getDataMap()->find(key) == currNode->getDataMap()->end()) {
		currNode->insertDataMap(key, new_frequentpatternNode);
		if (excessDataNode(currNode))//만약 데이터의 개수가 넘어간다?
		{
			splitDataNode(currNode);
			currNode = currNode->getParent();
			while (excessIndexNode(currNode))
			{
				splitIndexNode(currNode);
				currNode = currNode->getParent();
			}

		}
	}
	else {
		currNode->getDataMap()->find(key)->second->InsertList(set);
	}

	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;
	if (pCur == NULL) return pCur;
	if (pCur->getMostLeftChild() == NULL) return pCur;
	while (1) {
		while (pCur->getMostLeftChild() != NULL) { pCur = pCur->getMostLeftChild(); }

		map<int, FrequentPatternNode*>::iterator iter_search = pCur->getDataMap()->begin();
		while (1) {
			if (n > iter_search->first) {
				if (pCur->getNext() == NULL) return pCur;
				pCur = pCur->getNext();
				iter_search = pCur->getDataMap()->begin();
				if (n < iter_search->first) {
					pCur = pCur->getPrev();
					return pCur;
				}
				for (; iter_search != pCur->getDataMap()->end(); iter_search++) {
					if (n <= iter_search->first) { return pCur; }
				}
				if (pCur->getNext() == NULL) { return pCur; }
				iter_search = pCur->getDataMap()->begin();
			}
			else if (n <= iter_search->first) { return pCur; }
		}
	}
	return pCur;
}
BpTreeNode* BpTree::searchDataNode1(int n) {
	BpTreeNode* pCur = root;
	while (1) {
		while (pCur->getMostLeftChild() != NULL) { pCur = pCur->getMostLeftChild(); }

		map<int, FrequentPatternNode*>::iterator iter_search = pCur->getDataMap()->begin();
		while (1) {
			if (iter_search == pCur->getDataMap()->end()) { pCur = pCur->getNext(); }
			if (iter_search->first <= n) return pCur;
			iter_search++;
		}
	}
}
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	int a = ceil((order - 1) / 2.0) + 1;
	int count = 1;
	list<int> save_delete_frequency;
	map<int, FrequentPatternNode*> cutNode;
	int cut_frequent = 0;
	for (map <int, FrequentPatternNode*>::iterator iter = pDataNode->getDataMap()->end(); iter != pDataNode->getDataMap()->begin(); ) {//앞뒤 자르고 위로 올라갈 노드의 frequent 뽑기
		--iter;
		if (count == a) {
			cut_frequent = iter->first;
			cutNode.insert({ iter->first,iter->second });
			save_delete_frequency.push_back(iter->first);
			break;
		}
		cutNode.insert({ iter->first, iter->second });
		save_delete_frequency.push_back(iter->first);
		count++;
	}
	for (list<int>::iterator iter = save_delete_frequency.begin(); iter != save_delete_frequency.end(); iter++)
	{
		pDataNode->deleteMap(*iter);
	}
	BpTreeNode* cut_dataNode = new BpTreeDataNode;
	for (map<int, FrequentPatternNode*>::iterator iter = cutNode.begin(); iter != cutNode.end(); iter++)
	{
		cut_dataNode->insertDataMap(iter->first, iter->second); //자른 데이터노드 새로 만들기(뒤에거)
	}

	if (pDataNode->getParent() == NULL)
	{
		BpTreeNode* newidx_node = new BpTreeIndexNode;
		root = newidx_node;
		newidx_node->insertIndexMap(cut_frequent, cut_dataNode);
		cut_dataNode->setParent(newidx_node);
		newidx_node->setMostLeftChild(pDataNode);
		pDataNode->setParent(newidx_node);
		pDataNode->setNext(cut_dataNode);
		cut_dataNode->setPrev(pDataNode);
	}
	else
	{
		BpTreeNode* getindex = pDataNode->getParent();
		getindex->insertIndexMap(cut_frequent, cut_dataNode);
		cut_dataNode->setParent(getindex);
		cut_dataNode->setPrev(pDataNode);
		pDataNode->setNext(cut_dataNode);
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

	int a = ceil((order - 1) / 2.0) + 1;
	int count = 1;
	list<int> save_delete_frequency;
	map<int, BpTreeNode*> cutNode;
	int cut_frequent = 0;
	for (map <int, BpTreeNode*>::iterator iter = pIndexNode->getIndexMap()->end(); iter != pIndexNode->getIndexMap()->begin(); ) {//앞뒤 자르고 위로 올라갈 노드의 frequent 뽑기
		--iter;
		if (count == a) {
			cut_frequent = iter->first;
			cutNode.insert({ iter->first,iter->second });
			save_delete_frequency.push_back(iter->first);
			break;
		}
		cutNode.insert({ iter->first, iter->second });
		save_delete_frequency.push_back(iter->first);
		count++;
	}
	for (list<int>::iterator iter = save_delete_frequency.begin(); iter != save_delete_frequency.end(); iter++)
	{
		pIndexNode->deleteMap(*iter);
	}
	BpTreeNode* cut_idxNode = new BpTreeIndexNode;
	for (map<int, BpTreeNode*>::iterator iter = cutNode.begin(); iter != cutNode.end(); iter++)
	{
		cut_idxNode->insertIndexMap(iter->first, iter->second); //자른 데이터노드 새로 만들기(뒤에거)
	}
	cut_idxNode->setMostLeftChild(cut_idxNode->getIndexMap()->begin()->second);// 6이 올라갈 5의 자식을 가리켜야함
	if (pIndexNode->getParent() == NULL) {
		BpTreeNode* new_idxNode = new BpTreeIndexNode;
		new_idxNode->insertIndexMap(cut_idxNode->getIndexMap()->begin()->first, cut_idxNode);//5가 만들어지고 오른쪽 6이 있는 노드를 가리킴
		cut_idxNode->deleteMap(cut_idxNode->getIndexMap()->begin()->first);//이제 56 으로 나뉜 노드에 5를 지워줌
		cut_idxNode->setParent(new_idxNode);
		new_idxNode->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(new_idxNode);
	}
	else
	{
		BpTreeNode* parent_idxNode = pIndexNode->getParent();
		parent_idxNode->insertIndexMap(cut_idxNode->getIndexMap()->begin()->first, cut_idxNode);
		cut_idxNode->deleteMap(cut_idxNode->getIndexMap()->begin()->first);//이제 56 으로 나뉜 노드에 5를 지워줌
		cut_idxNode->setParent(parent_idxNode);

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

	return true;
}
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	if (root == NULL) return false;
	*fout << "FrequentPattern		Frequency" << endl;
	BpTreeNode* currNode = searchDataNode1(min_frequency);
	multimap<int, set<string>> list = currNode->getDataMap()->begin()->second->getList();
	multimap<int, set<string>>::iterator iter1 = list.begin();
	int k;
	while (1) {
		if (currNode == NULL) break;
		while (iter1 != list.end())
		{
			for (set<string>::iterator li = iter1->second.begin(); li != iter1->second.end(); li++)
			{
				k = currNode->getDataMap()->begin()->second->getFrequency();
				if (*li == item)
				{
					if(k >= min_frequency)
					printFrequentPatterns(iter1->second, item, k);
				}
			}
			iter1++;
		}
		
		currNode = currNode->getNext();
		if (currNode == NULL)break;
		list = currNode->getDataMap()->begin()->second->getList();
		iter1 = list.begin();
	}
	return true;
}
bool BpTree::printRange(string item, int min, int max) {

	return true;
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item, int k) {

	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	curPattern.erase(item);
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) {
		string temp = *it++;
		if (temp != item) *fout << temp << ", ";
		if (it == curPattern.end()) {
			*fout << item << "}    " << k << endl;
			break;
		}
		//*fout << ", ";
	}
}
