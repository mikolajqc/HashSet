//Plik main.cpp projektu z przedmiotu AAL. Autor: Mikolaj Ciesielski
#include <iostream>
//#include <unordered_map>
#include "HashTab.h"
#include <ctime>
#include <boost/unordered_set.hpp>
#include <fstream>
#include "Test.h"

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
			printf("File mode!\n");
			Test test(100000000);
			test.insertTest();
			test.eraseTest();
		}
		else if(*(argv[1] + 1) == 'g')
		{
			printf("Generate mode!\n");
		}
	}
	return 0;
}