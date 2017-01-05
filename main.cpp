#include <iostream>
#include <unordered_map>
#include "HashTab.h"
#include <ctime>
#include <boost/unordered_set.hpp>

using namespace std;

int main()
{
	/*
	double lastDuration1 = 1;
	double lastDuration2 = 1;
	
	for(unsigned int k = 1000000; k< 10000000; k=2*k)
	{
		cout << "Insert dla " << k;
		HashTab<std::string> has(1000000000);
		boost::unordered_set<string> has2;
		
		std::clock_t start1, start2;//, start3, start4;
		double duration1, duration2;//, duration3, duration4;
		unsigned int amount = k;
		
		
		start1 = clock();
		for(unsigned int i = 0; i < amount; ++i)
		{
			string test = std::to_string(i*i);
			has2.insert(test);
		}
		duration1 = ( std::clock() - start1 ) / (double) CLOCKS_PER_SEC;
		cout << " unordered_map: " << duration1 << " " << (duration1/lastDuration1) << " x wieksze ";
		lastDuration1 = duration1;
		
		
		
		start2 = clock();
		for(unsigned int i = 0; i < amount; ++i)
		{
			string test = std::to_string(i*i);
			has.insert(test);
		}
		duration2 = ( std::clock() - start2 ) / (double) CLOCKS_PER_SEC;

		cout << " HashTab: " << duration2 << " " << (duration2/lastDuration2) << " x wieksze " << endl;
		lastDuration2 = duration2;
		
		//for(typename HashTab<std::string>::Iterator i = has.begin(); i!=has.end(); ++i)
		//{
		//	std::cout << *i << std::endl;
		//}
		

	}
	
	
	*/
	
	
	HashTab<std::string> hashTab(10);
	hashTab.begin();
	
	hashTab.insert("hejka");
	hashTab.insert("hejka");
	hashTab.insert("a");
	typename HashTab<std::string>::Iterator i = hashTab.begin();
	std::cout << *i << std::endl;
	std::cout << *hashTab[0] << std::endl;
	hashTab.erase(i);
	i = hashTab.begin();
		hashTab.erase(i);
	i = hashTab.begin();
	hashTab.erase(i);
	i = hashTab.begin();

	
	return 0;
}