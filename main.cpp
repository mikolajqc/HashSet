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
	HashTab<std::string> has(33) ;
	
	if (has.empty()) std::cout << "empty" << std::endl;
	
	has.insert("hequerwa Pis to chuje");
	has.insert("1hequerwa Pis to chuje");
	has.insert("2hequerwa Pis to chuje");
	has.insert("3hequerwa Pis to chuje");
	has.insert("4hequerwa Pis to chuje");
	has.insert("5hequerwa Pis to chuje");
	has.insert("6hequerwa Pis to chuje");
	has.insert("7hequerwa Pis to chuje");
	has.clean();
	std::cout << has.getSize() << std::endl;
	if (has.empty()) std::cout << "empty" << std::endl;
	has.insert("8hequerwa Pis to chuje");
	has.insert("9hequerwa Pis to chuje");
	has.insert("ahequerwa Pis to chuje");
	has.insert("dhequerwa Pis to chuje");
	has.insert("chequerwa Pis to chuje");
	has.insert("bhequerwa Pis to chuje");
	
	if (has.empty()) std::cout << "empty" << std::endl;
	std::cout << has.getSize() << std::endl;
	if (has.erase("dhequerwa Pis to chuje")) std::cout << "deleted" << std::endl;
	std::cout << has.getSize() << std::endl;
	
	return 0;
}