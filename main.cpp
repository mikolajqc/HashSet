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
//-g [from] [to] [step] - wielkosc problemu - generate
// nothing - user edition

int main( int argc, char * argv[] )
{
	if(argc == 1)
	{
		printf("User mode!\n");
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
			Generator gen;
			gen.generatePairs();
			gen.generateVectorToRandom();
			for(unsigned int i = 0; i < 10000; ++i)cout << gen.generatePartOfString();
		}
	}
	return 0;
}