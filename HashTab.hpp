#define KMIN 16

#include <bitset>

template <class T> 
HashTab<T>::HashTab(size_t k)
{
	size_t startNumberOfCeils;
	
	MAXNUMBEROFCEILS = k;
	if(k < KMIN)
	{
		startNumberOfCeils = k;
	}
	else
	{
		startNumberOfCeils = KMIN;
	}
	
	hashTable.reserve(KMIN); // not k ?
	
	for(unsigned int i = 0; i < startNumberOfCeils; ++i)
	{
		List<T>* tempList = new List<T>;
		hashTable.push_back(tempList);
	}
	
}


template <class T> 
HashTab<T>::~HashTab()
{
	for(unsigned int i = 0; i < hashTable.size(); ++i)
	{
		delete hashTable[i];
	}
}

template <class T>
unsigned int HashTab<T>::hashFunction(T value)
{
	unsigned int hash = 2166136261;
	
	for (unsigned int i = 0; i < value.size(); ++i)
	{
		hash = hash ^ static_cast<int>(value[i]);
		hash = hash * 16777619;
		//std::cout  << hash  << std::endl;
	}
	hash%=hashTable.size();
	
	return hash;
}