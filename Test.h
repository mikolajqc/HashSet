
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "HashTab.h"
#include <ctime>
#include <fstream>

class Test
{
public:

	float insertTest();
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
	
	Test(size_t K, std::string pathFile);
	~Test();
	
private:
	HashTab<std::string>* hashTab;
	std::fstream fileStream;
	std::string pathFile;
};

#endif
