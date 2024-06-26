#pragma once

#include <set>
#include <map>
#include<string>
using namespace std;

class FrequentPatternNode
{
private:
	int frequency;		// FrequentPattern frequency
	multimap<int, set<string> > FrequentPatternList;	//first is FrequentPattern size, second is FrequentPattern data

public:
	FrequentPatternNode() { frequency = 0; }
	~FrequentPatternNode() { FrequentPatternList.clear(); }
	void setFrequency(int frequency) { this->frequency = frequency; } // set frequency data
	void InsertList(set<string> item) { FrequentPatternList.insert(multimap<int, set<string>>::value_type(item.size(),item)); } // insertList function
	int getFrequency() { return frequency; } // get frequency function
	multimap<int, set<string> > getList() { return FrequentPatternList; } // get list function
};


