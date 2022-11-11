#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
//template <class T>
class BpTreeIndexNode : public BpTreeNode { //inheritence BpTreeNode
private:
	map <int, BpTreeNode*> mapIndex;

public:
	BpTreeIndexNode() {}


	void insertIndexMap(int n, BpTreeNode* pN) {
		mapIndex.insert(map<int, BpTreeNode*>::value_type(n, pN)); //insert index data
	}

	void deleteMap(int n) {
		mapIndex.erase(n); //delete have n frequency map data
	}

	map <int, BpTreeNode*>* getIndexMap() { return &mapIndex; } //get index function

};

#endif