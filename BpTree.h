#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>
#include<list>
class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree();
	/* essential */
	bool		Insert(int key, set<string> set); //insert function
	bool		excessDataNode(BpTreeNode* pDataNode); //excessDataNode function
	bool		excessIndexNode(BpTreeNode* pIndexNode); //excessIndexNode function
	void		splitDataNode(BpTreeNode* pDataNode); //splitDatanode function
	void		splitIndexNode(BpTreeNode* pIndexNode); //splitIndexNode function
	BpTreeNode* getRoot() { return root; } //get root data fucntion
	BpTreeNode* searchDataNode(int n); //find have n frequency data node fucntion
	void	printFrequentPatterns(set<string> pFrequentPattern, string item,int k); //printFrequentPatterns function
	void	printFrequentPatterns(set<string> pFrequentPattern, string item,double k,int kk);//printFrequentPatterns fucntion
	bool	printFrequency(string item, int min_frequency);//printFrequency function
	bool	printConfidence(string item, double item_frequency, double min_confidence); // printConfidence function
	bool 	printRange(string item, int min, int max); // printRange fucntion

};

#endif
