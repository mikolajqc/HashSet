
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
	float insertTest(); //these methods return time
	float eraseTest();
	bool createFileStream();
	bool closeFileStream();
	
	bool correctnessTest();
	
	bool correctnessInsertTest();
	bool correctnessEraseTest();
	bool correctnessFindTest();
	bool correctnessCleanTest();
	bool correctnessEmptyTest();
	bool correctnessGetSizeTest();
	bool correctnessIteratorTest();
	
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