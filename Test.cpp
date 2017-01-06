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

bool Test::correctnessTest()
{
	bool result = true;
	
	if(createFileStream())
	{
		//First test if size of HashTab is equal to  number of inserted elements
		for(unsigned int i = 1; i < 1000; ++i)
		{
			for(unsigned int j = 0; j < i; ++j)
			{	
				std::string word;
				std::getline (fileStream,word);
				if(!fileStream.eof()) hashTab->insert(word);
			}
			printf("Insert %d elements result: ", i);
			result *= (hashTab->getSize() == i);
			if(result) printf("OK\n");
			else printf("BAD\n");
			hashTab->clean();
			fileStream.clear();
			fileStream.seekg(0, std::ifstream::beg);
		}
		
		for(unsigned int i = 1; i < 1000; ++i)
		{
			for(unsigned int j = 0; j < i; ++j)
			{	
				std::string word;
				std::getline (fileStream,word);
				if(!fileStream.eof()) hashTab->insert(word);
			}
			
			fileStream.clear();
			fileStream.seekg(0, std::ifstream::beg);
			
			for(unsigned int j = 0; j < i; ++j)
			{	
				std::string word;
				std::getline (fileStream,word);
				if(!fileStream.eof()) hashTab->erase(word);
			}
			printf("Erase %d elements result: ", i);
			result *= (hashTab->getSize() == 0);
			if(result) printf("OK\n");
			else printf("BAD\n");
			hashTab->clean();
			fileStream.clear();
			fileStream.seekg(0, std::ifstream::beg);
		}
		
		
		
	}
	else
	{
		result = false;
	}
	closeFileStream();
	return result;
}