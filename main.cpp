#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List<std::string> testList;
	
	for(unsigned int i = 0; i < 2;++i )
	{
		testList.insert("eloziom");
		testList.insert("eloziom");
		testList.insert("eloziom");
		
		cout << testList.getSize() << endl;
		//testList.erase("eloziom1");
		//testList.erase("eloziom2");
		testList.erase("eloziom");
		cout << testList.getSize() << endl;
		
		testList.clean();
		cout << testList.getSize() << endl;
	}
	
	return 0;
}