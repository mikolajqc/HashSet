#include "Test.h"


float Test::insertTest()
{
	float result = -1;
	
	if(createFileStream())
	{
		std::string word;
		std::getline (fileStream,word);
		clock_t start = clock();
		unsigned int i = 0;
		for(;fileStream.eof()==false;++i)
		{
			hashTab->insert(word);
			std::getline (fileStream,word);
		}
		clock_t resultTime = clock() - start;
		result = static_cast<float>(resultTime)/CLOCKS_PER_SEC;
		fileStream.close();
	}

	return result;
}

float Test::eraseTest()
{
	float result;
	if(createFileStream())
	{
		std::string word;
		std::getline (fileStream,word);
		clock_t start = clock();
		unsigned int i = 0;
		for(;fileStream.eof()==false;++i)
		{
			hashTab->erase(word);
			std::getline (fileStream,word);
		}
		clock_t resultTime = clock() - start;
		result = static_cast<float>(resultTime)/CLOCKS_PER_SEC;
		
		fileStream.close();
	}
	return result;
}

bool Test::createFileStream()
{
	fileStream.open (pathFile, std::ifstream::in);
	if(fileStream.is_open() == false)
	{
		printf("Error: No such directory!\n");
		return false;
	}
	return true;
}

bool Test::closeFileStream()
{
	fileStream.close();
	return true;
}

bool Test::test()
{
	return insertTest() && eraseTest() ;
}