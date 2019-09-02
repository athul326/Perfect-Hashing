#ifndef  SECONDTABLE_H
#define SECONDTABLE_H
#include <vector>
struct Node {
	unsigned long hash = NULL;
	std::string coords;
	class SecondTable* secTable = nullptr;
};
class SecondTable {
public:
	SecondTable();
	void add(Node* n);
	void insert();
	void clear();
	unsigned long hash(Node* n);
	int size();
	void resize();
	std::string find(unsigned long hashed);
	std::vector<Node*> getVector();
	int getHashTried();
private:
	std::vector<Node*> initData;
	std::vector<Node*> secTable;
	unsigned long a;
	unsigned long b;
	unsigned long p1 = 16890581;
	unsigned long p2 = 17027399;
	int seed = 0;
	int hashTried = 1;

};
#endif // ! SECONDTABLE_H

