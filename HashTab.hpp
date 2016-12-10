#define TYPICALMINNUMBEROFCEILS 32
#define MAXLOADFACTOR 0.8
#define MINLOADFACTOR 0.5

#include <cmath>
#include <bitset>

template <class T> 
HashTab<T>::HashTab(size_t k)
{
	size_t startNumberOfCeils;
	size = 0;
	
	MAXNUMBEROFCEILS = k;
	if(k < TYPICALMINNUMBEROFCEILS)
	{
		startNumberOfCeils = k;
	}
	else
	{
		startNumberOfCeils = TYPICALMINNUMBEROFCEILS;
	}
	
	hashTable.reserve(TYPICALMINNUMBEROFCEILS); // not k ?
	
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
	resize();
	
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
	
	resize();
	
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

	//Debug version:
	size_t result = 0;
	for(unsigned int i = 0; i < hashTable.size(); ++i)
	{
		result += hashTable[i]->getSize();
	}
	
	return result;

/*
	//Release version:
	return size;
*/
}

template <class T>
Node<T>& HashTab<T>::operator[] (int index)
{
	return *hashTable[index]->headNode; //really? it should be return iterator to the head
}

template <class T>
bool HashTab<T>::resize()
{
	float loadFactor = calculateLoadFactor();
	float newNumberOfCeils;

	if(loadFactor > 0.8 && (hashTable.size() >= TYPICALMINNUMBEROFCEILS) && (TYPICALMINNUMBEROFCEILS!= MAXNUMBEROFCEILS))
	{
		std::cout << "loadfactor > 0.8!" << std::endl;
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTable.size())) + 1));
	}
	else if(loadFactor < 0.5 && (hashTable.size() >= TYPICALMINNUMBEROFCEILS) && (TYPICALMINNUMBEROFCEILS!= MAXNUMBEROFCEILS))
	{
		std::cout << "loadFactor < 0.5!" << std::endl;
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTable.size()))));
	}
	else
	{
		std::cout << "load factor is fine" << std::endl;
		return false;
	}
	
	std::vector<List<T>* > newHashTable;
	newHashTable.reserve(newNumberOfCeils); // necesarry to create hashTable as a pointer 
	
	return true;
}