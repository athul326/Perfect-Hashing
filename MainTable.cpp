#include <string>
#include "MainTable.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
MainTable::MainTable(string filename) {
	string line;
	ifstream file;
	file.open(filename);
	while (getline(file, line)) {
		data.push_back(line);
		getline(file, line);
		coord.push_back(line);
	}
	srand(0);
	c = (rand() % p1) + 1;
	a = (rand() % p2) + 1;
	b = rand() % p2;
	table.resize(data.size());
	file.close();
	insert();
	sortSecTable();
}
void MainTable::insert() {
	for (int i = 0; i < data.size(); i++) {
		Node* newNode = new Node();
		newNode->hash = hash(data.at(i));
		newNode->coords = coord.at(i);
		//Hash code for where in vector to store node
		unsigned long spot = ((a*newNode->hash + b) % p2) % data.size();
		//If spot in vector is empty then add Node there
		if (table.at(spot)==nullptr) {
			table.at(spot) = newNode;
		}
		//If there exists a secondary table at the spot then add node into secondary table
		else if (table.at(spot)->secTable != nullptr) {
			table.at(spot)->secTable->add(newNode);
		}
		//If there exists a node in the spot but no secondary table then make a secondary table and move both nodes in there
		else {
			SecondTable* newTable = new SecondTable();
			//Node* moveNode = new Node();
			//moveNode->hash = table.at(spot)->hash;
			//moveNode->coords = table.at(spot)->coords;
			//table.at(spot)->hash = NULL;
			//table.at(spot)->coords = "";
			//newTable->add(moveNode);
			newTable->add(newNode);
			table.at(spot)->secTable = newTable;
		}
	}
}
unsigned long MainTable::hash(string text) {
	unsigned long sum = 0;
	for (int i = 0; i < text.length(); i++) {
		sum = ((sum*c)+text.at(i))%p1;
	}
	//sum = sum % p1;
	return sum;
}
void MainTable::sortSecTable() {
	for (int i = 0; i < table.size(); i++) {
		if (table.at(i)!=NULL&&table.at(i)->secTable != nullptr) {
			table.at(i)->secTable->resize();
			table.at(i)->secTable->insert();
			if (table.at(i)->secTable->size() > maxCollisions) {
				maxCollisions = table.at(i)->secTable->size() + 1;
			}
		}
	}
}
int MainTable::findCollisions(int numCollisions) {
	int numCities = 0;
	if (numCollisions == 0) {
		for (int i = 0; i < table.size(); i++) {
			if (table.at(i) == NULL) {
				numCities++;
			}
		}
	}
	for (int i = 0; i < table.size(); i++) {
		if (table.at(i) != NULL && table.at(i)->secTable != nullptr) {
			if (table.at(i)->secTable->size()+1 == numCollisions) { numCities++; }
		}
		else if (table.at(i) != NULL && table.at(i)->secTable == nullptr) {
			if (numCollisions == 1) { numCities++; }
		}
	}
	return numCities;
}
void MainTable::maxCity() {
	for (int i = 0; i < table.size(); i++) {
		if (table.at(i) != NULL && table.at(i)->secTable != nullptr) {
			if (table.at(i)->secTable->size()+1 == maxCollisions) {
				printCities(table.at(i),table.at(i)->secTable->getVector());
				break;
			}
		}
	}
}
int MainTable::findHashTimes(int hashtimes) {
	int count = 0;
	for (int i = 0; i < table.size(); i++) {
		if (table.at(i) != NULL && table.at(i)->secTable != nullptr) {
			if (table.at(i)->secTable->getHashTried() == hashtimes) { count++; }
		}
	}
	return count;
}
void MainTable::printCities(Node* n,vector<Node*> initData) {
	int pos = 0;
	pos = distance(coord.begin(), find(coord.begin(), coord.end(), n->coords));
	cout << data.at(pos) << " (" << n->coords << ")" << endl;
	for (int i = 0; i < initData.size(); i++) {
		pos = distance(coord.begin(), find(coord.begin(), coord.end(), initData.at(i)->coords));
		cout << data.at(pos) << " (" << initData.at(i)->coords << ")" << endl;
	}
}
void MainTable::print() {
	cout << "p1: " << p1 << "\np2: " << p2 << "\na: " << a << "\nb: " << b << "\nc: " << c << endl << endl;
	cout << "number of cities: " << table.size()<<endl;
	cout << "maximum collision: " << maxCollisions << endl;
	for (int i = 0; i < 10; i++) {
		cout << "# primary slots with " << i << " cities: " << findCollisions(i) << endl;
	}
	cout << "** cities in the slot with most collisions **" << endl;
	maxCity();
	for (int i = 1; i < 11; i++) {
		cout << "# secondary hash tables trying " << i << " hash functions: " << findHashTimes(i) << endl;
	}
}
void MainTable::search(string cityName) {
	unsigned long hashed = hash(cityName);
	unsigned long key = ((a*hashed + b) % p2) % data.size();
	cout << "city details: Key = " << key << endl;
	if (table.at(key)!=NULL&&table.at(key)->hash == hashed) {
		cout << cityName << " (" << table.at(key)->coords << ") " << endl;
	}
	else if (table.at(key) != NULL&&table.at(key)->secTable != nullptr) {
		string coord = table.at(key)->secTable->find(hashed);
		if (coord != "n/a") {
			cout<<cityName<< " (" << coord << ") " << endl;
		}
		else {
			cout << "n/a" << endl;
		}
	}
	else {
		cout << "n/a" << endl;
	}
}