#include "Test.h"



bool Test::insertTest()
{
	boost::unordered::unordered_set<std::string> h;
	if(createFileStream("polski.txt"))
	{
		std::string word;
		std::getline (fileStream,word);
		clock_t start = clock();
		while(fileStream.eof()==false)
		{
			hashTab->insert(word);
			h.insert(word);
			std::getline (fileStream,word);
		}
		clock_t resultTime = clock() - start;
		printf("Insert time: %f\n", (static_cast<float>(resultTime))/CLOCKS_PER_SEC);
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
	if(createFileStream("polski.txt"))
	{
		std::string word;
		std::getline (fileStream,word);
		clock_t start = clock();
		
		while(fileStream.eof()==false)
		{
			hashTab->erase(word);
			std::getline (fileStream,word);
		}
		clock_t resultTime = clock() - start;
		printf("Erase time: %f\n", (static_cast<float>(resultTime))/CLOCKS_PER_SEC);
		
		fileStream.close();
	}
	else
	{
		return false;
	}
	return true;
}

bool Test::createFileStream(std::string pathFile)
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

/*

int testFromFile(std::string filePath)
{
	HashTab<std::string> hT(10000000);
	
	std::fstream fileStream;
	fileStream.open ("polski.txt", std::ifstream::in);
	std::string word;
	std::getline (fileStream,word);
	while(fileStream.eof()==false)
	{
		hT.insert(word);
		std::getline (fileStream,word);
	}
	fileStream.close();
	

	fileStream.open ("polski.txt", std::ifstream::in);
	//std::string word;
	std::getline (fileStream,word);
	while(fileStream.eof()==false)
	{
		hT.erase(word);
		std::getline (fileStream,word);
	}
	fileStream.close();
	
	
	return 0;
}

*/