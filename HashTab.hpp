#define KMIN 32
#define MAXLOADFACTOR 0.8

#include <bitset>

template <class T> 
HashTab<T>::HashTab(size_t k)
{
	size_t startNumberOfCeils;
	size = 0;
	
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
	}
	hash%=hashTable.size();
	
	return hash;
}

template <class T>
bool HashTab<T>::insert(T value)
{
	++size;
	if(calculateLoadFactor() > MAXLOADFACTOR)
	{
		std::cout << "LoadFactor > 0.8!" << std::endl;
	}
	
	unsigned int index = hashFunction(value);
	
	hashTable[index]->insert(value);
	
	std::cout << "Inserted to index: " << index << std::endl;
	
	return true;
}

template <class T>
bool HashTab<T>::erase(T value)
{
	unsigned int index = hashFunction(value);
	size -= hashTable[index]->erase(value);
	return true;
}

template <class T>
bool HashTab<T>::clean()
{
	for(unsigned int i = 0; i < hashTable.size(); ++i)
	{
		hashTable[i]->clean(); //we cant do delete, cause we might to insert sth in the future
	}
	size = 0;
	return true;
}

template <class T>
bool HashTab<T>::empty()
{
	if(size == 0) return true;
	else return false;
}

template <class T>
float HashTab<T>::calculateLoadFactor()
{
	return static_cast<float>(size)/hashTable.size();
}

template <class T>
size_t HashTab<T>::getSize()
{
/*
	//Debug version:
	size_t result = 0;
	for(unsigned int i = 0; i < hashTable.size(); ++i)
	{
		result += hashTable[i]->getSize();
	}
	
	return result;
*/
	//Release version:
	return size;
}