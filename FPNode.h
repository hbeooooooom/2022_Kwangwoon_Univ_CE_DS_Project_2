#pragma once
#include<string>
#include <cstring>
#include <map>
#include <cmath>
using namespace std;
class FPNode
{
private:
	int frequency; 
	string item;
	FPNode* parent;
	FPNode* next;
	map<string, FPNode*> children;
public:
	FPNode();
	~FPNode();
	void setParent(FPNode* node) { this->parent = node; } //setParent node function
	void setNext(FPNode* node) { next = node; } // set next node function
	void setItem(string str){this->item =str;	} //set item function
	void pushchildren(string item, FPNode* node) { children.insert(map<string, FPNode*>::value_type(item, node)); } 
	void updateFrequency(int frequency) { this->frequency += frequency; }

	int getFrequency() { return frequency; } // get Frequency data function
	FPNode* getParent() { return parent; } //get parent node function
	FPNode* getNext() { return next; } //get next node function
	FPNode* getChildrenNode(string item);//get childrenNode function
	string getItem(){return item;} //get item function
	map<string, FPNode*> getChildren() { return children; } //get children node function
};


