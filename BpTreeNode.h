#pragma once
#include "FrequentPatternNode.h"
#include "FPNode.h"
class BpTreeNode
{
private:
	BpTreeNode* pParent; //parent node
	BpTreeNode* pMostLeftChild; // mostleftchilde node

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	~BpTreeNode() {

	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; } //set mostleftchilde function
	void setParent(BpTreeNode* pN) { pParent = pN; } //set parent function

	BpTreeNode* getParent() { return pParent; } //get parent function
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; } //get mostleftchilde function

	virtual void setNext(BpTreeNode* pN) {} //virtual function, setnext node function
	virtual void setPrev(BpTreeNode* pN) {} //virtual function, setprev node function
	virtual BpTreeNode* getNext() { return NULL; } //virtual function, get next node function
	virtual BpTreeNode* getPrev() { return NULL; }//virtual function, getprev node function

	virtual void insertDataMap(int n, FrequentPatternNode* pN) {}//virtual function, insert datamap
	virtual void insertIndexMap(int n, BpTreeNode* pN) {}//virtual function, insert indexmap
	virtual void deleteMap(int n) {} //virtual function, deleteMap

	virtual map<int, BpTreeNode*>* getIndexMap() { return {}; } //virtual function, getindexMap
	virtual map<int, FrequentPatternNode*>* getDataMap() { return {}; }//virtual function, get dataMap

};
