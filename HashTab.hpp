#define TYPICALMINNUMBEROFCEILS 32
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
	//hash = 0; //to delete
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
/*
	//Debug version:
	size_t result = 0;
	for(unsigned int i = 0; i < hashTable->size(); ++i)
	{
		result += (*hashTable)[i]->getSize();
	}
	
	return result;
*/

	//Release version:
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
	float newNumberOfCeils;
	size_t hashTableSize = hashTable->size();

	if(loadFactor > MAXLOADFACTOR && (hashTableSize >= TYPICALMINNUMBEROFCEILS) && (hashTableSize!= MAXNUMBEROFCEILS))
	{
		//newNumberOfCeils = findNextPrime(hashTableSize*2);
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTableSize)+1)));
		
		
		if(newNumberOfCeils > MAXNUMBEROFCEILS) newNumberOfCeils = MAXNUMBEROFCEILS;
	}
	else if(loadFactor < MINLOADFACTOR && (hashTableSize > TYPICALMINNUMBEROFCEILS) /*&& (TYPICALMINNUMBEROFCEILS!= MAXNUMBEROFCEILS)*/)
	{
		newNumberOfCeils = pow (2,(static_cast<int> (log2(hashTableSize - 1))));
		//newNumberOfCeils = findNextPrime(hashTableSize/2);
	}
	else
	{
		return false;
	}
	//std::cout << newNumberOfCeils << " ";
	std::vector<List<T>* >* oldHashTable = hashTable;
	hashTable = new std::vector<List<T>* >;

	init(newNumberOfCeils); ///tutaj robi sie 2 razy ! po co wypelnaic od razu??
	for(unsigned int i = 0; i < hashTableSize; ++i)  //hashTableSize is old size 
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
/*
//these method might be better!
template<class T>
bool HashTab<T>::isPrime(std::size_t x)
{
    std::size_t o = 4;
    for (std::size_t i = 5; true; i += o)
    {
        std::size_t q = x / i;
        if (q < i)
            return true;
        if (x == q * i)
            return false;
        o ^= 6;
    }
    return true;
}

template <class T>
size_t HashTab<T>::findNextPrime(size_t x)
{
    switch (x)
    {
    case 0:
    case 1:
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
    case 5:
        return 5;
    }
    std::size_t k = x / 6;
    std::size_t i = x - 6 * k;
    std::size_t o = i < 2 ? 1 : 5;
    x = 6 * k + o;
    for (i = (3 + o) / 2; !isPrime(x); x += i)
        i ^= 6;
    return x;
}
*/