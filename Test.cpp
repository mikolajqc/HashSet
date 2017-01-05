#include "Test.h"



bool Test::insertTest()
{
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
		printf("Insert %d strings.\nTime: %fs\n", i,(static_cast<float>(resultTime))/CLOCKS_PER_SEC);
		fileStream.close();
	}
	else
	{
		return false;
	}
	return true;
}

bool Test::eraseTest()
{
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
		printf("Erase %d strings.\nTime: %fs\n", i, (static_cast<float>(resultTime))/CLOCKS_PER_SEC);
		
		fileStream.close();
	}
	else
	{
		return false;
	}
	return true;
}

bool Test::createFileStream()
{
	fileStream.open (pathFile, std::ifstream::in);
	if(fileStream.is_open() == false)
	{
		printf("Error: No such file directory!");
		return false;
	}
	return true;
}

bool Test::closeFileStream()
{
	fileStream.close();
	return true;
} 