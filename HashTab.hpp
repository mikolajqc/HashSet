#define TYPICALMINNUMBEROFCEILS 16
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
	hashTable->reserve(sizeToReserve); // not k ?
	
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
	
	std::cout << "Value: " << value << " index: " << index << std::endl;
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
		(*hashTable)[i]->clean(); //we cant do delete, cause we might to insert sth in the future
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

	//Debug version:
	size_t result = 0;
	for(unsigned int i = 0; i < hashTable->size(); ++i)
	{
		result += (*hashTable)[i]->getSize();
	}
	
	return result;

/*
	//Release version:
	return size;
*/
}

template <class T>
typename List<T>::Iterator HashTab<T>::operator[] (int index)
{
	return (*hashTable)[index]->begin(); //really? it should be return iterator to the head
}

template <class T>
bool HashTab<T>::resize()
{
	float loadFactor = calculateLoadFactor();
	float newNumberOfCeils;

	if(loadFactor > MAXLOADFACTOR && (hashTable->size() >= TYPICALMINNUMBEROFCEILS) && (hashTable->size()!= MAXNUMBEROFCEILS))
	{
		std::cout << "loadfactor > 0.8! ";
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTable->size())) + 1));
		if(newNumberOfCeils > MAXNUMBEROFCEILS) newNumberOfCeils = MAXNUMBEROFCEILS;
	}
	else if(loadFactor < MINLOADFACTOR && (hashTable->size() > TYPICALMINNUMBEROFCEILS) /*&& (TYPICALMINNUMBEROFCEILS!= MAXNUMBEROFCEILS)*/)
	{
		std::cout << "loadFactor < 0.1! ";
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTable->size() - 1))));
	}
	else
	{
		std::cout << "load factor is fine "<< loadFactor << std::endl;
		return false;
	}
	
	std::cout << loadFactor << std::endl;
	
	std::vector<List<T>* >* oldHashTable = hashTable;
	hashTable = new std::vector<List<T>* >;

	init(newNumberOfCeils);
	for(unsigned int i = 0; i < oldHashTable->size(); ++i)
	{
		for(typename List<T>::Iterator lI = (*oldHashTable)[i]->begin(); lI != (*oldHashTable)[i]->end(); ++lI)
		{
			insert(*lI, false);
		}
		delete (*oldHashTable)[i];
	}
	std::cout << "Resized! Current vector size: " << hashTable->size() << std::endl;
	delete oldHashTable;
	
	return true;
}