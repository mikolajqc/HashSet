#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List<std::string> testList;
	
	cout << testList.getSize() << endl;
	testList.insert("eloziom");
	
	cout << testList.getSize() << endl;
	
	testList.insert("eloziom1");
	
	cout << testList.getSize() << endl;
	testList.insert("eloziom2");
	
	cout << testList.getSize() << endl;
	
	
	
	cout << *(++++++testList.begin()) << endl;
	
	return 0;
}