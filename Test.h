
#ifndef TEST_H
#define TEST_H

#include <iostream>
//#include <unordered_map>
#include "HashTab.h"
#include <ctime>
#include <boost/unordered_set.hpp>
#include <fstream>

class Test
{
public:
	bool insertTest();
	bool eraseTest();
	bool createFileStream(std::string pathFile);
	bool closeFileStream();
	
	Test(size_t K)
	{
		hashTab = new HashTab<std::string>(K);
	}
	
	~Test()
	{
		delete hashTab;
	}
	
	
private:
	HashTab<std::string>* hashTab;
	std::fstream fileStream;
	
	
};

#endif