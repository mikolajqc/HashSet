#include <iostream>
#include "HashTab.h"

using namespace std;

int main()
{
	List<std::string> testList;
	
	HashTab<std::string> has(1000000) ;
	
	if (has.empty()) std::cout << "empty" << std::endl;
	
	has.insert("Hello");
	cout << *has[11] << endl;
	
/*	for(unsigned int i = 0; i < 100000; ++i)
	{
		has.insert(std::to_string(i));
	}
	
	for(unsigned int i = 0; i < 100000; ++i)
	{
		has.erase(std::to_string(i));
	}

	if (has.empty()) std::cout << "empty" << std::endl;
*/	
	return 0;
}