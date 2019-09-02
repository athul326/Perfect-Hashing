#ifndef MAINTABLE_H
#define MAINTABLE_H
#include <string>
#include <vector>
#include "SecondTable.h"
class MainTable {
public:
	MainTable(std::string fileName);
	void insert();
	void print();
	unsigned long hash(std::string text);
	int findCollisions(int numCollisions);
	void maxCity();
	void printCities(Node* n,std::vector<Node*> initData);
	int findHashTimes(int hashtimes);
	void search(std::string cityName);
private:
	void sortSecTable();
	std::vector<Node*> table;
	unsigned long p1 = 16890581;
	unsigned long p2 = 17027399;
	unsigned long a, b, c;
	int maxCollisions = 0;
	std::vector<std::string> data;
	std::vector<std::string> coord;
};
#endif 

