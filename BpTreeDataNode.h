#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode //inheritence BpTreeNode
{
private:
	map <int, FrequentPatternNode*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;
public:
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}

	void setNext(BpTreeNode* pN) { pNext = pN; } //set next Node function
	void setPrev(BpTreeNode* pN) { pPrev = pN; } //set prev Node function
	BpTreeNode* getNext() { return pNext; } // get next node function
	BpTreeNode* getPrev() { return pPrev; } // get prev node function

	void insertDataMap(int n, FrequentPatternNode* pN) { //insert dataMap function
		mapData.insert(map<int, FrequentPatternNode*>::value_type(n, pN));
	}

	void deleteMap(int n) {//delete have n frequency map
		mapData.erase(n);
	}
	map<int, FrequentPatternNode*>* getDataMap() { return &mapData; } // get dataMap function

	
};

#endif
