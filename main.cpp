#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List<std::string> testList;
	
	for(unsigned int i = 0; i < 2;++i )
	{
		testList.insert("eloziom");
		testList.insert("eloziom1");
		testList.insert("eloziom2");
		
		cout << testList.getSize() << endl;
		testList.erase(testList.end());
		cout << testList.getSize() << endl;
		
		testList.clean();
		cout << testList.getSize() << endl;
	}
	
	return 0;
}