//Mikolaj Ciesielski
//Plik z implementacja klasy HashTab

#define TYPICALMINNUMBEROFCEILS 32 //It is initial number of ceils. When K<32 then initial number is K.
#define MAXLOADFACTOR 0.8
#define MINLOADFACTOR 0.2

#include <cmath>
#include <bitset>

template <class T> 
HashTab<T>::HashTab(size_t k)
{
	size_t startNumberOfCeils;
	
	MAXNUMBEROFCEILS = k;
	if(k < TYPICALMINNUMBEROFCEILS)
	{
		startNumberOfCeils = k;
	}
	else
	{
		startNumberOfCeils = TYPICALMINNUMBEROFCEILS;
	}
	
	hashTable = new std::vector<List<T>* >;
	init(startNumberOfCeils);
}


template <class T> 
HashTab<T>::~HashTab()
{
	for(unsigned int i = 0; i < hashTable->size(); ++i)
	{
		delete (*hashTable)[i];
	}
	delete hashTable;
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
	
	hash%=hashTable->size(); 
	return hash;
}

template <class T>
bool HashTab<T>::init(size_t sizeToReserve)
{
	hashTable->reserve(sizeToReserve);
	
	for(unsigned int i = 0; i < sizeToReserve; ++i)
	{
		List<T>* tempList = new List<T>;
		hashTable->push_back(tempList);
	}
	
	size = 0;
	return true;
}

template <class T>
bool HashTab<T>::insert(T value, bool withResize)
{

	unsigned int index = hashFunction(value);
	
	(*hashTable)[index]->insert(value);
	
	++size;
	
	if(withResize) resize();
	
	return true;
}

template <class T>
bool HashTab<T>::erase(T value)
{
	unsigned int index = hashFunction(value);
	size -= (*hashTable)[index]->erase(value);
	
	resize();
	
	return true;
}

template <class T>
bool HashTab<T>::clean()
{
	for(unsigned int i = 0; i < hashTable->size(); ++i)
	{
		(*hashTable)[i]->clean();
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
	return static_cast<float>(size)/hashTable->size();
}

template <class T>
size_t HashTab<T>::getSize()
{
	return size;
}

template <class T>
typename HashTab<T>::Iterator HashTab<T>::operator[] (int index)
{
	return Iterator((*hashTable)[index]->begin(), index, this);
}

template <class T>
bool HashTab<T>::resize()
{
	float loadFactor = calculateLoadFactor();
	size_t newNumberOfCeils;
	size_t hashTableSize = hashTable->size();

	if(loadFactor > MAXLOADFACTOR && (hashTableSize >= TYPICALMINNUMBEROFCEILS) && (hashTableSize!= MAXNUMBEROFCEILS))
	{
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTableSize)+1)));
		if(newNumberOfCeils > MAXNUMBEROFCEILS) newNumberOfCeils = MAXNUMBEROFCEILS;
	}
	else if(loadFactor < MINLOADFACTOR && (hashTableSize > TYPICALMINNUMBEROFCEILS) )
	{
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTableSize - 1))));
	}
	else
	{
		return false;
	}

	std::vector<List<T>* >* oldHashTable = hashTable;
	hashTable = new std::vector<List<T>* >;

	init(newNumberOfCeils); 

	for(unsigned int i = 0; i < hashTableSize; ++i)  //hashTableSize is oldHashTable size
	{
		for(typename List<T>::Iterator lI = (*oldHashTable)[i]->begin(); lI != (*oldHashTable)[i]->end(); ++lI)
		{
			insert(*lI, false); 
		}
		delete (*oldHashTable)[i];
	}

	delete oldHashTable;
	return true;
}
