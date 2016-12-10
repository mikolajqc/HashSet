#include <iostream>
#include "HashTab.h"

using namespace std;

int main()
{
	List<std::string> testList;
	/*
	for(unsigned int i = 0; i < 2;++i )
	{
		testList.insert("eloziom");
		testList.insert("eloziom1");
		testList.insert("eloziom2");
		
		cout << testList.getSize() << endl;
		
		testList.erase("eloziom");
		cout << testList.getSize() << endl;
		
	}
	
	testList.erase("eloziom1");
	cout << testList.getSize() << endl;
	
	*/
	HashTab<std::string> has(2048) ;
	
	//std::cout << has.hashFunction("hequerwa Pis to chuje") << std::endl;
	
	return 0;
}