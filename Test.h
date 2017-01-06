
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "HashTab.h"
#include <ctime>
#include <boost/unordered_set.hpp>
#include <fstream>

class Test
{
public:
	bool test();
	float insertTest();
	float eraseTest();
	bool createFileStream();
	bool closeFileStream();
	
	Test(size_t K, std::string pathFile)
	{
		hashTab = new HashTab<std::string>(K);
		this->pathFile = pathFile;
	}
	
	~Test()
	{
		delete hashTab;
	}
	
	
private:
	HashTab<std::string>* hashTab;
	std::fstream fileStream;
	std::string pathFile;
	
};

#endif