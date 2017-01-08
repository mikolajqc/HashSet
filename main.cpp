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
	printf("Correctness test mode!\n");
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

bool getConfiguration(std::vector<unsigned int>& result)
{
	std::fstream confFile;
	confFile.open ("Tests/conf.txt", std::ifstream::in);
	if(confFile.is_open() == false)
	{
		printf("Error: File: \"conf.txt\" doesnt exist!\n");
		return false;
	}
	std::string::size_type sizeType;
	std::string start, step, numberOfSteps;
	std::getline (confFile,start);
	std::getline (confFile,step);
	std::getline (confFile,numberOfSteps);
	
	result.push_back(std::stoi(start, &sizeType));
	result.push_back(std::stoi(step, &sizeType));
	result.push_back(std::stoi(numberOfSteps, &sizeType));
	
	confFile.close();
	return true;
}

int generateMode(int argc, char * argv[])
{
	printf("Time test mode!\n");
	size_t K;
	cout << "Enter maximal number of ceils in hash table:";
	cin >> K;
	//only if necessary
	if(argc == 3 && *(argv[2] + 1) == 'f')
	{
		cout << "Enter first number of strings: ";
		unsigned int firstSize, numberOfTests;
		cin >> firstSize;
		cout << "Enter first number of tests: ";
		cin >> numberOfTests;
		
		Generator gen(firstSize,2,numberOfTests);
		
		gen.generatePairs();
		gen.generateVectorToRandom();
		cout << "Files generating..." << endl;
		gen.generateFiles();
	}
	cout <<"Time testing: \n";
	cout << "Number of strings:\tInsert time:\t\tErase time:\n";
	
	std::vector<unsigned int> conf;
	if(getConfiguration(conf) == false) return 0;
	
	for(unsigned int i = 0; i < conf[2]; ++i)
	{
		Test test(K,"Tests/" + std::to_string(i) + ".txt");
		cout << conf[0] << " * 2^" << i << " strings \t";
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
		printf("-f -correctness test mode, you can enter a path to the file you want to use.\n");
		printf("-g -time test mode \n-g -f - with generators\n");
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