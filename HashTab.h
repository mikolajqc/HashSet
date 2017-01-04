#ifndef HASHTAB_H
#define HASHTAB_H

#include "List.h"
#include <vector>

template <class T>
class HashTab
{
	
public:
	HashTab(size_t K); // K - max number of ceils in vector
	~HashTab();
	
	bool init(size_t sizeToReserve); //czy init wogle jest konieczny? czy reserve tego nie
									 //zalatwia czy nie mozna tworzyc listy tylko gdy zajety?
	
	bool insert(T value, bool withResize = true);
	bool erase(T value);
	bool clean();
	bool empty();
	//dopisz find();
	
	size_t getSize(); //number of elements

	typename List<T>::Iterator operator[] (int index);
	
	//iterator w ogole w tym wypadku jest konieczny?
	class Iterator: public std::iterator<std::forward_iterator_tag, T>
	{
		friend class HashTab;
	public:
		Iterator();
		Iterator(typename List<T>::Iterator lI, unsigned int cI, HashTab* hT)
		:listIterator(lI), currentIndex(cI), hashTab(hT){}
		T operator*()
		{
			return *listIterator;
		}
		
		Iterator& operator++()
		{
			
			++listIterator;
			
			while(currentIndex!=( (*hashTab).hashTable->size() -1 ) && (listIterator == (*(*hashTab).hashTable)[currentIndex]->end() ) )
			{
				++currentIndex;
				listIterator = (*(*hashTab).hashTable)[currentIndex]->begin();
			}
			return *this;
		}
		
		Iterator operator++(int)
		{
			Iterator temp = *this;
			++listIterator;
			
			while(currentIndex!=( (*hashTab).hashTable->size() -1 ) && (listIterator == (*(*hashTab).hashTable)[currentIndex]->end() ) )
			{
				++currentIndex;
				listIterator = (*(*hashTab).hashTable)[currentIndex]->begin();
			}
			return temp;
		}
		
		Iterator& operator--()
		{
			while((listIterator == (*(*hashTab).hashTable)[currentIndex]->begin() ) && currentIndex != 0 )
			{
				--currentIndex;
				listIterator = (*(*hashTab).hashTable)[currentIndex]->end();
			}
			--listIterator;
			return *this;
		}
		
		Iterator operator--(int)
		{
			Iterator temp = *this;
			while((listIterator == (*(*hashTab).hashTable)[currentIndex]->begin() ) && currentIndex != 0 )
			{
				--currentIndex;
				listIterator = (*(*hashTab).hashTable)[currentIndex]->end();
			}
			--listIterator;
			return temp;
		}
		
		bool operator==(const Iterator& a) const
		{
			return listIterator == a.listIterator && currentIndex == a.currentIndex && hashTab == a.hashTab;
		}
		
		bool operator!=(const Iterator& a) const
		{
			return listIterator != a.listIterator || currentIndex != a.currentIndex || hashTab != a.hashTab;
		}
	
	private:
		typename List<T>::Iterator listIterator;
		unsigned int currentIndex;
		HashTab* hashTab;
	};
	
	Iterator begin()
	{
		return Iterator((*hashTable)[minIndex]->begin(), minIndex, this);
	}
	
	Iterator end()
	{
		return Iterator((*hashTable)[hashTable->size() -1]->end(), (hashTable->size() -1), this);
	}

	bool erase(Iterator i);

	bool find(T value, std::vector<Iterator>& iterators);
	
private:
	std::vector<List<T>* >* hashTable;
	size_t MAXNUMBEROFCEILS; // max number of ceils in vector
	size_t minIndex; // it is helpfull when looking for begin and end element
	size_t maxIndex;
	unsigned int hashFunction(T value); // FNV-1a
	size_t size;
	
	size_t findNextPrime(size_t number);
	bool isPrime (size_t number);
	size_t findPreviousPrime(size_t number);
	
	bool resize(); // resizing when load factor is > 0.8 or if the load factor < 0.6
	float calculateLoadFactor();
};

#include "HashTab.hpp"

#endif /* HASHTAB_H */