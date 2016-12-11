#include <iostream>
#include "HashTab.h"

using namespace std;

int main()
{
	List<std::string> testList;
	
	HashTab<std::string> has(100000) ;
	
	if (has.empty()) std::cout << "empty" << std::endl;
	
	for(unsigned int i = 0; i < 100000; ++i)
	{
		has.insert(std::to_string(i));
	}
	
	for(unsigned int i = 0; i < 100000; ++i)
	{
		has.erase(std::to_string(i));
	}
	
	return 0;
}