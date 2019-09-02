#include "MainTable.h"
#include <iostream>
using namespace std;
int main(int argc, char*argv[]){
	const string SEARCH_FOR_CITY = "Ajo, AZ";
	if (argc < 2) {
		cout << "Correct usage: " << argv[0] << " filename " << endl;
	}
	else {
		MainTable test(argv[1]);
		test.print();
		test.search(SEARCH_FOR_CITY);
	}
}