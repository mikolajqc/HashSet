#include <iostream>
#include <unordered_map>
#include "HashTab.h"
#include <ctime>
#include <boost/unordered_set.hpp>

using namespace std;

int main()
{
	double lastDuration1 = 1;
	double lastDuration2 = 1;
	//double lastDuration3 = 1;
	//double lastDuration4 = 1;
	
	for(unsigned int k = 1000; k< 10000000; k=2*k)
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
		
		//erase
/*
		cout << "Erase dla: " << k;
		start3 = clock();
		for(unsigned int i = 0; i < amount; ++i)
		{
			string test = std::to_string(i);
			has2.erase(test);
		}
		duration3 = ( std::clock() - start3 ) / (double) CLOCKS_PER_SEC;
		cout << " unordered_map: " << duration3 << " " << (duration3/lastDuration3) << " x wieksze ";
		lastDuration3 = duration3;
		
		
		start4 = clock();
		for(unsigned int i = 0; i < amount; ++i)
		{
			string test = std::to_string(i);
			has.erase(test);
		}
		duration4 = ( std::clock() - start4 ) / (double) CLOCKS_PER_SEC;

		cout << " HashTab: " << duration4 << " " << (duration4/lastDuration4) << " x wieksze " << endl;
		lastDuration4 = duration4;
*/
	}
	
	return 0;
}