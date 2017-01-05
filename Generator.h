#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <string>
#include <iostream>

class Generator
{
public:
	int generatePairs();
	int generateVectorToRandom();
	int generateFiles(); //this method return number of created files
	std::string generatePartOfString();

	Generator(unsigned long int st, unsigned int sp, unsigned int n)
	:start(st), step(sp), numberOfSteps(n) {};

private:
	unsigned long int start;
	unsigned int step;
	unsigned int numberOfSteps;

	std::vector<std::pair<std::string, int> > pairs;
	std::vector<std::string> vectorToRandom;

	std::vector<char> letters = {
		'a', 'e', 'o', 'i', '\n',
		'z', 'n', 's', 'r', 'w',
		'c', 't', 'l', 'y', 'k',
		'd', 'p', 'm', 'u', 'j',
		'b', 'g', 'h', 'f', 'q'
	};
	std::vector<int> frequences = {
		95, 88, 86, 82, 80, 65,
		57, 50, 47, 47, 44, 40,
		39, 38, 35, 33, 31, 28,
		25, 23, 15, 14, 10, 3, 1
	}; //sum = 1076
};

#endif