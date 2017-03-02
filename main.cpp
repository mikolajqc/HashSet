//Mikolaj Ciesielski
//Plik main.cpp

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
	printf("Correctness test mode!\nBefore a test make sure test file has more than 1000 strings.\n");
	size_t K;
	cout << "Enter maximal number of ceils in hash table:";
	cin >> K;
	std::string path;
	cout << "\nEnter a path: ";
	cin >> path;
	Test test(K, path);

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
	#ifdef _WIN32
	std::string slash = "\\";
	#else
	std::string slash = "/";
	#endif
	std::fstream confFile;
	confFile.open ("Tests" + slash + "conf.txt", std::ifstream::in);
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

	if(argc == 3 && *(argv[2] + 1) == 'f')
	{
		cout << "Enter first number of strings: ";
		unsigned int firstSize, numberOfTests, maxLength, multiplier;
		cin >> firstSize;
		cout << "Enter number of tests: ";
		cin >> numberOfTests;
		cout << "Enter multipliers: ";
		cin >> multiplier;
		cout << "Enter maxLength of word: ";
		cin >> maxLength;
		
		Generator gen(firstSize,multiplier,numberOfTests, maxLength);
		
		gen.generatePairs();
		gen.generateVectorToRandom();
		cout << "Files generating..." << endl;
		gen.generateFiles();
	}
	
	
	cout <<"Time testing: \n";

	std::vector<unsigned int> conf;
	if(getConfiguration(conf) == false) return 0;
	
	
	std::vector<float>insertResults, eraseResults, qResult;
	
	#ifdef _WIN32
	std::string slash = "\\";
	#else
	std::string slash = "/";
	#endif
	
	for(unsigned int i = 0; i < conf[2]; ++i)
	{
		Test test(K,"Tests" + slash + std::to_string(i) + ".txt");
		insertResults.push_back(test.insertTest());
		eraseResults.push_back(test.eraseTest());
	}
	
	int median = insertResults.size()/2;
	unsigned int NMedian = pow(conf[1],median) * 1000;
	
	cout <<"\n";
	cout << "Insert test:\n";
	cout << "Number of strings:\tInsert time:\t\tq:\n";
	
	for(unsigned int i = 0; i < conf[2]; ++i)
	{
		unsigned int N = pow(conf[1],i) * 1000;
		cout << conf[0] << " * " << conf[1]<<"^" << i << " strings \t";
		printf("Insert:\t%.6fs\t%.6f\n", insertResults[i], (insertResults[i] * NMedian) / (insertResults[median] * N));
	}
	
	cout << "\n";
	cout << "Erase test:\n";
	cout << "Number of strings:\tInsert time:\t\tq:\n";
	
	for(unsigned int i = 0; i < conf[2]; ++i)
	{
		unsigned int N = pow(conf[1],i) * 1000;
		cout << conf[0] << " * " << conf[1]<<"^" << i << " strings \t";
		printf("Erase:\t%.6fs\t%.6f\n", eraseResults[i], (eraseResults[i] * NMedian) / (eraseResults[median] * N));
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