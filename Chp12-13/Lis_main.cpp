// Lis_main.cpp

#include <iostream>
#include "Lis.h"

using namespace std;

int main() {
	Lis<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4); // end 포인터

	for (Lis <int>::iterator it = list.begin(); it != list.end(); ++it) {
		cout << *it << " ";
	}

	cout << endl;


	return 0;

}
