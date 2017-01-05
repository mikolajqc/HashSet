//Plik main.cpp projektu z przedmiotu AAL. Autor: Mikolaj Ciesielski
#include <iostream>
#include "HashTab.h"
#include <ctime>
#include <boost/unordered_set.hpp>
#include <fstream>
#include "Test.h"
#include "Generator.h"
#include <cstdlib>

using namespace std;

//-f [filepath or default]
//-g -f full edition -start - generate
// nothing - user edition

int main( int argc, char * argv[] )
{
	if(argc == 1)
	{
		printf("Help:\n");
		printf("-f -file mode, you can enter a path to the file you want to use.\n");
		printf("-g generate mode\n-g -f - generate mode with generating all files\n");
	}
	else
	{
		if(*(argv[1]) != '-')
		{
			printf("Error: Have you missed \"-\"?\n");
			return -1;
		}
		if(*(argv[1] + 1) == 'f')
		{
			size_t K;
			cout << "Enter maximal number of ceils in hash table:";
			cin >> K;
			printf("File mode!\n");
			Test test(K, "polski.txt");
			test.insertTest();
			test.eraseTest();
		}
		else if(*(argv[1] + 1) == 'g')
		{
			printf("Generate mode!\n");
			Generator gen(1000,2,15);
			gen.generatePairs();
			gen.generateVectorToRandom();
			//only if necessary
			if(argc == 3 && *(argv[2] + 1) == 'f') gen.generateFiles();
			
			for(unsigned int i = 0; i < 15; ++i)
			{
				Test test(100000000,"Tests/" + std::to_string(i) + ".txt");
				test.insertTest();
				test.eraseTest();
			}
			
		}
	}
	return 0;
}