//Plik main.cpp projektu z przedmiotu AAL. Autor: Mikolaj Ciesielski
#include <iostream>
#include "HashTab.h"
#include <ctime>

#include <fstream>
#include "Test.h"
#include "Generator.h"
#include <cstdlib>

using namespace std;


int fileMode()
{
	printf("File mode!\n");
	size_t K;
	cout << "Enter maximal number of ceils in hash table:";
	cin >> K;
	std::string path;
	cout << "\nEnter a path: ";
	cin >> path;
	Test test(K, path);
	//test.test();
	if(test.correctnessTest() == true)
	{
		cout << "Result: OK\n";
	}
	else
	{
		cout << "Result: FAIL\n";
	}
	return 0;
}

int generateMode(int argc, char * argv[])
{
	printf("Generate mode!\n");
	size_t K;
	cout << "Enter maximal number of ceils in hash table:";
	cin >> K;
	Generator gen(1000,2,15);
	gen.generatePairs();
	gen.generateVectorToRandom();
	//only if necessary
	if(argc == 3 && *(argv[2] + 1) == 'f') gen.generateFiles();
	
	cout << "Number of strings:\tInsert time:\t\tErase time:\n";
	
	for(unsigned int i = 0; i < 15; ++i)
	{
		Test test(K,"Tests/" + std::to_string(i) + ".txt");
		cout << 1000 << " * 2^" << i << " strings \t";
		cout  << "Insert" << test.insertTest() << "s\t\t";
		cout  << "Erase" << test.eraseTest() <<  "s" <<endl;
	}
	return 0;
}

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
			fileMode();
		}
		else if(*(argv[1] + 1) == 'g')
		{
			generateMode(argc, argv);
		}
	}
	return 0;
}