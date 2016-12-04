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
	
	
	cout << *(testList.begin()++) << endl;
	
	testList.erase("eloziom2");
	cout << *(++testList.begin()) << endl;
	
	cout << testList.getSize() << endl;
	
	//testList.clean();
	
	return 0;
}