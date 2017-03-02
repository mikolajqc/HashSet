#include "Test.h"

Test::Test(size_t K, std::string pathFile)
{
	hashTab = new HashTab<std::string>(K);
	this->pathFile = pathFile;
}

Test::~Test()
{
	delete hashTab;
}

float Test::insertTest()
{
	float result = -1;
	
	if(createFileStream())
	{
		std::string word;
		std::getline (fileStream,word);
		unsigned int i = 0;
		clock_t start = clock();
		
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
	float result = 0;
	
	if(createFileStream())
	{
		std::string word;
		std::getline (fileStream,word);
		unsigned int i = 0;
		clock_t start = clock();
		
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

bool Test::correctnessFindTest()
{
	bool result = true;
	
	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			
			if(!fileStream.eof()) hashTab->insert(word);
			
			typename std::vector<HashTab<std::string>::Iterator> iterators;
			result *= hashTab->find(word, iterators);
			result *= *iterators[0] == word;
		}
		
		printf("Find %d elements result: ", i);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}
	return result;
}

bool Test::correctnessInsertTest()
{
	bool result = true;
	
	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			
			if(!fileStream.eof()) hashTab->insert(word);
			
			std::vector<List<std::string>::Iterator> iterators;
			result *= (*(hashTab->hashTable))[hashTab->hashFunction(word)]->find(word, iterators);
		}
		
		printf("Insert %d elements result: ", i);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}
	return result;
}

bool Test::correctnessEraseTest()
{
	bool result = true;
	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			if(!fileStream.eof()) hashTab->insert(word);
		}
		
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		size_t lastSize = hashTab->getSize();
		
		for(unsigned int j = 0; j < i; ++j)
		{
			std::string word;
			std::getline (fileStream,word);
			if(!fileStream.eof()) hashTab->erase(word);
		}
		
		size_t currentSize = hashTab->getSize();
		
		printf("Erase %d elements result: ", i);
		result *= ((lastSize - currentSize) == i);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}
	return result;
}

bool Test::correctnessGetSizeTest()
{
	bool result = true;

	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			result *= (hashTab->getSize() == j);
			
			if(!fileStream.eof()) hashTab->insert(word);
			
		}
		printf("getSize test with %d elements result: ", i);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}

	return result;
}

bool Test::correctnessCleanTest()
{
	bool result = true;
	
	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			if(!fileStream.eof()) hashTab->insert(word);
		}
		
		printf("Clean test with %d elements result: ", i);
		hashTab->clean();
		
		size_t currentSize = 0;
		for(unsigned int i = 0; i < hashTab->hashTable->size(); ++i)
		{
			currentSize += (*(hashTab->hashTable))[i]->getSize();
		}
		
		result *= (currentSize == 0);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}
	
	return result;
}

bool Test::correctnessEmptyTest()
{
	bool result = true;
	
	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			result *= (hashTab->empty() == !j);
			
			if(!fileStream.eof()) hashTab->insert(word);
		}
		
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			if(!fileStream.eof())
			{
				hashTab->erase(word);
				result *= (hashTab->empty() == !(i-j-1));
			}
		}
		
		printf("Empty test with %d elements result: ", i);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}
	return result;
}

bool Test::correctnessIteratorTest()
{
	bool result  = true;
	
	for(unsigned int i = 1; i < 1000; ++i)
	{
		fileStream.clear();
		fileStream.seekg(0, std::ifstream::beg);
		
		for(unsigned int j = 0; j < i; ++j)
		{	
			std::string word;
			std::getline (fileStream,word);
			
			if(!fileStream.eof()) hashTab->insert(word);
			if(j == 0)
			{
				typename HashTab<std::string>::Iterator it = hashTab->begin();
				result *= (*it == word);
			}
		}
		
		typename HashTab<std::string>::Iterator iterator = hashTab->begin();
		unsigned int k =0;
		
		for(;iterator!=hashTab->end();++iterator,++k);
		result*= (k == hashTab->getSize());
		
		for(;iterator!=hashTab->begin();--iterator,--k);
		result*= (k == 0);
		
		unsigned int j = 0;
		typename HashTab<std::string>::Iterator it = hashTab->begin();
		
		for(;it!=hashTab->end();++it, ++j)
		{
			if(j == 0)
			{
				result*= (it == hashTab->begin());
				result*= !(it != hashTab->begin());
			}
			else
			{
				result*= !(it == hashTab->begin());
				result*= (it != hashTab->begin());
			}
		}
		
		
		printf("Iterator test with %d elements result: ", i);
		
		if(result) printf("OK\n");
		else printf("FAIL\n");
		
		hashTab->clean();
	}
	return result;
}

bool Test::correctnessTest()
{
	bool result = true;
	
	if(createFileStream())
	{
		result *= correctnessCleanTest();
		result *= correctnessGetSizeTest();
		result *= correctnessFindTest();
		result *= correctnessInsertTest();
		result *= correctnessEraseTest();
		result *= correctnessEmptyTest();
		result *= correctnessIteratorTest();
	}
	else
	{
		result = false;
	}
	closeFileStream();
	return result;
}
