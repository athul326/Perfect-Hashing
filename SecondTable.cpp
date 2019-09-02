#include <string>
#include "SecondTable.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
SecondTable::SecondTable() {
	srand(seed);
	a = (rand() % p2) + 1;
	b = rand() % p2;
	seed++;
}
void SecondTable::add(Node* n) {
	initData.push_back(n);
}
unsigned long SecondTable::hash(Node* n) {
	return ((a*n->hash + b) % p2) % (secTable.size());
}
void SecondTable::insert() {
	for (int i = 0; i < initData.size(); i++) {
		if (secTable.at(hash(initData.at(i))) != nullptr) {
			clear();
		}
		else
		{
			secTable.at(hash(initData.at(i))) = initData.at(i);
		}
	}
}
void SecondTable::resize() {
	secTable.resize(initData.size()*initData.size());
}
int SecondTable::size() {
	return initData.size();
}
void SecondTable::clear() {
	for (int i = 0; i < secTable.size(); i++) {
		secTable.at(i) = nullptr;
	}
	srand(seed);
	a = (rand() % p2) + 1;
	b = rand() % p2;
	seed++;
	hashTried++;
	insert();
}
vector<Node*> SecondTable::getVector() {
	return initData;
}
int SecondTable::getHashTried() {
	return hashTried;
}
string SecondTable::find(unsigned long hashed) {
	unsigned long key = ((a*hashed + b) % p2) % (secTable.size());
	if (secTable.at(key) != NULL && secTable.at(key)->hash == hashed) {
		return secTable.at(key)->coords;
	}
	else {
		return "n/a";
	}
}